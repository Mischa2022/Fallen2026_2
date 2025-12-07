#include <Time.h>
#include <TimeLib.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
#include <RTClib.h>
#include <rotary.h>

//RFID
#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
#define NR_KNOWN_KEYS   6

unsigned long ergebnisA,ergebnisB; //buffer für Read der Blöcke wird in einer Funktion gefüllt
int last_key= NR_KNOWN_KEYS-1;
int key_used; //Puffer um getesteten Key, numerisch darzustellen
byte knownKeys[NR_KNOWN_KEYS][MFRC522::MF_KEY_SIZE] =  {
    
    {0xff,0xff,0xff,0xff,0xff,0xff},
    {0x00,0x00,0x00,0x00,0x00,0x00}, 
    {0xFF,0xE6,0xFF,0xFF,0xD1,0xFF},
    {0xa2,0x2c,0x08,0xb0,0x94,0x97},
    {0x00,0x00,0x00,0x13,0x8D,0xF1},
    {0x00,0x00,0x00,0x00,0x00,0x01} // als buffer für neuen Key
    };

//*************************************************************************************//
//String basis_konfig ="*FALLIN5223*1735477208*0*60*5*48*30*30*6*6*24*5*1*20*20*6*6*70*70*2*2*10*10*6*6*";
String basis_konfig ="*FALLEN2025*1745971200*0*60*4*48*48*48*2*1*24*3*1*25*25*3*1*75*75*2*2*10*15*6*2*";
String basis[26];
#define max_read  26
unsigned long Speicherwerte_Konfig [max_read-1];
String Con_Name=""; //Beispiel Conname, wird normalerweise aus der Konfig gefüllt
unsigned long con_start_time;        // con-startzeit wird über Konfig gefüllt.
unsigned long tagesdosis; 
unsigned long konfig_time;
int anzahl_tage; //für bestimmung aktuellen Tag 0=Anreisetag, 1=erster Spieltag usw. wird durch konfig gefüllt bedeutet maximal 5 spieltage ohne anreisetag
int UTC; // Zeitzone, wird durch Konfig gefüllt und muss nun wieder aktiv genutzt werden 2=Sommer 1=Winter unixtime wird mit 0 ausgegeben
int debug=1;
int erster_buchungstag=1; //0 gleich anreise //1 gleich ab ersten spieltag

//Con_Spezifikationen // werden nicht über Konfig gefüllt 
//*************************************************************************************//
unsigned long minimum_ray_writing =10000UL;  //minimum Raywert der beim Schreiben nicht unterschritten werden darf
unsigned long maximum_ray_writing =450000UL; //maximum Raywert der beim Schreiben nicht überschritten werden darf
//für Menschen
unsigned long start_raywert;      // standardwert, der vergeben wird bei neuen/leeren RFID-TAG. Ist nicht über Konfig abgedeckt
unsigned long startwert_min= 100; // proxy Raywert neue DOngel
unsigned long startwert_max= 200; // proxy Raywert neue DOngel

//für Mutanten
unsigned long start_raywert_m;      // standardwert, der vergeben wird bei neuen/leeren RFID-TAG. Ist nicht über Konfig abgedeckt
unsigned long startwert_min_m= 200; // proxy Raywert neue DOngel
unsigned long startwert_max_m= 300; // proxy Raywert neue DOngel

//Checkin
//*************************************************************************************//
unsigned long raywert_gelesen=0;
unsigned long raywert_gelesen2=0;
unsigned int  checkin_reason=0; //Grund für den Checkin
//String msg_conname; 
long oedlaender= 100;     //codierung für ray-o-mat
long mutant= 360;         //codierung für ray-o-mat
long bunkerbewohner =250; //codierung für ray-o-mat landen auf dem Dongel entspricht Typus
/*
unsigned long NanoClean; // variable für Ray-Abzug Einnahme Nanoclean
int Nanoclean_min_effekt;
int Nanoclean_max_effekt;
*/
  //Bloecke 2025 aera Sascha
//*************************************************************************************//
                                              //Bereich a                 Bereich b                            
     
//                                      62   
//                                      61   
//                                      60     

