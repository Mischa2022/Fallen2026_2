/*Auflistung Unterfunktionen, die fuer SD-Karten_Reeader benoetigt werden
 * 

 * cut                        //  2025 unterfunktion
 * split                      //  2025 unterfunktion
 * read_konfig_out_of_string  //  2025 auslesen von konfigdaten aus einem String
 * initialisierung2()         //  2025 ueberpruefung ob sd_reader funktioniert und ob neue konfig verfuegbar, sonst laden der bestehenden konfig
 * checkinlog()               //  2025 speichert die werte und zeiten des checkins 
 * booking_save()             //  2025 speichert die werte und zeiten von Medikamentenbuchungen 
 * check_medi_log()           //  2025 Funktion um den Buchungsstand zu laden. Also wieviele Medis wurden bisher gebucht
 * write_medi_log()           //  2025 Funktion zum speichern der Medibuchungen
 */

void cut(String Start, String Ziel[max_read], char trenner ) {


  for (int x = 0; x < max_read; x++) {
    Ziel[x] = split(Start, trenner, x + 1);
    /*
    if (x == max_read - 1) {
      kontroll_key = txt[x];
   //   Serial.print( "Kontrollwert SD:");
   //   Serial.println( txt[x]);
    }*/
    if (x != max_read - 1) {
       
      Speicherwerte_Konfig[x] = Ziel[x].toInt();
    
      //Dump zur Hilfe
     // Serial.println( Speicherwerte_Konfig[x]);
    }
  }
}

//*****************************************************************************************//

String split(String s, char parser, int index) {
  String rs = "";
  int parserIndex = index;
  int parserCnt = 0;
  int rFromIndex = 0, rToIndex = -1;
  while (index >= parserCnt) {
    rFromIndex = rToIndex + 1;
    rToIndex = s.indexOf(parser, rFromIndex);
    if (index == parserCnt) {
      if (rToIndex == 0 || rToIndex == -1) return "";
      return s.substring(rFromIndex, rToIndex);
    } else parserCnt++;
  }
  return rs;
}
//*****************************************************************************************//

void read_konfig_out_of_string(String basis[]) {

Con_Name = basis[0];

Con_Name.toCharArray(conname,11);

  konfig_time = basis[1].toInt();
  
      //con_start_time=konfig_time+(2*86400); //fuer tests bei verschiedenen startwerten
      con_start_time=konfig_time;
      
      UTC =basis[2].toInt();
      //UNIX_korrektur = basis[3]*60; // ist nun festgesetzt
      anzahl_tage=basis[4].toInt();// minuswert nur zum testen von konfigdaten
      tagesdosis=basis[5].toInt(); 
      con_end_time=con_start_time+(86400*anzahl_tage);
      Clean_per_day=basis[9].toInt(); 
      Clean_per_con=basis[8].toInt(); 
      Cleanray_min_effekt=basis[6].toInt();
      Cleanray_max_effekt=basis[7].toInt();
                           
      LifeCleaner_per_day=basis[12].toInt(); 
      Life_per_con=basis[11].toInt();    
      LifeCleaner_buffer=(basis[10].toInt()*3600);  //(XStunden *60Min*60Sekunden)        
             
      Blood_per_day=basis[16].toInt();
      Blood_per_con=basis[15].toInt();           
      Bloodclean_min_effekt=basis[13].toInt();
      Bloodclean_max_effekt=basis[14].toInt();
                   
      Nano_per_day=basis[20].toInt();
      Nano_per_con=basis[19].toInt(); 
      Nanoclean_min_effekt=basis[17].toInt();
      Nanoclean_max_effekt=basis[18].toInt();
                            
      Dekon_per_day=basis[24].toInt();                                
      Dekon_per_con=basis[23].toInt();                     
      Dekon_min_effekt=basis[21].toInt();
      Dekon_max_effekt=basis[22].toInt();
/*
        Serial.println(con_start_time);
      for(int x=0;x<25;x++){
        Serial.println(basis[x]);
      }*/
      
}

//*****************************************************************************************//

