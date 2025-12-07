#include <avr/wdt.h>
#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>
#include <TimeLib.h>
#include <RTClib.h>
#include <SD.h>
#include <EEPROM.h>
#include <LiquidCrystal_I2C.h>
#include <rotary.h>
#include <Bounce2.h>


//Geraetspezifisch
//*************************************************************************************//
char*Terminalname = "Terminal11";
//char*Terminalname = "  Heart  ";
int debug=1;
int erster_buchungstag=1; //0 gleich anreise //1 gleich ab ersten spieltag

//Con_Spezifikationen // werden ueber Konfig gefuellt
//*************************************************************************************//
String basis_konfig ="*FALLEN2025*1745971200*0*60*4*48*48*48*2*1*24*3*1*25*25*3*1*75*75*2*2*10*15*6*2*";

String basis2[26];
String Con_Name=""; //Beispiel Conname, wird normalerweise aus der Konfig gefuellt
String neu_konfig;//fuer konfig import
//String neu_konfig2;//fuer konfig import
String neu[26];//fuer konfig import
//String uebertragen;
//String uebertragen2;
char conname[11];

//char array2[50];
//char array3[50];

unsigned long con_start_time;        // con-startzeit wird ueber Konfig gefuellt.
unsigned long con_end_time;
unsigned long tagesdosis; 
unsigned long konfig_time;

int anzahl_tage; //fuer bestimmung aktuellen Tag 0=Anreisetag, 1=erster Spieltag usw. wird durch konfig gefuellt bedeutet maximal 5 spieltage ohne anreisetag
int UTC; // Zeitzone, wird durch Konfig gefuellt und muss nun wieder aktiv genutzt werden 2=Sommer 1=Winter unixtime wird mit 0 ausgegeben

bool warten = false;//fuer konfig import

//HARDWARE Version 2024
//*************************************************************************************//

//RFID
#define RST_PIN         7         
#define SS_PIN          22  
//SD
#define chipSelect  31
//LED
#define ledPin  5   
// buzzer
#define buzzer_pin  6 
//buttons & poti

#define DT  2
#define CLK 3 
#define Switch  4
#define BUTTON_PIN A5 
#define POTI_PIN A7 

LiquidCrystal_I2C lcd(0x27,20,4);//GELB
//LiquidCrystal_I2C lcd(0x3F,20,4); //BLAU

RTC_DS3231 rtc;
bool input_over_rotary=false; //false = poti & button

//*************************************************************************************//
//HARDWARE Version Sascha Orgaplex
//*************************************************************************************//
/*
//RFID
#define RST_PIN         7         
#define SS_PIN          13  
     
//SD
#define chipSelect  31

//LED
#define ledPin  35   

// buzzer
#define buzzer_pin  A1 
//#define buzzer_pin  6 //buzzer aus

//buttons & poti
bool input_over_rotary=false; //false = poti & button
#define DT  2
#define CLK 3 
#define Switch  A14
#define BUTTON_PIN A15 //nicht vergeben
#define POTI_PIN A13//nicht vergeben

LiquidCrystal_I2C lcd(0x27,20,4); //GELB
//LiquidCrystal_I2C lcd(0x3F,20,4);//BLAU
//RTC_PCF8563 rtc;
RTC_DS3231 rtc;

*/
//*************************************************************************************//



//Con_Spezifikationen // werden nicht ueber Konfig gefuellt 
//*************************************************************************************//
unsigned long minimum_ray_writing =10000UL;  //minimum Raywert der beim Schreiben nicht unterschritten werden darf
unsigned long maximum_ray_writing =450000UL; //maximum Raywert der beim Schreiben nicht ueberschritten werden darf

//fuer Menschen
unsigned long start_raywert;      // standardwert, der vergeben wird bei neuen/leeren RFID-TAG. Ist nicht ueber Konfig abgedeckt
unsigned long startwert_min= 60; // proxy Raywert neue DOngel
unsigned long startwert_max= 250; // proxy Raywert neue DOngel

