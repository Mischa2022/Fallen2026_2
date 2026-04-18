
#include <TimeLib.h>
#include <RTClib.h>
#include <SPI.h>
#include <SD.h>
File konfigFile;  //Konfigimportdatei
File modus;
File root;
String basis_konfig ="*FALLENtest*1776419776*0*60*4*48*48*48*2*1*24*3*1*25*25*3*1*75*75*2*2*10*15*6*2*";
RTC_DS3231 rtc;
DateTime t;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  rtc.begin();
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing SD card...");

  if (!SD.begin(31)) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");

  root = SD.open("/");

  printDirectory(root, 0);

 SD.remove("medi.txt");
  delay(500);
   SD.remove("Konfig.txt");
  delay(500);
  SD.remove("clog.txt");
  delay(500);
  SD.remove("blog.txt");
  delay(500);

   konfigFile = SD.open("Konfig.txt", FILE_WRITE);
   if (konfigFile) {
  
   konfigFile.print(basis_konfig);
 //  konfigFile.print("*FALLEN2024*1707298223*0*60*4*48*30*30*3*1*24*5*1*20*20*3*3*70*70*2*2*10*10*6*6*");
   konfigFile.println("");
   konfigFile.close();
   }
   Serial.println("Konfig geschrieben");
  Serial.println("done!");

     modus = SD.open("moduslog.txt", FILE_WRITE);
   if (!modus) {
      modus = SD.open("modus.txt", FILE_WRITE);
      modus.println(0);
  modus.close();
   }
   Serial.println("Modus geschrieben");
  Serial.println("done!");


    if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }
      DateTime now = rtc.now();
    
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
}

void loop() {
 
}

void printDirectory(File dir, int numTabs) {
  while (true) {

    File entry =  dir.openNextFile();
    if (! entry) {
      // no more files
      break;
    }
    for (uint8_t i = 0; i < numTabs; i++) {
      Serial.print('\t');
    }
    Serial.print(entry.name());
    if (entry.isDirectory()) {
      Serial.println("/");
      printDirectory(entry, numTabs + 1);
    } else {
      // files have sizes, directories do not
      Serial.print("\t\t");
      Serial.println(entry.size(), DEC);
    }
    entry.close();
  }
}
