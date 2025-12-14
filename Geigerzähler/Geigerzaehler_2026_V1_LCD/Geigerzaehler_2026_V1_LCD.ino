#include <stdlib.h> 
#include <string.h>
#include <RTClib.h>
#include <TimeLib.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//*****************************************************************************************//

#define lCD_Version 3
//1= großes LCD gelb  3= große LCD blau 2= kleines LCD gelb  4= kleines LCD blau 5=Dominik
//*****************************************************************************************//
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

// Ausgaben / Pufferwerte die durch Check_RFID gefüllt werden
//*************************************************************************************//
unsigned long Con_Start_read;
unsigned long Last_Booking_read;
unsigned long Con_End_read;
unsigned long Con_End;
unsigned long Ray_value_intern_read;
unsigned long Ray_value_extern_read;
unsigned long archtype_read;
//unsigned long free_space_read; // ohne Funktion
//unsigned long new_free_space;
//unsigned long rights;
unsigned long LifeCleaner_effekt_read=0;     //read-buffer für Auswirkung



//*****************************************************************************************//
//RTC
RTC_DS1307 RTC;
//DateTime t;
unsigned long aktuell_time=0;        // buffer für aktuelle zeit
//int con_tag; //puffer um zu bestimmen, welcher tag aktuell läuft 

//*****************************************************************************************//
//Anzeige 

#if lCD_Version == 1
LiquidCrystal_I2C lcd(0x3f,20,4);//Gelb 4 Reihen
int anzeige_groesse=0;
int  LED_B_Pin   = 7;
int  LED_G_Pin  =  6;
int  LED_R_Pin   = 5;
int  LED_GND_Pin=  4;
#endif

#if lCD_Version == 3
LiquidCrystal_I2C lcd(0x27,20,4); //Blau 4 Reihen
int anzeige_groesse=0;
int  LED_B_Pin   = 7;
int  LED_G_Pin  =  6;
int  LED_R_Pin   = 5;
int  LED_GND_Pin=  4;
#endif

#if lCD_Version == 2
LiquidCrystal_I2C lcd(0x3f,16,2); //Gelb 2 Reihen
int anzeige_groesse=1;
int  LED_B_Pin   = 7;
int  LED_G_Pin  =  6;
int  LED_R_Pin   = 5;
int  LED_GND_Pin=  4;
#endif

#if lCD_Version == 4
LiquidCrystal_I2C lcd(0x27,16,2); //Blau 2 Reihen
int anzeige_groesse=1;
int  LED_B_Pin   = 7;
int  LED_G_Pin  =  6;
int  LED_R_Pin   = 5;
int  LED_GND_Pin=  4;
#endif

#if lCD_Version == 5
int anzeige_groesse=0;
int  LED_B_Pin   = 7;
int  LED_G_Pin  =  6;
int  LED_R_Pin   = 5;
int  LED_GND_Pin=  4;
LiquidCrystal_I2C lcd(0x3f,20,4);//Gelb
#endif


int start=0; // anzeige für zeit
bool led_on=1;      //stellt ein ob die pins mit gnd oder 5v starten

int analogeAnzeige_Pin =3;
//int messwert_anzeige;
int t,y;
int oldt=0;
int buzzer_pin =A2;
//int buzzer_pin =A6;


 //FAKE   
 bool fakemodus=false; //false und es ist eine reine raykelle
 int poti_Pin = A3; 
 int Poti_read = 0; 
 int Poti_messwert=0; 
 bool modus=0; // ist "1" dann ist uhr verstellt, leuchte lila und mach nur fake
 

//**********************************Einstellungen******************************************//
unsigned long ray_writing;
int error=0;  //counter für fehlgeschlagene leseversuche RFID
int ergebnis; //counter für fehlerhaft getestete Keys
int feedback; //counter für erfolgreiches testen eines keys
long raywert,raywert2=0;
bool LC_aktiv=0;
int sorte=0;
//*****************************************************************************************//