void initialisierung2() {
  char read_Char4;  //konfig import sd
    Serial.println(F("Initialisierung"));

  //keine SD-Karte
  if (!SD.begin(chipSelect)) {
    Serial.println(F("SD-Karte nicht ok"));
    //Serial.write('\n');delay(write_pause);
    
    while (1);
  }

  moduslog = SD.open("moduslog.txt");
 if (moduslog) {
    while (moduslog.available()) {
        moduslog.seek(0);
        modusbuffer[0] =moduslog.read()-'0'; 
        modus=modusbuffer[0];
        lcd.setCursor(0, 0);
        
   if (modus==0){
    Serial.println(F("Godzilla"));
    
    Serial2.print("y");Serial2.print(modus);Serial2.write('\n');
    locked=false;

    }    
   if (modus==1){
    
    Serial.println(F("Checkin"));
    
    Serial2.print("y");Serial2.print(modus);Serial2.write('\n');
    locked=false;
    }  
   if (modus==2){
    
    Serial.println(F("Buchung"));
    
    Serial2.print("y");Serial2.print(modus);Serial2.write('\n');
    locked=true;
    }     
      moduslog.close();                       
    }
                        
   }
     else {
     modus=0;
     myprint("moduslog.txt nicht vorhanden","","",true,true,false,1,port);
     }
     /*
     if (SD.exists("konfig.txt")) {
      SD.remove("konfig.txt");
      delay(100);
     }*/
  Serial.println(F("SD-Karte ok"));       
   if (SD.exists("konfig.txt")) {
        Serial.print(F("Konfig auf SD gefunden :"));
       File dataFile = SD.open("konfig.txt", FILE_READ);

        if (dataFile) {
        while (dataFile.available()) {
              read_Char4 = (char)dataFile.read();
        
          if (read_Char4 != '\n') {
             neu_konfig += read_Char4;
             
            }
            
          else{
            Serial.println(neu_konfig);
            dataFile.close();
            cut(neu_konfig, neu, '*');
            delay(100);
            read_konfig_out_of_string(neu);
            }
        }
        Serial.println();
        } 
      }
      else{
        Serial.println(F("Konfig nicht auf SD gefunden"));

          cut(basis_konfig, basis2, '*');
          /* for (int y = 0; y < 25; y++) {
              Serial.print(y);Serial.print(" ");
              Serial.print(bereich_name[y]);
              Serial.println( basis[y]); 
              delay(10);
          }*/
          read_konfig_out_of_string(basis2);
      }
//Reader-Check
   bool test = mfrc522.PCD_PerformSelfTest(); // perform the test
 
  if (!test){
    myprint("RFID-Reader nicht verfügbar","","",true,true,false,1,0);
    while (1);
  }
  Serial.println(F("Reader ok"));  
//Uhrcheck
  if( aktuell_time<(con_start_time-432000)||aktuell_time > 1893452460){
 // Serial.print("Con_start_time:");Serial.println(con_start_time);
  myprint("Uhr ist verstellt","","",true,true,false,1,0);
  while (1);
 }
 Serial.println(F("Uhr ok"));

  }



//*****************************************************************************************//
int checkin_save() { 
  String typus2;
  wdt_reset();
  t = rtc.now();
    if (typus==1){typus2="Mensch          ";}
    if (typus==2){typus2="Mutant          ";}
    if (typus==3){typus2="Mensch mit Bonus";}
    
  checkinlog = SD.open("clog.txt", FILE_WRITE);
  if (checkinlog) {
    
    Serial.println(F("Writing to clog..."));
   // Serial.write('\n');delay(write_pause);
    checkinlog.print(Terminalname);
    checkinlog.print(F(" | "));
    checkinlog.print(Con_Name);
    checkinlog.print(F(" | "));
 
  for (byte j = 0; j < mfrc522.uid.size; j++) {
    checkinlog.print(mfrc522.uid.uidByte[j] < 0x10 ? " 0" : " ");
    checkinlog.print(mfrc522.uid.uidByte[j], HEX);
  }
    checkinlog.print(F(" | Raywert alt | "));
    checkinlog.print(raywert_gelesen2);
    checkinlog.print(F(" | Raywert neu | "));
    checkinlog.print(raywert_gelesen/1000);
    checkinlog.print(F(" | Typus | "));
    checkinlog.print(typus2);
    checkinlog.print(F(" | Checkin um | "));
    checkinlog.printf("%4d-%02d-%02d %02d:%02d:%02d", t.year(), t.month(), t.day(), t.hour()+UTC, t.minute(), t.second());
    checkinlog.print(F(" | Verhalten | "));
    checkinlog.print(msg6);
    checkinlog.println(F(""));
    //checkinlog.println("-------------------------------------------------------------------------------------------------------------------------------------------------");
    checkinlog.close(); 

    Serial.println(F("Save done."));
  //  Serial.write('\n');delay(write_pause);
  } 
  
}
//*****************************************************************************************//