//fuer Mutanten
unsigned long start_raywert_m;      // standardwert, der vergeben wird bei neuen/leeren RFID-TAG. Ist nicht ueber Konfig abgedeckt
unsigned long startwert_min_m= 200; // proxy Raywert neue DOngel
unsigned long startwert_max_m= 300; // proxy Raywert neue DOngel

//Checkin
//*************************************************************************************//
unsigned long raywert_gelesen=0;
unsigned long raywert_gelesen2=0;
unsigned int  checkin_reason=0; //Grund fuer den Checkin

long oedlaender= 100;     //codierung fuer ray-o-mat
long mutant= 360;         //codierung fuer ray-o-mat
long bunkerbewohner =250; //codierung fuer ray-o-mat landen auf dem Dongel entspricht Typus

//RFID
//*************************************************************************************//
MFRC522 mfrc522(SS_PIN, RST_PIN);   
MFRC522::MIFARE_Key key;
#define NR_KNOWN_KEYS   6

unsigned long ergebnisA,ergebnisB; //buffer fuer Read der Bloecke wird in einer Funktion gefuellt
int last_key= NR_KNOWN_KEYS-1;
int key_used; //Puffer um getesteten Key, numerisch darzustellen
byte knownKeys[NR_KNOWN_KEYS][MFRC522::MF_KEY_SIZE] =  {
    
    {0xff,0xff,0xff,0xff,0xff,0xff},
    {0x00,0x00,0x00,0x00,0x00,0x00}, 
    {0xFF,0xE6,0xFF,0xFF,0xD1,0xFF},
    {0xa2,0x2c,0x08,0xb0,0x94,0x97},
    {0x00,0x00,0x00,0x13,0x8D,0xF1},
    {0xff,0xff,0xff,0xff,0xff,0xff} // als buffer fuer neuen Key
    };

byte known_id[10][4]={
  //medilog
  {0x3C,0xFB,0x0D,0x04},
  {0x35,0x47,0x05,0x04},
  {0x5A,0x02,0x05,0x04},
  {0x92,0x8D,0x04,0x04},
  {0x8E,0xCC,0x04,0x04},
  //mode
  {0x5E,0x6F,0x0B,0x04},
  {0xC5,0xC0,0x06,0x04},
  {0x9F,0x02,0x09,0x04},
  {0x8A,0x99,0x06,0x04},
  {0xCB,0xFA,0x06,0x04}

    };
byte id_buffer[4];  
bool known =false; 

//Bloecke 2024 aera Sascha / Frank
//*************************************************************************************//
 /*                                             //Bereich a                 Bereich b
#define Admin1_block                    58    //Con_Start_read            Last_Booking_read    
#define Admin2_block                    57    //LifeCleaner_effekt_read   archtype_read
#define Admin3_block                    56    //Ray_value_intern_read     Ray_value_extern_read (unser Raywert fuer aeussere)
#define Nano1_block                     54    //NanoClean_read[0]         NanoClean_read[1]           
#define Nano2_block                     53    //NanoClean_read[2]         NanoClean_read[3]
#define Dekon1_block                    50    //Dekon_read[0]             Dekon_read[1]
#define Dekon2_block                    49    //Dekon_read[2]             Dekon_read[3]
#define Dekon3_block                    48    //Dekon_read[4]             Dekon_read[5]
#define LifeCleaner1_block              46    //LifeCleaner_read[0]       LifeCleaner_read[1]
#define LifeCleaner2_block              45    //LifeCleaner_read[2]       LifeCleaner_read[3]
#define LifeCleaner3_block              44    //LifeCleaner_read[4]       LifeCleaner_read[5]
#define BloodClean1_block               42    //BloodClean_read[0]        BloodClean_read [1]
#define BloodClean2_block               41    //BloodClean_read[2]        BloodClean_read [3]
#define BloodClean3_block               40    //BloodClean_read[4]        BloodClean_read [5]
#define Cleanray1_block                 38    //Cleanray_read[0]          Cleanray_read[1]
#define Cleanray2_block                 37    //Cleanray_read[2]          Cleanray_read[3]
#define Cleanray3_block                 36    //Cleanray_read[4]          Cleanray_read[5]
#define Admin4_block                    1     // frei                     Medirechte    
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

//Bloecke und Werte 2019 aera Roy
//*************************************************************************************//
/*
#define Old_Ray_value_intern_read_block_2019 13   //Roys System alte Bloecke
#define constart_block_2019              8        //Roys System alte Bloecke
unsigned long Old_Ray_value_intern_read2019;
unsigned long Con_Start_read2019;
*/
// Ausgaben / Pufferwerte die durch Check_RFID gefuellt werden
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

