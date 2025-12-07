#include <Adafruit_NeoPixel.h>

#include <stdlib.h> 
#include <string.h>
#include <RTClib.h>
#include <TimeLib.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h> 

//*****************************************************************************************//

unsigned long malus = 20;
unsigned long malus_betrag;

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

byte id_buffer[4];  

//Blöcke 2022
//*************************************************************************************//
                                              //Bereich a                 Bereich b
#define Admin1_block                    58    //Con_Start_read            Last_Booking_read    
#define Admin2_block                    57    //LifeCleaner_effekt_read   archtype_read
#define Admin3_block                    56    //Con-Ende                  Ray_value_extern_read (unser Raywert für äussere)


// Ausgaben / Pufferwerte die durch Check_RFID gefüllt werden
//*************************************************************************************//
unsigned long Con_Start_read;
unsigned long Con_End_read;
unsigned long Last_Booking_read;
unsigned long Ray_value_intern_read;
unsigned long Ray_value_extern_read;
unsigned long archtype_read;
unsigned long LifeCleaner_effekt_read=0;     //read-buffer für Auswirkung

unsigned long minimum_ray_writing =10000UL;  //minimum Raywert der beim Schreiben nicht unterschritten werden darf
unsigned long maximum_ray_writing =450000UL; //maximum Raywert der beim Schreiben nicht ueberschritten werden darf

//*****************************************************************************************//
//RTC
RTC_DS1307 RTC;
//DateTime t;
unsigned long aktuell_time=0;        // buffer für aktuelle zeit


//*****************************************************************************************//

//Anzeige 

int start=0; // anzeige für zeit
int t,y;
int oldt=0;
int buzzer_pin =A2;

#define PIN1   A3 
int NUMPIXELS  = 1; 

Adafruit_NeoPixel pixels(NUMPIXELS, PIN1, NEO_GRB + NEO_KHZ800);


 
int malus_pin =A1;
 bool modus=0; // ist "1" dann ist uhr verstellt, leuchte lila 
 bool schalter=0; //für malusbuchung

int tagesdosis=48;
int UTC=1;
unsigned int anzahl_tage_maximal=4; // Geigerzähler arbeiten maximal diese Anzahl an Tagen weiter mit Spielerdongel
unsigned long rest_time;


//**********************************Einstellungen******************************************//
unsigned long ray_writing;
int error=0;  //counter für fehlgeschlagene leseversuche RFID
int ergebnis; //counter für fehlerhaft getestete Keys
int feedback; //counter für erfolgreiches testen eines keys
long raywert,raywert2=0;
bool LC_aktiv=0;
int sorte=0;

int main_error=0;
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
  //RTC.adjust(DateTime(2024, 11, 4, 10, 0, 0));

pinMode(buzzer_pin, OUTPUT);
pinMode(malus_pin, INPUT); 
  pixels.begin(); 

}

//*****************************************************************************************//
void loop(){

  if(schalter==1){ // malus schreiben an
      pixels.setPixelColor(0,pixels.Color(0, 50, 50));
      pixels.show();
    }
  else{
      pixels.setPixelColor(0,pixels.Color(0, 0, 0));
      pixels.show();        
    }

    DateTime now = RTC.now(); 
    aktuell_time=now.unixtime();
    
  if(digitalRead(malus_pin)==HIGH){
      schalter=!schalter;
      delay(1000);
    }

 if( aktuell_time<1640991601||aktuell_time > 1893452460){
    Serial.println("Uhr ist verstellt");
    pixels.setPixelColor(0,pixels.Color(50, 0, 50));
    pixels.show();
    delay(1000);
    modus=1;
    }
    
  if(modus==0){ //lese modus wenn alles ok ist
  
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

// Medi-Erkennung
sorte=Mediread_MFRC522();

  if(sorte!=0){
    buzzer_play(1,100); 
    pixels.setPixelColor(0,pixels.Color(50,50, 50));
    pixels.show();
    delay(1000);
    mfrc522.PICC_HaltA();   //finale stopfunktion
    mfrc522.PCD_StopCrypto1();//finale stopfunktion
    }

//normal_rfid
  Check_rfid_tag();
 if( error==0){ //wenn karte sauber gelesen wurde weiter
        buzzer_play(1,100); 
        
         if( Con_Start_read!=0&& schalter==0){ // enthält die karte spielerdaten oder nur fake für plots
              Serial.println("only reading");
              new_ray();
              raywert=raywert2; //ursprünglicher raywert wird durch neuberechneten ersetzt für anzeige
              anzeige(raywert); 
              delay(1000);          
              mfrc522.PICC_HaltA();   //finale stopfunktion
              mfrc522.PCD_StopCrypto1();//finale stopfunktion
            }
      
        else if( Con_Start_read!=0&& schalter==1){ // enthält die karte spielerdaten oder nur fake für plots
          Serial.println("reading & writing");
          new_ray();
          raywert=raywert2; //ursprünglicher raywert wird durch neuberechneten ersetzt für anzeige
          malus_betrag=(malus+raywert2)*1000;
          Serial.print("was ich gerne schreiben moechte:");Serial.println(malus_betrag);
          ray_manipulation(malus_betrag);

            if(main_error!=0){
              pixels.setPixelColor(0,pixels.Color(50, 0, 50));
              pixels.show();
              buzzer_play(10,100); 
              mfrc522.PICC_HaltA();   //finale stopfunktion
              mfrc522.PCD_StopCrypto1();//finale stopfunktion
              }
            else{
              malus_betrag=malus_betrag/1000;
              anzeige(malus_betrag); 
              }

          mfrc522.PICC_HaltA();   //finale stopfunktion
          mfrc522.PCD_StopCrypto1();//finale stopfunktion
          
        }
      
      // für leere Karten
        else if(Con_Start_read==0&&raywert==0){ 
          
           pixels.setPixelColor(0,pixels.Color(50,50, 50));
           pixels.show();
           delay(1000);
           Serial.print("Leer");
           Serial.println("");
           delay(1000);
           mfrc522.PICC_HaltA();   //finale stopfunktion
           mfrc522.PCD_StopCrypto1();//finale stopfunktion
          }
      else{ //für plotkarten, die nur raywert haben
      
      
        anzeige(raywert);
        Serial.print("Plot-Ray:");
        Serial.println(raywert);
        delay(1000);
        mfrc522.PICC_HaltA();   //finale stopfunktion
        mfrc522.PCD_StopCrypto1();//finale stopfunktion
        }
       }
 else{


 mfrc522.PICC_HaltA();   //finale stopfunktion
 mfrc522.PCD_StopCrypto1();//finale stopfunktion

 error=0;
 main_error=0;
  }
  main_error=0;
 }
  main_error=0;
}

//*****************************************************************************************//  
//*****************************************ENDE********************************************//
//*****************************************************************************************//
