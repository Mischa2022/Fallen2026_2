

#include <LiquidCrystal_I2C.h>
#include <RTClib.h>
#include <TimeLib.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h> 
#include <TM1637Display.h>
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

//Blöcke 2022
//*************************************************************************************//
                                              //Bereich a                 Bereich b
#define Admin1_block                    58    //Con_Start_read            Last_Booking_read    
#define Admin2_block                    57    //LifeCleaner_effekt_read   archtype_read
#define Ray_block                       56    //Ray_value_intern_read     Ray_value_extern_read (unser Raywert für äussere)


// Ausgaben / Pufferwerte die durch Check_RFID gefüllt werden
//*************************************************************************************//
unsigned long Con_Start_read;
unsigned long Last_Booking_read;
unsigned long Ray_value_intern_read;
unsigned long Ray_value_extern_read;
unsigned long archtype_read;
//unsigned long free_space_read; // ohne Funktion
//unsigned long new_free_space;
//unsigned long rights;
unsigned long LifeCleaner_effekt_read=0;     //read-buffer für Auswirkung



//*****************************************************************************************//
//RTC
RTC_PCF8563 RTC;
//DateTime t;
unsigned long aktuell_time=0;        // buffer für aktuelle zeit
//int con_tag; //puffer um zu bestimmen, welcher tag aktuell läuft 
int old_min=0;
//*****************************************************************************************//
//Dominik
/*
int  LED_B_Pin   = 7;
int  LED_G_Pin  =  6;
int  LED_R_Pin   = 5;
int  LED_GND_Pin=  4;
LiquidCrystal_I2C lcd(0x3f,20,4);//Gelb
*/
//Anzeige 
#define CLK 4
#define DIO 5
LiquidCrystal_I2C lcd(0x27,16,2); 
TM1637Display display(CLK, DIO);     

int LED1_Pin=A0;
int LED2_Pin=A1;
int LED3_Pin=A2;




int start=0; // anzeige für zeit
//bool led_on=1;      //stellt ein ob die pins mit gnd oder 5v starten

int analogeAnzeige_Pin =3;
//int messwert_anzeige;
int t,y;
int oldt=0;
int buzzer_pin =6;
//int buzzer_pin =A6;


 //FAKE   
 bool fakemodus=true; //false und es ist eine reine raykelle
 int poti_Pin = A3; 
 int Poti_read = 0; 
 int Poti_messwert=0; 
 bool modus=0; // ist "1" dann ist uhr verstellt, leuchte lila und mach nur fake
 
bool spass=0;
int song;

byte known_id[2][4]={
    {0x96, 0x92, 0x65, 0x2A},
   // {0xE0, 0x5D, 0xBD, 0xC4}
    {0x2C,0x33,0x98,0xD2}
    };
byte id_buffer[4];  
bool known =false; 
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

  Serial.begin(9600);
  SPI.begin(); 
  mfrc522.PCD_Init();
  lcd.init();// keine Ahnung wofür ich das drin lassen muss

/*
 RTC.writeSqwPinMode(PCF8563_SquareWave1HZ); 
if ( RTC.initialized()) {
                
//                  Jahr ,Monat,Tag, Stunde, Min,Sek
RTC.adjust(DateTime(2023, 3, 21, 17, 19, 0));

}
if ( !RTC.initialized()) {
  
//                  Jahr ,Monat,Tag, Stunde, Min,Sek
RTC.adjust(DateTime(2023, 3, 21, 17, 19, 0));
        }      
  */

  pinMode(LED1_Pin, OUTPUT);
  pinMode(LED2_Pin, OUTPUT);
  pinMode(LED3_Pin, OUTPUT);


pinMode(analogeAnzeige_Pin, OUTPUT);
pinMode(buzzer_pin, OUTPUT);
pinMode(poti_Pin, INPUT);


digitalWrite(analogeAnzeige_Pin,LOW);

  digitalWrite(LED1_Pin,LOW);
  digitalWrite(LED2_Pin,LOW);
  digitalWrite(LED3_Pin,LOW);


}

