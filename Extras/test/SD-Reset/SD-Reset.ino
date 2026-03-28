/*
  Listfiles

  This example shows how print out the files in a
  directory on a SD card

  The circuit:
   SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4 (for MKRZero SD: SDCARD_SS_PIN)

  created   Nov 2010
  by David A. Mellis
  modified 9 Apr 2012
  by Tom Igoe
  modified 2 Feb 2014
  by Scott Fitzgerald

  This example code is in the public domain.

*/
#include <SPI.h>
#include <SD.h>
File konfigFile;  //Konfigimportdatei
File root;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
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
   konfigFile.print("*FALLEN2025*1745971200*0*60*4*48*48*48*2*1*24*3*1*25*25*3*1*75*75*2*2*10*15*6*2*");
 //  konfigFile.print("*FALLEN2024*1707298223*0*60*4*48*30*30*3*1*24*5*1*20*20*3*3*70*70*2*2*10*10*6*6*");
   konfigFile.println("");
   konfigFile.close();
   }
   Serial.println("Konfig geschrieben");
  Serial.println("done!");
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
