#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h> 


//*****************************************************************************************//
//RFID

    #define SS_PIN 10
    #define RST_PIN 9
    MFRC522 mfrc522(SS_PIN, RST_PIN);


MFRC522::MIFARE_Key key;
#define NR_KNOWN_KEYS   6

unsigned long ergebnisA,ergebnisB; //buffer für Read der Blöcke wird in einer Funktion gefüllt
int last_key= NR_KNOWN_KEYS-1;
int key_used; //Puffer um getesteten Key, numerisch darzustellen
byte id_buffer[4];  
byte knownKeys[NR_KNOWN_KEYS][MFRC522::MF_KEY_SIZE] =  {


    {0xff,0xff,0xff,0xff,0xff,0xff},
    {0x00,0x00,0x00,0x00,0x00,0x00}, 
    {0xFF,0xE6,0xFF,0xFF,0xD1,0xFF},
    {0xa2,0x2c,0x08,0xb0,0x94,0x97},
    {0x00,0x00,0x00,0x13,0x8D,0xF1},
    {0xff,0xff,0xff,0xff,0xff,0xff} // als buffer für neuen Key
    };

//*****************************************************************************************//
 //Ein-/ Ausgabe  
   
  // LiquidCrystal_I2C lcd(0x3f,16,2);int LCD_State= 1; //Gelb 2 Reihen
  //  LiquidCrystal_I2C lcd(0x3f,20,4);int LCD_State= 2; //Gelb 4 Reihen
//   LiquidCrystal_I2C lcd(0x27,16,2);int LCD_State= 1; //Blau 2 Reihen
  // LiquidCrystal_I2C lcd(0x27,20,4);// int LCD_State= 2;//Blau 4 Reihen

    int Poti_read = 0;
    int potPin = A3; 
    int buzzer =A2;
    int buzzertime =0;
    int redPin=7;
    int greenPin=5;
    int bluePin=4;
//**********************************Einstellungen******************************************//

//read
unsigned long Ray_value_intern_read;
unsigned long Ray_value_extern_read;
//read unterfunktionen
//unsigned long ergebnisA,ergebnisB;
unsigned long reading=0;

//allgemeine Prozessvariablen
unsigned long ray_writing;
int error=0;  //counter für fehlgeschlagene leseversuche RFID
int ergebnis; //counter für fehlerhaft getestete Keys
int feedback; //counter für erfolgreiches testen eines keys

unsigned int steps=0;

unsigned int error2=0;
unsigned int error3=0;
unsigned long medi;
unsigned long secure;
unsigned long id;
int kontroll_block=10;

                        
                                                                                                                                                                              
//*****************************************************************************************//
void setup()
{ 
  Serial.begin(57600);
  SPI.begin(); 
  mfrc522.PCD_Init();

  pinMode(buzzer, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(4,LOW);
  digitalWrite(redPin,LOW);
  digitalWrite(greenPin,LOW);
  digitalWrite(bluePin,HIGH);
  randomSeed(analogRead(0));
}

//*****************************************************************************************//
void loop(){
 


if(steps==0){
//ergebnisA,ergebnisB=0;
reading=0;
error=0;
error2=0;
//medi_effekt=0;
//medi=0;
//secure=0;
//art=0;
id=0;
digitalWrite(redPin,LOW);
digitalWrite(greenPin,LOW);
digitalWrite(bluePin,HIGH);


}
               
    if (  mfrc522.PICC_IsNewCardPresent()) {
     
  }else steps=0;    
 
  if (  mfrc522.PICC_ReadCardSerial()) {  
    digitalWrite(buzzer,HIGH);
    delay(100);
    digitalWrite(buzzer,LOW);
  steps=1;
  }
  else {
    steps=0;  return;
    }



if(steps==1){
/*   newkey();// falls Dongel bereits eingecheckt
      delay(100);
      key__searchB(14);// falls Dongel noch nicht eingecheckt/ für Dummy-Dongel
      delay(100);
      rfid_reading(knownKeys[0],56); //56
      Ray_value_intern_read=ergebnisA;
      Ray_value_extern_read=ergebnisB; 
      Serial.print("Ray_value_intern_read:");Serial.println(Ray_value_intern_read);
      Serial.print("Ray_value_extern_read:");Serial.println(Ray_value_extern_read);
      delay(2000);*/
      rfid_reset();
//ray_manipulation(20000);
//delay(2000);
      steps=2;
         
  }

if(steps==2){ 
//digitalWrite(redPin,LOW);
//digitalWrite(greenPin,HIGH);
//digitalWrite(bluePin,LOW);
 
Serial.println("Fertig");
      digitalWrite(buzzer,HIGH);
    delay(100);
    digitalWrite(buzzer,LOW);
delay(2000); 
steps=3;}
           
         if(error3!=0){
            digitalWrite(buzzer,HIGH);
    delay(100);
    digitalWrite(buzzer,LOW);
    delay(100);
      digitalWrite(buzzer,HIGH);
    delay(100);
    digitalWrite(buzzer,LOW);
    delay(100);
      digitalWrite(buzzer,HIGH);
    delay(100);
    digitalWrite(buzzer,LOW);
    
  digitalWrite(redPin,HIGH);
  Serial.println("Fehler");
      delay(500); 
    
      steps=3;
  }
    
 if(steps==3){
 
  digitalWrite(redPin,LOW); 
  digitalWrite(bluePin,LOW); 
  digitalWrite(greenPin,LOW); 
  error3=0;
      mfrc522.PICC_HaltA();
      mfrc522.PCD_StopCrypto1(); 
      steps=0;
  }



}

//*****************************************************************************************//