//Puffer fuer Medis und ihre Auswirkungen wird durch Konfig und Check_rfid gefuellt
//*************************************************************************************//
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

// SD / Ausgaben
//*************************************************************************************//
File konfigFile;  //Konfigimportdatei
File buchunglog;  // Ablage der Medibuchungen mit einigen Details
File checkinlog;  // Ablage der Checkindaten mit einigen Details
File medilog;     // Datei zum Speichern der Mengen an Medibuchungen um sie spaeter auszuwerten beim Einsammeln
File moduslog;
#define max_read  26



//String kontroll_key;
String Puffer;

char*msg0;
char*msg1;  //Hauptbemerkung im Display wenn Prozess durch
char*msg2;  //Nebenbemerkung zbs " Ray:"
char*msg3;  //Wertausgabe auf dem Display
char*msg4;
char*msg5;
char*msg6;
char*buchungsgrund;
char*buchungsgrund2;

unsigned long Speicherwerte_Konfig [max_read-1]; //fuer lesen von sd, zum ablegen EEPROM

int konfig_check =0;
int typus=0;
int Menge_Dekon=0;      //Ablage fuer Mengen gebuchter Medis
int Menge_Nanoclean=0;  //Ablage fuer Mengen gebuchter Medis
int Menge_Life=0;       //Ablage fuer Mengen gebuchter Medis
int Menge_Clean=0;      //Ablage fuer Mengen gebuchter Medis
int Menge_Blood=0;      //Ablage fuer Mengen gebuchter Medis
int Menge_Draw=0;       //Ablage fuer Mengen gebuchter Medis

//RTC
//*************************************************************************************//

DateTime t;
unsigned long rest_time;         // restliche sekunden um con-start auf 24:00 aufzufuellen als erst buchung, wichtig fuer Ray-O-Mat
unsigned long UNIX_korrektur=3600;
unsigned long aktuell_time;        // buffer fuer aktuelle zeit
int con_tag; //puffer um zu bestimmen, welcher tag aktuell laeuft 

//Serielle Kommunikation
//*************************************************************************************//
#define anzahl_werte 11
String read_String = "";
String read_konfig_String = "";
String read_String2 = "";
char ziel_char=' '; //nachdem auswerten dieses chars, muss unbedingt ' ' wieder gesetzt werden
char char_read[anzahl_werte];
char* Medi[] {"Update     ","Nanoclean  ","Dekon      ","Lifecleaner","Bloodclean ","Cleanray   ","Drawback   "};

unsigned long wert=0;
unsigned long ziel_long=0;
int write_pause =80;
int werte[anzahl_werte];
int counter=0;
int port= 0;
int modusbuffer[3];

bool stringComplete = false;  
bool flow=0;
bool newkonfig=false;
                                                                                                   
//Fehlerzaehler & Rechenhilfen
//*************************************************************************************//
unsigned long ray_writing;
int error=0;  //counter fuer fehlgeschlagene leseversuche RFID
int ergebnis; //counter fuer fehlerhaft getestete Keys
int feedback; //counter fuer erfolgreiches testen eines keys

//Terminalvariablen
//*************************************************************************************//   

unsigned long entsperrzeit; 
unsigned long sperrzeit=120000; 
unsigned long aktuelle_millis;