//*****************************************************************************************//
void loop(){
randomSeed(analogRead(0));
display.setBrightness(0x0f);  
  spass=0;
  song = 0;
    DateTime now = RTC.now(); 
    aktuell_time=now.unixtime();
    
 if( aktuell_time<1640991601||aktuell_time > 1893452460){
  Serial.println("Uhr ist verstellt");
 //  lcd.setCursor(0, 0);
 //  lcd.print("Uhr ist verstellt");

modus=1;
 }    
 
//raywert=0;
//raywert2=0;

if(old_min!=now.minute()){

random_SEG(300,10);

old_min=now.minute();
}
  display.showNumberDecEx(now.hour(),0b11100000,true,2,0);
 display.showNumberDec(now.minute(),true,2,2);
 
// fake modus
if(fakemodus==false){
  Poti_read=0;Poti_messwert=0;
}
else{
  
Poti_read=analogRead(poti_Pin);
Serial.print("Analog read:");Serial.println(Poti_read);
Poti_messwert=map( Poti_read,0,1000,0,450);

  if(Poti_read>20){

    anzeige(Poti_messwert);
    //display.clear();
    //display.showNumberDec(Poti_messwert,false);
    }
  else{
    analoge_anzeige(0);
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
     for (byte j = 0; j < mfrc522.uid.size; j++) {
                id_buffer[j]=mfrc522.uid.uidByte[j];
                }
                /*
      Serial.print(id_buffer[0],HEX);Serial.print(" | ");
      Serial.print(id_buffer[1],HEX);Serial.print(" | ");
      Serial.print(id_buffer[2],HEX);Serial.print(" | ");
      Serial.println(id_buffer[3],HEX);*/
sorte=Mediread_MFRC522();
if(sorte!=0){
      mfrc522.PICC_HaltA();   //finale stopfunktion
    mfrc522.PCD_StopCrypto1();//finale stopfunktion
}
            
//lala_modus

int x=0;
if(memcmp(id_buffer, known_id[0], sizeof(id_buffer)) == 0){
                known=!known;x=1;delay(500);
                }
if(memcmp(id_buffer, known_id[1], sizeof(id_buffer)) == 0){
                known=!known;x=2;delay(500);
                }  
  
  if(known==true){
    sing(x);
    spass=1;
    known=!known;
  }
  
//normal_rfid
 Check_rfid_tag(1,0);
 if( error==0&&spass==0){ //wenn karte sauber gelesen wurde weiter
  
  if( Con_Start_read!=0){ // enthält die karte spielerdaten oder nur fake für plots
 new_ray();
 raywert=raywert2; //ursprünglicher raywert wird durch neuberechneten ersetzt für anzeige
// Serial.print("Spieler :");   Serial.println(raywert);

   anzeige(raywert); 
       display.clear();
   display.showNumberDec(raywert,false);
delay(2000);

    mfrc522.PICC_HaltA();   //finale stopfunktion
    mfrc522.PCD_StopCrypto1();//finale stopfunktion
  }

  else if(Con_Start_read==0&&raywert==0){ 

      anzeige(raywert);
   display.clear();
   display.showNumberDec(raywert,false);
  Serial.print("Leer");
  Serial.println("");
  
delay(2000);

    mfrc522.PICC_HaltA();   //finale stopfunktion
    mfrc522.PCD_StopCrypto1();//finale stopfunktion
  }
else{ //für plotkarten, die nur raywert haben
  //  Serial.print("PLOT: ");       Serial.println(raywert);

      anzeige(raywert);
   display.clear();
   display.showNumberDec(raywert,false);
  Serial.print("Plot-Ray:");
  Serial.println(raywert);
  
delay(2000);

    mfrc522.PICC_HaltA();   //finale stopfunktion
    mfrc522.PCD_StopCrypto1();//finale stopfunktion
  }

 }
 else{
 // Serial.println("Error");

      mfrc522.PICC_HaltA();   //finale stopfunktion
    mfrc522.PCD_StopCrypto1();//finale stopfunktion
   digitalWrite(LED1_Pin,LOW);
 digitalWrite(LED2_Pin,LOW);
 digitalWrite(LED3_Pin,LOW);
 error=0;
 }
}
}

//*****************************************************************************************//  
//*****************************************ENDE********************************************//
//*****************************************************************************************//