#define Admin1_block                    58    //Con_Start_read            Last_Booking_read    
#define Admin2_block                    57    //LifeCleaner_effekt_read   archtype_read
#define Admin3_block                    56    //Con_End                   Ray_value_extern_read (unser Raywert fuer aeussere)      
int block_nano[]{54,53,52,50};
int block_dekon[]{49,48,46,45,44,42,41};
int block_life[]{37,36,34,33,32};
int block_blood[]{30,29,28,26,25};
int block_clean[]{18,17,16,14};

//                                      40    
//                                      38      
//                                      24      
//                                      22      
//                                      21      
//                                      20      
//                                      13      
//                                      12                                              
//                                      10      
//                                       9      
//                                       8                                                                                
//                                       6
//                                       5
//                                       4
//                                       2
#define Admin4_block                     1    // frei                     Medirechte        
//Blöcke und Werte 2019
//*************************************************************************************//
#define Old_Ray_value_intern_read_block_2019 13   //Roys System alte Blöcke
#define constart_block_2019              8        //Roys System alte Blöcke
unsigned long Old_Ray_value_intern_read2019;
unsigned long Con_Start_read2019;

// Ausgaben / Pufferwerte die durch Check_RFID gefüllt werden
//*************************************************************************************//
unsigned long Con_Start_read;
unsigned long Con_End_read;
unsigned long Con_End;
unsigned long Last_Booking_read;
unsigned long Ray_value_intern_read;
unsigned long Ray_value_extern_read;
unsigned long archtype_read;
unsigned long free_space_read; // ohne Funktion
unsigned long new_free_space;
unsigned long rights;
unsigned long LifeCleaner_effekt_read;     //read-buffer fuer Auswirkung
unsigned long NanoClean_read[8]; 
unsigned long Dekon_read[14]; 
unsigned long LifeCleaner_read[10];
unsigned long Cleanray_read[8];
unsigned long BloodClean_read[10];

unsigned long Dekon;  // variable fuer Ray-Abzug Einnahme Dekon
int Dekon_min_effekt;
int Dekon_max_effekt;
int Dekon_per_day; 
int Dekon_per_con;    
int Dekoncounter_thisday=0;
int Dekoncounter_allday=0;

unsigned long NanoClean; // variable fuer Ray-Abzug Einnahme Nanoclean
int Nanoclean_min_effekt;
int Nanoclean_max_effekt;
int Nano_per_day;   
int Nano_per_con; 
int Nanocounter_thisday=0;
int Nanocounter_allday=0;

unsigned long LifeCleaner; // variable fuer Ray-Abzug Einnahme Lifecleaner --> aktuell 0
unsigned long LifeCleaner_buffer;  //(XStunden *60Min*60Sekunden) 
int Lifecleaner_min_effekt=0;//weil keinen Effekt auf Ray-Wert ist aber als Variable moeglich
int Lifecleaner_max_effekt=0;//weil keinen Effekt auf Ray-Wert ist aber als Variable moeglich
int LifeCleaner_per_day;    
int Life_per_con;  
int Lifecounter_thisday=0;
int Lifecounter_allday=0;

unsigned long Cleanray;// variable fuer Ray-Abzug Einnahme Cleanray
int Cleanray_min_effekt;
int Cleanray_max_effekt;
int Clean_per_day; 
int Clean_per_con;
int Cleancounter_thisday=0;
int Cleancounter_allday=0;

unsigned long BloodClean; // variable fuer Ray-Abzug Einnahme Blutwaesche
int Bloodclean_min_effekt;
int Bloodclean_max_effekt;
int Blood_per_day; 
int Blood_per_con;   
int Bloodcounter_thisday=0;
int Bloodcounter_allday=0;

unsigned long Drawback;// variable fuer Ray-Aufschlag Einnahme Drawbackmarke
int Drawback_min_effekt= 10; //fehlt noch in der Konfig
int Drawback_max_effekt=15;  //fehlt noch in der Konfig

