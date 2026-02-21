
#include <Wire.h>
#include <SPI.h>
#include <MFRC522.h>
#include <TimeLib.h>
#include <RTClib.h>
#include <SD.h>
#include <EEPROM.h>
#include <MD5.h>
#include <Servo.h>


//HARDWARE
//*************************************************************************************//
char*Terminalname = "Rayomatic 1";
char*geraete_id="Ray_FS_1";

int erster_buchungstag=1; //0 gleich anreise //1 gleich ab ersten spieltag

//RFID
#define RST_PIN         7     //neue Platine      
#define SS_PIN          13    //neue Platine        
//SD
const int chipSelect = 31;//neue Platine  

//LED
const int ledPin1 = 33; //neue Platine  // A2 Dongel anwesend? "An" ansonsten "Aus"
const int ledPin2 = 35; //neue Platine  // nur für meine Spielhardware

//Relais
int relaisPin[] ={A11,A5,A7,A9}; //reihenfolge muss getestet werden
//int relaisPin[] ={A11,A9,A7,A5};//reihenfolge muss getestet werden
bool geschaltet =1; //1=invertiert on / off der Relais
long wartezeit =5000; // Wartezeit nach schalten der Relais, bis es weiter geht.

// buzzer
const int buzzer_pin = A1; //neue Platine
//
long intervall=5000; //Wartezeit nach einlegen des Spielerdongels und automatisch weitermachen und nicht mehr warten auf Medi

// Servo
Servo myservo_anzeige;
Servo myservo_wippe;

#define tresor          45
#define geschlossen     90
#define rueckgabe        135
int servo_value; //puffer für wippe

//Con_Spezifikationen // werden über Konfig gefüllt
//*************************************************************************************//
String basis_konfig ="*FALLEN2024*1710925200*0*60*5*48*30*30*6*6*24*5*1*20*20*6*6*70*70*2*2*10*10*6*6*";
String basis2[26];

String neu_konfig;//für konfig import
String neu[26];//für konfig import
bool warten = false;//für konfig import


String Con_Name=""; //Beispiel Conname, wird normalerweise aus der Konfig gefüllt
unsigned long con_start_time;        // con-startzeit wird über Konfig gefüllt.
unsigned long tagesdosis; 
unsigned long konfig_time;
int anzahl_tage; //für bestimmung aktuellen Tag 0=Anreisetag, 1=erster Spieltag usw. wird durch konfig gefüllt bedeutet maximal 5 spieltage ohne anreisetag
int UTC; // Zeitzone, wird durch Konfig gefüllt und muss nun wieder aktiv genutzt werden 2=Sommer 1=Winter unixtime wird mit 0 ausgegeben

//Con_Spezifikationen // werden nicht über Konfig gefüllt 
//*************************************************************************************//
unsigned long minimum_ray_writing =10000UL;  //minimum Raywert der beim Schreiben nicht unterschritten werden darf
unsigned long maximum_ray_writing =450000UL; //maximum Raywert der beim Schreiben nicht überschritten werden darf

//RFID
//*************************************************************************************//
//PN532
 #include <PN532_I2C.h>
 #include <PN532.h>
 PN532_I2C pn532i2c(Wire);
 PN532 nfc(pn532i2c);  
 unsigned long ergebnisA2,ergebnisB2; //puffer für gelesene Werte
 bool reader=false; //um Lesen zu starten

//MFRC522
MFRC522 mfrc522(SS_PIN, RST_PIN);   
MFRC522::MIFARE_Key key;
#define NR_KNOWN_KEYS   6

