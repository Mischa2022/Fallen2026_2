/*Auflistung Unterfunktionen, die für SD-Karten_Reeader benötigt werden
 * 
 * konfig_read()              //  funktion die werte von der sd karte liest und auf seine "richtigkeit" kontrolliert
 * cut                        //  unterfunktion
 * split                      //  unterfunktion
 * save_konfig_to_eeprom()    //  speichern von eingelesenen konfigdaten im eeprom
 * read_konfig_from_eeprom()  //  auslesen von konfigdaten aus dem eeprom
 * initialisierung()          //  überprüfung ob sd_reader funktioniert und ob neue konfig verfügbar, sonst laden der bestehenden konfig
 * checkinlog()               //  speichert die werte und zeiten des checkins 
 * booking_save()             //  speichert die werte und zeiten von Medikamentenbuchungen 
 * check_medi_log()           //  Funktion um den Buchungsstand zu laden. Also wieviele Medis wurden bisher gebucht
 * write_medi_log()           //  Funktion zum speichern der Medibuchungen
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

  konfig_time = basis[1].toInt();
  
      //con_start_time=konfig_time+(2*86400); //für tests bei verschiedenen startwerten
      con_start_time=konfig_time;
      UTC =basis[2].toInt();
      //UNIX_korrektur = basis[3]*60; // ist nun festgesetzt
      anzahl_tage=basis[4].toInt();// minuswert nur zum testen von konfigdaten
      tagesdosis=basis[5].toInt(); 
   
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
/*
int checkin_save() { 
  String typus2;
  
  t = rtc.now();
    if (typus==1){typus2="Mensch          ";}
    if (typus==2){typus2="Mutant          ";}
    if (typus==3){typus2="Mensch mit Bonus";}
    
  checkinlog = SD.open("clog.txt", FILE_WRITE);
  if (checkinlog) {
    
    Serial.write("Writing to clog...");
    Serial.write('\n');delay(50);
    checkinlog.print(Terminalname);
    checkinlog.print(" | ");
    checkinlog.print(Con_Name);
    checkinlog.print(F("| ID: "));
 
  for (byte j = 0; j < mfrc522.uid.size; j++) {
    checkinlog.print(mfrc522.uid.uidByte[j] < 0x10 ? " 0" : " ");
    checkinlog.print(mfrc522.uid.uidByte[j], HEX);
  }
    checkinlog.print(" | Raywert : ");
    checkinlog.print(Ray_value_extern_read/1000);
    checkinlog.print(" | Typus : ");
    
    checkinlog.print(typus2);
    checkinlog.print(" | Checkin at : ");
    checkinlog.printf("%4d-%02d-%02d %02d:%02d:%02d", t.year(), t.month(), t.day(), t.hour()+UTC, t.minute(), t.second());
    checkinlog.println("");
    checkinlog.println("-------------------------------------------------------------------------------------------------------------------------------------------------");
    checkinlog.close(); 

    Serial.write("Save done.");
    Serial.write('\n');delay(50);
  } 
  
}*/
//*****************************************************************************************//

int booking_save() { 
   t = rtc.now();
  buchunglog = SD.open("blog.txt", FILE_WRITE);
  if (buchunglog) {
    Serial.write("Writing to blog.txt...");
    Serial.write('\n');delay(50);
    buchunglog.print(Terminalname);
    buchunglog.print(" | ");
    buchunglog.print(Con_Name);
    buchunglog.print(F("| ID: "));
 
  for (byte j = 0; j < mfrc522.uid.size; j++) {
    buchunglog.print(mfrc522.uid.uidByte[j] < 0x10 ? " 0" : " ");
    buchunglog.print(mfrc522.uid.uidByte[j], HEX);
  }
    buchunglog.print(" | ");
    buchunglog.print("Raywert old: ");
    buchunglog.print(Ray_value_extern_read/1000);
    buchunglog.print(" | Raywert new: ");
    buchunglog.print(ray_writing);
    buchunglog.print(" | by ");
    buchunglog.print(buchungsgrund);
    buchunglog.print(buchungsgrund2);
    buchunglog.print(" | at : ");
    buchunglog.printf("%4d-%02d-%02d %02d:%02d:%02d", t.year(), t.month(), t.day(), t.hour()+UTC, t.minute(), t.second());
    buchunglog.println("");
    buchunglog.println("-------------------------------------------------------------------------------------------------------------------------------------------------");
    buchunglog.close();
    Serial.write("Save done.");
    Serial.write('\n');delay(50);
  } 
}
//*****************************************************************************************//

long check_medi_log(){

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
    medilog.close();
  }
  else{
Menge_Dekon     =   1000;    
Menge_Nanoclean =   2000;
Menge_Life      =   3000;
Menge_Clean     =   4000;
Menge_Blood     =   5000;
Menge_Draw      =   6000;
  }
}
//*****************************************************************************************//
long write_medi_log(unsigned int b1, unsigned int b2,unsigned int b3,unsigned int b4,unsigned int b5,unsigned int b6 ){

  File medilog = SD.open("medi.txt",FILE_WRITE);
if (medilog) {
  Serial.println("Writing to medi.txt...");
  medilog.seek(0);
  medilog.print(b1);
  medilog.print("|");
  medilog.print(b2);
  medilog.print("|");
  medilog.print(b3);
  medilog.print("|");
  medilog.print(b4);
  medilog.print("|");
  medilog.print(b5);
  medilog.print("|");
  medilog.print(b6);
  medilog.print("|");
  medilog.close(); 
}
}
//*****************************************************************************************//