int modus=0; // auswahl fuer verschiedene terminals. 0=Godzilla, 1=checkin,2=buchung
bool locked=false;

//LCD

//Bool fuer Anzeige // hier wird festgelegt, welche optionen das terminal grundsaetzlich anzeigen und bearbeiten darf
bool Anzeige_update =false;
bool Anzeige_Nanoclean =false;
bool Anzeige_Dekon =false;
bool Anzeige_Lifecleaner =false;
bool Anzeige_Blutwaesche =false;
bool Anzeige_Cleanray =false;
bool Anzeige_drawback =false;

bool tft=false;
  
//Button
//*************************************************************************************// 
Bounce2::Button button = Bounce2::Button();
Rotary rotary = Rotary(DT,CLK,Switch);
volatile unsigned char result;
int poti_anzeige;
int counterx = 0;
int maxebene;
bool ebene= false;

//*************************************************************************************//
//*************************************************************************************//

void setup() {

  
pinMode(buzzer_pin, OUTPUT);
pinMode(ledPin, OUTPUT);
pinMode(POTI_PIN, INPUT);

button.attach( BUTTON_PIN, INPUT ); // USE EXTERNAL PULL-UP
button.interval(5); 
button.setPressedState(LOW); 


randomSeed(analogRead(0));

Serial.begin(57600); 
//Serial1.begin(57600); 
Serial2.begin(57600); 
Serial3.begin(57600); 
Wire.begin();        
rtc.begin();
SPI.begin();
lcd.init();
lcd.backlight();
mfrc522.PCD_Init(); 

t = rtc.now();      
aktuell_time=t.unixtime();
delay(1000);
initialisierung2();

rest_time=86400- ((con_start_time+(UTC*UNIX_korrektur))%86400);


//uhr_pruefen(aktuell_time);
unsigned long a_t_korrektur=0;
      

      a_t_korrektur=aktuell_time+(UTC*3600);
                                                                  
      Serial.printf("Momentane Zeit: %4d-%02d-%02d %02d:%02d:%02d", year(a_t_korrektur), month(a_t_korrektur), day(a_t_korrektur), hour(a_t_korrektur), minute(a_t_korrektur), second(a_t_korrektur));
      Serial.write('\n');delay(write_pause);
      Serial.print(F("Momentane Zeit Unix: "));
      Serial.print(aktuell_time); // Ohne UTC da allgemein gueltige Zeitangabe
      Serial.write('\n');delay(write_pause);
      Serial.print(F("Con_Start:"));
      Serial.print(con_start_time);
      Serial.write('\n');delay(write_pause);
      
   if(aktuell_time>con_start_time+rest_time){
      //Serial.write("vergangene Sekunden ab Anreise:");
      //Serial.print(aktuell_time-(con_start_time+rest_time));
      Serial.print(F("vergangene Stunden ab Anreise:"));
      Serial.println((aktuell_time-(con_start_time+rest_time))/3600);
      
       }
       else{
        Serial.println(F("Vor Constart"));
      }
      
      delay(50);
      con_tag=con_tag_bestimmen(aktuell_time,con_start_time,rest_time);
      Serial.print(F("Contag:"));
      Serial.println(con_tag);
myprint("----------------------------------------------------------------------------------------","","",true,true,false,1,port);
myprint("----------------------------------------------------------------------------------------","","",true,true,false,1,port);  
        
        lcd.setCursor(1, 1);
        lcd.print(t.year(), DEC);
        lcd.print("/");
        lcd.print(t.month(), DEC);
        lcd.print('/');
        lcd.print(t.day(), DEC);
        lcd.setCursor(1, 2);
        lcd.print(t.hour(), DEC);
        lcd.print(':');
        lcd.print(t.minute(), DEC);
        lcd.print(':');
        lcd.print(t.second(), DEC);  
        delay(3000);


      menue_print_lcd(modus,0);     
      myprint("Nun Dongel auflegen","","",false,true,false,1,0);
 
                 
wdt_enable(WDTO_8S);
}