int Menge_Dekon=0;      //Ablage fuer Mengen gebuchter Medis
int Menge_Nanoclean=0;  //Ablage fuer Mengen gebuchter Medis
int Menge_Life=0;       //Ablage fuer Mengen gebuchter Medis
int Menge_Clean=0;      //Ablage fuer Mengen gebuchter Medis
int Menge_Blood=0;      //Ablage fuer Mengen gebuchter Medis
int Menge_Draw=0;       //Ablage fuer Mengen gebuchter Medis

//OLED
//*************************************************************************************//

#define USE_LCD 0x7920

#if USE_LCD == 0x7920
#include "Adafruit_ST7920_kbv.h" //local
Adafruit_ST7920_kbv Display(10);
#define LCD_BEGIN()    Display.begin()
#define KS0108_WHITE   WHITE
#define KS0108_BLACK   BLACK
#define KS0108_INVERSE INVERSE

#endif

char*msg="";
char*buchungsgrund;
char*buchungsgrund2;
char* Medi[] {"Update     ","Nanoclean  ","Dekon      ","Lifecleaner","Bloodclean ","Cleanray   ","Drawback   "};

//RTC
//*************************************************************************************//
RTC_DS3231 rtc;
//RTC_DS1307 RTC;
DateTime t;

unsigned long aktuell_time;        // buffer für aktuelle zeit
int con_tag; //puffer um zu bestimmen, welcher tag aktuell läuft 
unsigned long rest_time;  

//Fehlerzähler & Rechenhilfen
//*************************************************************************************//
unsigned long ray_writing;
int error=0;  //counter für fehlgeschlagene leseversuche RFID
int ergebnis; //counter für fehlerhaft getestete Keys
int feedback; //counter für erfolgreiches testen eines keys
int ray_counter=50;
 int lc_counter=0;
int x,y;
long raywert,raywert2=0;
long ray_malus=0;
bool LC_aktiv=0;

unsigned long lifecleaner_hour=10;
//button
//*************************************************************************************//

#define DT  6
#define CLK 2 
#define Switch  4
Rotary rotary = Rotary(DT,CLK,Switch);
volatile unsigned char result;

int counterx = 0;
int maxebene;

bool lock= false;
int read_wert;
int ebene=0;
int unterebene=0;
int menue=0;
bool vektor=false;

//LED
//*************************************************************************************//

int led_green=11;
int led_yellow=15;
int led_red=13;

void setup() {
	Serial.begin(57600);		// Initialize serial communications with the PC
  Wire.begin();
	SPI.begin();			// Init SPI bus

pinMode(led_green, OUTPUT);
digitalWrite(led_green, HIGH);
delay(500);
digitalWrite(led_green, LOW);
pinMode(led_yellow, OUTPUT);
digitalWrite(led_yellow, HIGH);
delay(500);
digitalWrite(led_yellow, LOW);
pinMode(led_red, OUTPUT);
digitalWrite(led_red, HIGH);
delay(500);
digitalWrite(led_red, LOW);

randomSeed(analogRead(0));
  
LCD_BEGIN();
Display.display();

Display.setRotation(2);
Display.clearDisplay();
 mfrc522.PCD_Init();   // Init MFRC522     
      //rtc.begin();

       if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
      
     //RTC_DS1307
/*  if (! RTC.isrunning()) {
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }*/
  
    //RTC_DS3231
/* if (RTC.lostPower()) {
    RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));   
  }*/
cut(basis_konfig, basis, '*');
read_konfig_out_of_string_light();
    
draw_mode(0);

t = rtc.now();      
aktuell_time=t.unixtime();
delay(1000);
      Serial.printf("Momentane Zeit: %4d-%02d-%02d %02d:%02d:%02d", year(aktuell_time), month(aktuell_time), day(aktuell_time), hour(aktuell_time), minute(aktuell_time), second(aktuell_time));
      Serial.write('\n');delay(50);
      Serial.print(F("Momentane Zeit Unix: "));
      Serial.println(aktuell_time); // Ohne UTC da allgemein gueltige Zeitangabe
     // Serial.write('\n');delay(write_pause);
      Serial.print(F("Con_Start:"));
      Serial.println(con_start_time);

      con_tag=con_tag_bestimmen(aktuell_time,con_start_time,rest_time);
      Serial.print(F("Contag:"));
      Serial.println(con_tag);
}