unsigned long ergebnisA,ergebnisB; //buffer für Read der Blöcke wird in einer Funktion gefüllt
int last_key= NR_KNOWN_KEYS-1;
int key_used; //Puffer um getesteten Key, numerisch darzustellen
byte knownKeys[NR_KNOWN_KEYS][6] =  {
    
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
#define Cleanray1_block                 38    //BloodClean_read[0]        BloodClean_read[1]
#define Cleanray2_block                 37    //BloodClean_read[2]        BloodClean_read[3]
#define Cleanray3_block                 36    //BloodClean_read[4]        BloodClean_read[5]

//Blöcke und Werte 2019
//*************************************************************************************//
#define Old_Ray_value_intern_read_block_2019 13   //Roys System alte Blöcke
#define constart_block_2019              8        //Roys System alte Blöcke
unsigned long Old_Ray_value_intern_read2019;
unsigned long Con_Start_read2019;

// Ausgaben / Pufferwerte die durch Check_RFID gefüllt werden
//*************************************************************************************//
unsigned long Con_Start_read;
unsigned long Last_Booking_read;
unsigned long Ray_value_intern_read;
unsigned long Ray_value_extern_read;
unsigned long archtype_read;
unsigned long free_space_read; // ohne Funktion
unsigned long new_free_space;
unsigned long rights;
unsigned long LifeCleaner_effekt_read;     //read-buffer für Auswirkung
unsigned long NanoClean_read[4]; 
unsigned long Dekon_read[6]; 
unsigned long LifeCleaner_read[6];
unsigned long Cleanray_read[6];
unsigned long BloodClean_read[6];

//Puffer für Medis und ihre Auswirkungen wird durch Konfig und Check_rfid gefüllt
//*************************************************************************************//
unsigned long Dekon;  // variable für Ray-Abzug Einnahme Dekon
int Dekon_min_effekt;
int Dekon_max_effekt;
int Dekon_per_day; 
int Dekon_per_con;    
int Dekoncounter_thisday=0;
int Dekoncounter_allday=0;

unsigned long NanoClean; // variable für Ray-Abzug Einnahme Nanoclean
int Nanoclean_min_effekt;
int Nanoclean_max_effekt;
int Nano_per_day;   
int Nano_per_con; 
int Nanocounter_thisday=0;
int Nanocounter_allday=0;

unsigned long LifeCleaner; // variable für Ray-Abzug Einnahme Lifecleaner --> aktuell 0
unsigned long LifeCleaner_buffer;  //(XStunden *60Min*60Sekunden) 
int Lifecleaner_min_effekt=0;//weil keinen Effekt auf Ray-Wert ist aber als Variable möglich
int Lifecleaner_max_effekt=0;//weil keinen Effekt auf Ray-Wert ist aber als Variable möglich
int LifeCleaner_per_day;    
int Life_per_con;  
int Lifecounter_thisday=0;
int Lifecounter_allday=0;

unsigned long Cleanray;// variable für Ray-Abzug Einnahme Cleanray
int Cleanray_min_effekt;
int Cleanray_max_effekt;
int Clean_per_day; 
int Clean_per_con;
int Cleancounter_thisday=0;
int Cleancounter_allday=0;

unsigned long BloodClean; // variable für Ray-Abzug Einnahme Blutwäsche
int Bloodclean_min_effekt;
int Bloodclean_max_effekt;
int Blood_per_day; 
int Blood_per_con;   
int Bloodcounter_thisday=0;
int Bloodcounter_allday=0;

unsigned long Drawback;// variable für Ray-Aufschlag Einnahme Drawbackmarke
int Drawback_min_effekt= 10; //fehlt noch in der Konfig
int Drawback_max_effekt=15;  //fehlt noch in der Konfig

// SD / Ausgaben
//*************************************************************************************//
File konfigFile;
File buchunglog;
File checkinlog;
File medilog;     // Datei zum Speichern der Mengen an Medibuchungen um sie später auszuwerten beim Einsammeln
#define max_read  26

unsigned long Speicherwerte_Konfig [max_read-1]; //für lesen von sd, zum ablegen EEPROM
unsigned long Speicherwerte_Konfigread [max_read-1]; // für auslesen aus EEPROM

String text="";
String txt[max_read];
String kontrolle="";
String kontroll_key;
char Puffer[11];
char*msg0;
char*msg1;  //Hauptbemerkung im Display wenn Prozess durch
char*msg2;  //Nebenbemerkung zbs " Ray:"
char*msg3;  //Wertausgabe auf dem Display
char*msg4;
char*buchungsgrund;
char*buchungsgrund2;
int konfig_check =0;
int typus=0;

int Menge_Dekon=0;      //Ablage für Mengen gebuchter Medis
int Menge_Nanoclean=0;  //Ablage für Mengen gebuchter Medis
int Menge_Life=0;       //Ablage für Mengen gebuchter Medis
int Menge_Clean=0;      //Ablage für Mengen gebuchter Medis
int Menge_Blood=0;      //Ablage für Mengen gebuchter Medis
int Menge_Draw=0;       //Ablage für Mengen gebuchter Medis

//RTC
//*************************************************************************************//
RTC_DS3231 rtc;
DateTime t;
unsigned long rest_time;         // restliche sekunden um con-start auf 24:00 aufzufüllen als erst buchung, wichtig für Ray-O-Mat
unsigned long UNIX_korrektur=3600;
unsigned long aktuell_time;        // buffer für aktuelle zeit
int con_tag; //puffer um zu bestimmen, welcher tag aktuell läuft 

//Serielle Kommunikation
//*************************************************************************************//
#define anzahl_werte 11
unsigned long wert=0;
unsigned long ziel_long=0;
String read_String = "";
String read_String2 = "";
char ziel_char=' '; //nachdem auswerten dieses chars, muss unbedingt ' ' wieder gesetzt werden
char char_read[anzahl_werte];
int werte[anzahl_werte];
int counter=0;
bool stringComplete = false;  
bool flow=0;

//Fehlerzähler & Rechenhilfen
//*************************************************************************************//
unsigned long ray_writing;
int error=0;  //counter für fehlgeschlagene leseversuche RFID
int ergebnis; //counter für fehlerhaft getestete Keys
int feedback; //counter für erfolgreiches testen eines keys

//Medi_read
int sorte=0;
unsigned long previousMillis=0;
int test =0;
long raywert;
//*************************************************************************************//

void setup() {
pinMode(buzzer_pin, OUTPUT);
pinMode(ledPin1, OUTPUT);
pinMode(ledPin2, OUTPUT);
pinMode(relaisPin[0], OUTPUT);
pinMode(relaisPin[1], OUTPUT);
pinMode(relaisPin[2], OUTPUT);
pinMode(relaisPin[3], OUTPUT);
digitalWrite(ledPin1,LOW);
digitalWrite(ledPin2,LOW);
digitalWrite(relaisPin[0],geschaltet);
digitalWrite(relaisPin[1],geschaltet);
digitalWrite(relaisPin[2],geschaltet);
digitalWrite(relaisPin[3],geschaltet);
myservo_anzeige.attach(10);
myservo_wippe.attach(12);

randomSeed(analogRead(0));

Serial.begin(57600); 
Wire.begin();        
rtc.begin();
SPI.begin();
mfrc522.PCD_Init(); 

nfc.begin();
nfc.SAMConfig();

//LED-Testscenario

digitalWrite(ledPin1,HIGH);
delay(500);
digitalWrite(ledPin2,HIGH);
delay(500);
digitalWrite(relaisPin[0],!geschaltet);
delay(500);
digitalWrite(relaisPin[1],!geschaltet);
delay(500);
digitalWrite(relaisPin[2],!geschaltet);
delay(500);
digitalWrite(relaisPin[3],!geschaltet);
delay(500);
digitalWrite(ledPin1,LOW);
delay(500);
digitalWrite(ledPin2,LOW);
digitalWrite(relaisPin[0],geschaltet);
delay(500);
digitalWrite(relaisPin[1],geschaltet);
delay(500);
digitalWrite(relaisPin[2],geschaltet);
delay(500);
digitalWrite(relaisPin[3],geschaltet);
//buzzer_play( 10,300);

/*
myservo_wippe.write(45);
delay(2000);
myservo_wippe.write(90);
delay(2000);
myservo_wippe.write(135);
delay(2000);
*/

initialisierung2();
   
t = rtc.now();      
aktuell_time=t.unixtime();
rest_time=86400- ((con_start_time+(UTC*UNIX_korrektur))%86400); 


uhr_pruefen(aktuell_time);


      Serial.println();  
      Serial.println("Nun Dongel auflegen");
      Serial.println();
}

void loop() {
  main_rayomat_1();
 //   main_rayomat_2();
}