int booking_save() { 
  wdt_reset();
   t = rtc.now();
  buchunglog = SD.open("blog.txt", FILE_WRITE);
  if (buchunglog) {
    Serial.println(F("Writing to blog.txt..."));
  //  Serial.write('\n');delay(write_pause);
    buchunglog.print(Terminalname);
    buchunglog.print(" | ");
    buchunglog.print(Con_Name);
    buchunglog.print(F(" | "));
 
  for (byte j = 0; j < mfrc522.uid.size; j++) {
    buchunglog.print(mfrc522.uid.uidByte[j] < 0x10 ? " 0" : " ");
    buchunglog.print(mfrc522.uid.uidByte[j], HEX);
  }
    buchunglog.print(F(" | Raywert alt | "));
    buchunglog.print(Ray_value_extern_read/1000);
    buchunglog.print(F(" | Raywert neu | "));
    buchunglog.print(ray_writing);
    buchunglog.print(F(" | | | "));
    buchunglog.print(buchungsgrund);
    buchunglog.print(buchungsgrund2);
    buchunglog.print(F(" | "));
    buchunglog.printf("%4d-%02d-%02d %02d:%02d:%02d", t.year(), t.month(), t.day(), t.hour()+UTC, t.minute(), t.second());
    buchunglog.print(F(" | "));
    buchunglog.print(F(" | "));
    buchunglog.println(F(""));
    //buchunglog.println("-------------------------------------------------------------------------------------------------------------------------------------------------");
    buchunglog.close();
    Serial.println(F("Save done."));
    //Serial.write('\n');delay(write_pause);
  } 
}
//*****************************************************************************************//

long check_medi_log(){
wdt_reset();
int read_buffer[28];
int y;
File medilog = SD.open("medi.txt");
 
  if (medilog) {
    while (medilog.available()) {
    medilog.seek(0);
      for(y=0;y<=28;y++){
       read_buffer[y]=medilog.read()-'0';     
      }
      if(y>=28){medilog.close();}
 
         Menge_Dekon= ((read_buffer[0]*1000)+(read_buffer[1]*100)+(read_buffer[2]*10)+(read_buffer[3]));
         Menge_Nanoclean= ((read_buffer[5]*1000)+(read_buffer[6]*100)+(read_buffer[7]*10)+(read_buffer[8]));
         Menge_Life= ((read_buffer[10]*1000)+(read_buffer[11]*100)+(read_buffer[12]*10)+(read_buffer[13]));
         Menge_Clean= ((read_buffer[15]*1000)+(read_buffer[16]*100)+(read_buffer[17]*10)+(read_buffer[18]));
         Menge_Blood= ((read_buffer[20]*1000)+(read_buffer[21]*100)+(read_buffer[22]*10)+(read_buffer[23]));   
         Menge_Draw= ((read_buffer[25]*1000)+(read_buffer[26]*100)+(read_buffer[27]*10)+(read_buffer[28]));   
    } 
    /*     
    Serial.println("Gelesen");
    Serial.print("MDekon:");Serial.println(Menge_Dekon);
    Serial.print("MNano:");Serial.println(Menge_Nanoclean);
    Serial.print("MLife:");Serial.println(Menge_Life);
    Serial.print("MClean:");Serial.println(Menge_Clean);
    Serial.print("MBlood:");Serial.println(Menge_Blood);
    Serial.print("MDraw:");Serial.println(Menge_Draw);
    */
    medilog.close();
  }
  else{
  
Menge_Dekon     =   1000;    
Menge_Nanoclean =   2000;
Menge_Life      =   3000;
Menge_Clean     =   4000;
Menge_Blood     =   5000;
Menge_Draw      =   6000;
/*
    Serial.println("geraten");
    Serial.print("MDekon:");Serial.println(Menge_Dekon);
    Serial.print("MNano:");Serial.println(Menge_Nanoclean);
    Serial.print("MLife:");Serial.println(Menge_Life);
    Serial.print("MClean:");Serial.println(Menge_Clean);
    Serial.print("MBlood:");Serial.println(Menge_Blood);
    Serial.print("MDraw:");Serial.println(Menge_Draw);
    */
  }
}
//*****************************************************************************************//
long write_medi_log(unsigned int b1, unsigned int b2,unsigned int b3,unsigned int b4,unsigned int b5,unsigned int b6 ){
wdt_reset();
  File medilog = SD.open("medi.txt",FILE_WRITE);
if (medilog) {
  Serial.println(F("Writing to medi.txt..."));
  medilog.seek(0);
  medilog.print(b1);
  medilog.print(F("|"));
  medilog.print(b2);
  medilog.print(F("|"));
  medilog.print(b3);
  medilog.print(F("|"));
  medilog.print(b4);
  medilog.print(F("|"));
  medilog.print(b5);
  medilog.print(F("|"));
  medilog.print(b6);
  medilog.print(F("|"));
  medilog.close(); 
  Serial.println(F("Save done."));
 // Serial.write('\n');delay(write_pause);
}
}
//*****************************************************************************************//