void loop() {
if(ebene==0){   
    
   if (rotary.buttonPressedReleased(20)) {
      lock=!lock; 
      if(lock==true){ebene=1;menue=1;}else{ ebene=0;menue=0;}
     }
     draw_mode(ebene);
  
}
   else{
      result = rotary.process();
      rotary_read(0,10);
     }
     
if (  mfrc522.PICC_IsNewCardPresent()&&mfrc522.PICC_ReadCardSerial()) {
 digitalWrite(led_yellow, HIGH);
 delay(500);
 digitalWrite(led_yellow, LOW);
 if(ebene==0){
  Check_rfid_tag_pipboy(1,0);
 //Check_rfid_tag(1,0);
 new_ray(raywert);//automatisch korrigieren auf vergangene zeit, seid letztem buchen, nur anzeigen, kein schreiben
//button_controll();
draw_mode(ebene);
 }


//Analyse
if(menue==1&&unterebene==1){
  Check_rfid_tag(10,1);
  new_ray(Ray_value_extern_read/1000);
    Display.clearDisplay();
    Display.setTextSize(1);
    Display.setTextColor(WHITE);
    Display.setCursor( 0, 20);
    Display.print("Analyse fertig");
    Display.display();
    delay(2000);
    menue=1;ebene=1;unterebene=2;counterx=0;
}   

//manipulieren von raywert
if(menue==3&&unterebene==3){
  
   newkey();// falls Dongel bereits eingecheckt
   delay(100);
   key__searchB(14);// falls Dongel noch nicht eingecheckt/ für Dummy-Dongel
   delay(100);
   rfid_reading(knownKeys[0],Admin3_block ); //56
      Con_End_read=ergebnisA;
      Ray_value_extern_read=ergebnisB; 
   
 if(Con_Start_read!=0){ //falls spielertag
  
   if(Ray_value_extern_read+ray_malus<10000){
    writing(knownKeys[last_key],56,Con_End_read, 10000);
    }
  else{
      writing(knownKeys[last_key],56,Con_End_read, Ray_value_extern_read+ray_malus);
      }
  }
 
 if(Con_Start_read==0){ //falls leerer oder plot dongel
  
  if(Ray_value_extern_read+ray_malus<10000){
    writing(knownKeys[key_used],56,Con_End_read, 10000);
    }
  else{
    writing(knownKeys[key_used],56,Con_End_read, Ray_value_extern_read+ray_malus);
    }
  }menue=3;unterebene=0;
}
  if(menue==2&&unterebene==1){
      DateTime now = rtc.now(); 
    aktuell_time=now.unixtime();
   newkey();// falls Dongel bereits eingecheckt
   delay(100);
   medibuchung_pipboy(1);
    Display.clearDisplay();
    Display.setTextSize(1);
    Display.setTextColor(WHITE);
    Display.setCursor( 0, 20);
    Display.print("Update fertig");
    Display.display();
    delay(2000);
    menue=2;unterebene=0;
    draw_mode(ebene);
  }
  if(menue==2&&unterebene==2){
      DateTime now = rtc.now(); 
    aktuell_time=now.unixtime();
   newkey();// falls Dongel bereits eingecheckt
   delay(100);
   medibuchung_pipboy(2);
    Display.clearDisplay();
    Display.setTextSize(1);
    Display.setTextColor(WHITE);
    Display.setCursor( 0, 20);
    Display.print("Nanoclean fertig");
    Display.display();
    delay(2000);
    menue=2;unterebene=0;
    draw_mode(ebene);
  }
  if(menue==2&&unterebene==3){
      DateTime now = rtc.now(); 
    aktuell_time=now.unixtime();
   newkey();// falls Dongel bereits eingecheckt
   delay(100);
   medibuchung_pipboy(3);
    Display.clearDisplay();
    Display.setTextSize(1);
    Display.setTextColor(WHITE);
    Display.setCursor( 0, 20);
    Display.print("Dekon fertig");
    Display.display();
    delay(2000);
    menue=2;unterebene=0;
    draw_mode(ebene);
  }

   if(menue==2&&unterebene==4){
      DateTime now = rtc.now(); 
    aktuell_time=now.unixtime();
   newkey();// falls Dongel bereits eingecheckt
   delay(100);
   medibuchung_pipboy(4);
    Display.clearDisplay();
    Display.setTextSize(1);
    Display.setTextColor(WHITE);
    Display.setCursor( 0, 20);
    Display.print("Lifecleaner fertig");
    Display.display();
    delay(2000);
    menue=2;unterebene=0;
    draw_mode(ebene);
  }

    if(menue==2&&unterebene==5){
      DateTime now = rtc.now(); 
    aktuell_time=now.unixtime();
   newkey();// falls Dongel bereits eingecheckt
   delay(100);
   medibuchung_pipboy(5);
    Display.clearDisplay();
    Display.setTextSize(1);
    Display.setTextColor(WHITE);
    Display.setCursor( 0, 20);
    Display.print("Bloodclean fertig");
    Display.display();
    delay(2000);
    menue=2;unterebene=0;
    draw_mode(ebene);
  }

    if(menue==2&&unterebene==6){
      DateTime now = rtc.now(); 
    aktuell_time=now.unixtime();
   newkey();// falls Dongel bereits eingecheckt
   delay(100);
   medibuchung_pipboy(6);
    Display.clearDisplay();
    Display.setTextSize(1);
    Display.setTextColor(WHITE);
    Display.setCursor( 0, 20);
    Display.print("Cleanray fertig");
    Display.display();
    delay(2000);
    menue=2;unterebene=0;
    draw_mode(ebene);
  }

   if(menue==2&&unterebene==7){
      DateTime now = rtc.now(); 
    aktuell_time=now.unixtime();
   newkey();// falls Dongel bereits eingecheckt
   delay(100);
   medibuchung_pipboy(7);
    Display.clearDisplay();
    Display.setTextSize(1);
    Display.setTextColor(WHITE);
    Display.setCursor( 0, 20);
    Display.print("Drawback fertig");
    Display.display();
    delay(2000);
    menue=2;unterebene=0;
    draw_mode(ebene);
  }
  
//manipulieren von Lifecleaner
if(menue==4&&unterebene==2){
      DateTime now = rtc.now(); 
    aktuell_time=now.unixtime();
   newkey();// falls Dongel bereits eingecheckt
   delay(100);
   //Serial.println("bin hier");
   key__searchB(14);// falls Dongel noch nicht eingecheckt/ für Dummy-Dongel
   delay(100);
 //   Serial.println("bin nun hier");
 if(Con_Start_read==0){ //falls plot
  writing(knownKeys[key_used],57,aktuell_time+(lifecleaner_hour*3600), archtype_read);//10stunden

 // Serial.println("bin jetzt hier");
 }
 if(Con_Start_read!=0){//falls spielertag
  writing(knownKeys[last_key],57,aktuell_time+(lifecleaner_hour*3600), archtype_read);//10stunden

//  Serial.println("bin mal hier");
 }
 menue=4;unterebene=0;
    }
    
//checkin
if(menue==6&&unterebene==1){
  checkin(oedlaender,false,2,0);
    Display.clearDisplay();
    Display.setTextSize(1);
    Display.setTextColor(WHITE);
    Display.setCursor( 0, 20);
    Display.print("Checkin fertig");
    Display.display();
    delay(2000);
    menue=6;ebene=0;unterebene=0;counterx=0;
}   

//reset
if(menue==7&&unterebene==1){
  rfid_reset();
    Display.clearDisplay();
    Display.setTextSize(1);
    Display.setTextColor(WHITE);
    Display.setCursor( 0, 20);
    Display.print("Reset fertig");
    Display.display();
    delay(2000);
    menue=0;ebene=0;unterebene=0;counterx=0;
}





    mfrc522.PICC_HaltA();   //finale stopfunktion
    mfrc522.PCD_StopCrypto1();//finale stopfunktion
    ray_malus=0;
    
     }
}