//*****************************************************************************************//
void setup()
{ 

  Serial.begin(57600);
  SPI.begin(); 
  mfrc522.PCD_Init();

      RTC.begin();
  if (! RTC.isrunning()) {
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }
  


pinMode(LED_B_Pin, OUTPUT);
pinMode(LED_G_Pin, OUTPUT);
pinMode(LED_R_Pin, OUTPUT);
pinMode(LED_GND_Pin, OUTPUT);

pinMode(analogeAnzeige_Pin, OUTPUT);
pinMode(buzzer_pin, OUTPUT);
pinMode(poti_Pin, INPUT);

digitalWrite(LED_B_Pin,!led_on);
digitalWrite(LED_G_Pin,!led_on);
digitalWrite(LED_R_Pin,!led_on);
digitalWrite(LED_GND_Pin,!led_on);
digitalWrite(analogeAnzeige_Pin,LOW);


lcd.init();
lcd.backlight();

}

//*****************************************************************************************//
void loop(){

    DateTime now = RTC.now(); 
    aktuell_time=now.unixtime();
    


if(start==0){ // um einmal die uhrzeit anzuzeigen
   Serial.printf("Momentane Zeit: %4d-%02d-%02d %02d:%02d:%02d", now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second());
      Serial.println();
        lcd.setCursor(0, 0);
        lcd.print(now.year(), DEC);
        lcd.print('/');
        lcd.print(now.month(), DEC);
        lcd.print('/');
        lcd.print(now.day(), DEC);
        lcd.setCursor(0, 1);
        lcd.print(now.hour(), DEC);
        lcd.print(':');
        lcd.print(now.minute(), DEC);
        lcd.print(':');
        lcd.print(now.second(), DEC);
   
    delay(2000);
    lcd.clear();
    
    start=1;
}

 if( aktuell_time<1640991601||aktuell_time > 1893452460){
  Serial.println(F("Uhr ist verstellt"));
   lcd.setCursor(0, 0);
   lcd.print("Uhr ist verstellt");
   
    lcd.clear();
    delay(2000);
modus=1;
 }
 if(anzeige_groesse==0){
   lcd.setCursor(0, 0);
      lcd.print("Rad|Bio|Che|");
      lcd.setCursor(11,1);
      lcd.print("|");
      lcd.setCursor(3,1);
      lcd.print("|");
      lcd.setCursor(7,1);
      lcd.print("|");
      lcd.setCursor(3,2);
      lcd.print("|");
      lcd.setCursor(7,2);
      lcd.print("|");
      lcd.setCursor(11,2);
      lcd.print("|");
      lcd.setCursor(11,3);
      lcd.print("|");
      lcd.setCursor(3,3);
      lcd.print("|");
      lcd.setCursor(7,3);
      lcd.print("|");
 }
    if(anzeige_groesse==1){
       lcd.setCursor(0, 0);
       lcd.print(" Grn|Yel|Red ");   
       lcd.setCursor(4, 1);
       lcd.print("|");  
       lcd.setCursor(8, 1);
       lcd.print("|");  
     
  }
 
// fake modus
Poti_read=analogRead(poti_Pin);
//Serial.print("Analog read:");Serial.println(Poti_read);
Poti_messwert=map( Poti_read,0,1000,0,450);

if(fakemodus==false){Poti_read=0;Poti_messwert=0;}

if(Poti_read==0){
  if(anzeige_groesse==0){
    lcd.setCursor(17, 0);
    lcd.print("   ");
    }
  if(anzeige_groesse==1){
      lcd.setCursor(13, 0);
      lcd.print("   ");
    }  
analoge_anzeige(0);
  if(modus==1){
    digitalWrite(LED_B_Pin,led_on);
    digitalWrite(LED_R_Pin,led_on);
  }

}
if(Poti_read!=0){
  if(anzeige_groesse==0){
    lcd.setCursor(17, 0);
    lcd.print("  M");
  }
  if(anzeige_groesse==1){
      lcd.setCursor(13, 0);
      lcd.print("  M");
    }
anzeige(Poti_messwert);

}
else{
  if(anzeige_groesse==0){
   lcd.setCursor(0, 0);
      lcd.print("Rad|Bio|Che|");
      lcd.setCursor(12, 0);
      lcd.print("    ");
      lcd.setCursor(11,1);
      lcd.print("|");
      lcd.setCursor(3,1);
      lcd.print("|");
      lcd.setCursor(7,1);
      lcd.print("|");
      lcd.setCursor(3,2);
      lcd.print("|");
      lcd.setCursor(7,2);
      lcd.print("|");
      lcd.setCursor(11,2);
      lcd.print("|");
      lcd.setCursor(11,3);
      lcd.print("|");
      lcd.setCursor(3,3);
      lcd.print("|");
      lcd.setCursor(7,3);
      lcd.print("|");
      display_2(0);
  }
    if(anzeige_groesse==1){
       lcd.setCursor(0, 0);
       lcd.print(" Grn|Yel|Red ");   
       lcd.setCursor(4, 1);
       lcd.print("|");  
       lcd.setCursor(8, 1);
       lcd.print("|");  
      display_1(0);
  }
}

  if(modus==0){
//lese modus
  if ( ! mfrc522.PICC_IsNewCardPresent()) {

    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

sorte=Mediread_MFRC522();
if(sorte!=0){
    mfrc522.PICC_HaltA();   //finale stopfunktion
    mfrc522.PCD_StopCrypto1();//finale stopfunktion
}
      
//normal_rfid
 Check_rfid_tag(1,0);
 if( error==0){ //wenn karte sauber gelesen wurde weiter
  
  if( Con_Start_read!=0){ // enthält die karte spielerdaten oder nur fake für plots
 new_ray();
 raywert=raywert2; //ursprünglicher raywert wird durch neuberechneten ersetzt für anzeige

   anzeige(raywert); 

delay(2000);

    mfrc522.PICC_HaltA();   //finale stopfunktion
    mfrc522.PCD_StopCrypto1();//finale stopfunktion
  }

  else if(Con_Start_read==0&&raywert==0){ 
    if(anzeige_groesse==0){
      lcd.setCursor(17, 0);
      lcd.print(" LR");
    }
    if(anzeige_groesse==1){
      lcd.setCursor(13, 0);
      lcd.print(" LR");
    }
      anzeige(raywert);
  Serial.print(F("Leer"));
  Serial.println(F(""));
  /*
     newkey();// falls Dongel bereits eingecheckt
   delay(100);
   key__searchB(56);// falls Dongel noch nicht eingecheckt/ für Dummy-Dongel
    delay(100);
  writing(knownKeys[0],56,Ray_value_intern_read,110000);
 */
delay(2000);

    mfrc522.PICC_HaltA();   //finale stopfunktion
    mfrc522.PCD_StopCrypto1();//finale stopfunktion
  }
else{ //für plotkarten, die nur raywert haben

    if(anzeige_groesse==0){
      lcd.setCursor(17, 0);
      lcd.print("PLT");
    }
    if(anzeige_groesse==1){
      lcd.setCursor(13, 0);
      lcd.print("PLT");
    }
      anzeige(raywert);
  Serial.print(F("Plot-Ray:"));
  Serial.println(raywert);
  
delay(2000);

    mfrc522.PICC_HaltA();   //finale stopfunktion
    mfrc522.PCD_StopCrypto1();//finale stopfunktion
  }

 }
 else{
 // Serial.println(F("Error"));

      mfrc522.PICC_HaltA();   //finale stopfunktion
    mfrc522.PCD_StopCrypto1();//finale stopfunktion
     digitalWrite(LED_R_Pin,!led_on);
 digitalWrite(LED_G_Pin,!led_on);
 digitalWrite(LED_B_Pin,!led_on); 
 error=0;
 }
  }
}

//*****************************************************************************************//  
//*****************************************ENDE********************************************//
//*****************************************************************************************//
