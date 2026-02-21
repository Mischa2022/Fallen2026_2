 /*Auflistung Unterfunktionen, die für Check einens Dongels benötigt werden
 * 
 * Check_rfid_tag_mfrc522    //Helferfunktion um einen Spieler_Dongel per mfrc522 auf gespeicherte Werte zu prüfen
 * Check_rfid_tag_PN532    //Helferfunktion um einen Spieler_Dongel per mfrc522 auf gespeicherte Werte zu prüfen
 */

int Check_rfid_tag_mfrc522(int variante,bool ausfuehrlich){

/*varianten
 * 1 nur spieler infos ohne medi
 * 2 Nur Nanoclean infos
 * 3 Nur Dekon infos
 * 4 Nur Lifecleaner infos
 * 5 Nur Blutwäsche infos
 * 6 Nur Cleanray infos
 * 10 alle infos
 */
 
// Lesen der zufüllenden Werte

//Con und Spielerrelevante Daten
//*************************************************************************************//
if(variante==1||variante==10||variante==20){

error=error+reading_MFRC522(knownKeys[0],Admin1_block); //58

  Con_Start_read=ergebnisA;
  Last_Booking_read=ergebnisB; 

  ergebnisA=0;ergebnisB=0;    
    
error=error+reading_MFRC522(knownKeys[0],Admin2_block); //57
  archtype_read=ergebnisB;
  LifeCleaner_effekt_read=ergebnisA; 

  ergebnisA=0;ergebnisB=0;
    
error=error+reading_MFRC522(knownKeys[0],Ray_block); //56
  Ray_value_intern_read=ergebnisA;
  Ray_value_extern_read=ergebnisB; 

  ergebnisA=0;ergebnisB=0;  
}

//Nanocleaninformationen
//*************************************************************************************//
if( variante == 2 || variante == 10 ){
  
  int i;
 
  for(int x = Nano1_block; x >= Nano2_block; x--) { // 54 und 53
    
    error=error+reading_MFRC522(knownKeys[0],x);

    if(x == Nano1_block){
      i = 0;
    } else {
      i = 2;
    }
    
      NanoClean_read[i]=ergebnisA;
      NanoClean_read[i+1]=ergebnisB; 

      ergebnisA=0;
      ergebnisB=0;
    
  }

  for(int y = 0; y <= 3; y++) {

      if(NanoClean_read[y]>=con_start_time){
        Nanocounter_allday=Nanocounter_allday+1;
      }
  
      if(tagabgleich(con_tag,NanoClean_read[y])){
        Nanocounter_thisday=Nanocounter_thisday+1;
      } 
      
  }
  //zum Abfangen von falsch interpretierten Werten bei Buchungen bei Anreise
    if(Nanocounter_thisday>Nanocounter_allday){ 
    Nanocounter_allday=Nanocounter_thisday;
  }
}

//Dekoninformationen
//*************************************************************************************//
if(variante==3||variante==10){  
 int i;
 
  for(int x = Dekon1_block; x >= Dekon3_block; x--) { // 50,49,48
    
    error=error+reading_MFRC522(knownKeys[0],x);

    if(x == Dekon3_block){
      i = 4;

    }
    if(x == Dekon2_block){
      i = 2;

    }
    if(x == Dekon1_block){
      i = 0;

    }
    
      Dekon_read[i]=ergebnisA;
      Dekon_read[i+1]=ergebnisB; 

      ergebnisA=0;
      ergebnisB=0;
    
  }

  for(int y = 0; y <= 5; y++) {

      if(Dekon_read[y]>=con_start_time){
        Dekoncounter_allday=Dekoncounter_allday+1;
      }
  
      if(tagabgleich(con_tag,Dekon_read[y])){
        Dekoncounter_thisday=Dekoncounter_thisday+1;
      } 
      
  }
  //zum Abfangen von falsch interpretierten Werten bei Buchungen bei Anreise
      if(Dekoncounter_thisday>Dekoncounter_allday){
    Dekoncounter_allday=Dekoncounter_thisday;
  }
}

//Lifecleanerinformationen
//*************************************************************************************//
if(variante==4||variante==10){
 int i;
 
  for(int x = LifeCleaner1_block; x >= LifeCleaner3_block; x--) { // 46,45,44
    
    error=error+reading_MFRC522(knownKeys[0],x);

    if(x == LifeCleaner3_block){
      i = 4;

    }
    if(x == LifeCleaner2_block){
      i = 2;

    }
    if(x == LifeCleaner1_block){
      i = 0;

    }
    
      LifeCleaner_read[i]=ergebnisA;
      LifeCleaner_read[i+1]=ergebnisB; 

      ergebnisA=0;
      ergebnisB=0;
    
  }

  for(int y = 0; y <= 5; y++) {

      if(LifeCleaner_read[y]>=con_start_time){
        Lifecounter_allday=Lifecounter_allday+1;
      }
  
      if(tagabgleich(con_tag,LifeCleaner_read[y])){
        Lifecounter_thisday=Lifecounter_thisday+1;
      } 
      
  }
  //zum Abfangen von falsch interpretierten Werten bei Buchungen bei Anreise
    if(Lifecounter_thisday>Lifecounter_allday){
    Lifecounter_allday=Lifecounter_thisday;
  }
} 

//Blutwäscheinformationen
//*************************************************************************************//
if(variante==5||variante==10){  
 int i;
 
  for(int x = BloodClean1_block; x >= BloodClean3_block; x--) { // 42,41,40
    
    error=error+reading_MFRC522(knownKeys[0],x);

    if(x == BloodClean3_block){
      i = 4;

    }
    if(x == BloodClean2_block){
      i = 2;

    }
    if(x == BloodClean1_block){
      i = 0;

    }
    
      BloodClean_read[i]=ergebnisA;
      BloodClean_read[i+1]=ergebnisB; 

      ergebnisA=0;
      ergebnisB=0;
    
  }

  for(int y = 0; y <= 5; y++) {

      if(BloodClean_read[y]>=con_start_time){
        Bloodcounter_allday=Bloodcounter_allday+1;
      }
  
      if(tagabgleich(con_tag,BloodClean_read[y])){
        Bloodcounter_thisday=Bloodcounter_thisday+1;
      } 
      
  }
  //zum Abfangen von falsch interpretierten Werten bei Buchungen bei Anreise
  if(Bloodcounter_thisday>Bloodcounter_allday){
    Bloodcounter_allday=Bloodcounter_thisday;
  }
} 

//Cleanrayinformationen
//*************************************************************************************//
if(variante==6||variante==10){  
int i;
 
  for(int x = Cleanray1_block; x >= Cleanray3_block; x--) { // 38,37,36
    
    error=error+reading_MFRC522(knownKeys[0],x);

    if(x == Cleanray3_block){
      i = 4;

    }
    if(x == Cleanray2_block){
      i = 2;

    }
    if(x == Cleanray1_block){
      i = 0;

    }
    
      Cleanray_read[i]=ergebnisA;
      Cleanray_read[i+1]=ergebnisB; 

      ergebnisA=0;
      ergebnisB=0;
    
  }

  for(int y = 0; y <= 5; y++) {

      if(Cleanray_read[y]>=con_start_time){
        Cleancounter_allday=Cleancounter_allday+1;
      }
  
      if(tagabgleich(con_tag,Cleanray_read[y])){
        Cleancounter_thisday=Cleancounter_thisday+1;
      } 
      
  }
  //zum Abfangen von falsch interpretierten Werten bei Buchungen bei Anreise
  if(Cleancounter_thisday>Cleancounter_allday){
    Cleancounter_allday=Cleancounter_thisday;
  }
}

//Medirechte
//*************************************************************************************//
if(variante==1||variante==10){
  error=error+reading_MFRC522(knownKeys[0],1);
  rights=ergebnisB;

  ergebnisA=0;ergebnisB=0;
}

//Ausgabe der gelesenen Werte als UNIX-werte aber nur wenn error==0
//*************************************************************************************//
  if(error==0&&ausfuehrlich==0){
  if(variante==1||variante==10){
   
   // Serial.print("Con_Start_read:");//wird im folgenden Konvertiert
   // Serial.println(Con_Start_read); //wird im folgenden Konvertiert
    if(Con_Start_read==con_start_time){
      Serial.println(Con_Name);
     }
      else {
        Serial.println("noch nicht richtiges Con");
      }
  
   Serial.print("Letzte Buchung:"); //für Godzilla eigentlich "Last_Booking_read:"
   Serial.println(Last_Booking_read);
   
   // Serial.print("archtype_read:");//wird im folgenden Konvertiert
   // Serial.println(archtype_read); //wird im folgenden Konvertiert
    Serial.print("Archetyp:");
    if(archtype_read==100){
      Serial.println("Mensch");
      }//für Godzilla
      
    if(archtype_read==360){
      Serial.println("Mutant");
      }//für Godzilla
      
    if(archtype_read==250){
      Serial.println("Bunkerbewohner");
      }//für Godzilla 
      
    if(archtype_read==0){
      Serial.println("Kein Typus");
    }//für Godzilla für Plots
    
   Serial.print("LifeCleanereffekt:");//für Godzilla eigentlich "LifeCleaner effekt_read:"
   Serial.println(LifeCleaner_effekt_read);
   // Serial.print("Ray_value_intern_read:"); //wird momentan nicht gebraucht
   // Serial.println(Ray_value_intern_read);  //wird momentan nicht gebraucht
   
    Serial.print("Raywert:");//für Godzilla eigentlich "Ray_value_extern_read:"
    Serial.println(Ray_value_extern_read);
   
  }
  
  if(variante==2||variante==10){
  Serial.print("NanoClean1_read:");
  Serial.println(NanoClean_read[0]);
   
  Serial.print("NanoClean2_read:");
  Serial.println(NanoClean_read[1]);
  
  Serial.print("NanoClean3_read:");
  Serial.println(NanoClean_read[2]); 
  
  Serial.print("NanoClean4_read:");
  Serial.println(NanoClean_read[3]);
  }
  
  if(variante==3||variante==10){
  Serial.print("Dekon1_read:");
  Serial.println(Dekon_read[0]); 
  
  Serial.print("Dekon2_read:");
  Serial.println(Dekon_read[1]);
  
  Serial.print("Dekon3_read:");
  Serial.println(Dekon_read[2]); 
  
  Serial.print("Dekon4_read:");
  Serial.println(Dekon_read[3]);
  
  Serial.print("Dekon5_read:");
  Serial.println(Dekon_read[4]); 
  
  Serial.print("Dekon6_read:");
  Serial.println(Dekon_read[5]);
  }
  
  if(variante==4||variante==10){
  Serial.print("LifeCleaner1_read:");
  Serial.println(LifeCleaner_read[0]); 
  
  Serial.print("LifeCleaner2_read:");
  Serial.println(LifeCleaner_read[1]);
  
  Serial.print("LifeCleaner3_read:");
  Serial.println(LifeCleaner_read[2]); 
  
  Serial.print("LifeCleaner4_read:");
  Serial.println(LifeCleaner_read[3]);
  
  Serial.print("LifeCleaner5_read:");
  Serial.println(LifeCleaner_read[4]); 
  
  Serial.print("LifeCleaner6_read:");
  Serial.println(LifeCleaner_read[5]);
  } 
  
  if(variante==5||variante==10){ 
  Serial.print("BloodClean1_read:");
  Serial.println(BloodClean_read[0]); 
  
  Serial.print("BloodClean2_read:");
  Serial.println(BloodClean_read[1]);
  
  Serial.print("BloodClean3_read:");
  Serial.println(BloodClean_read[2]); 
  
  Serial.print("BloodClean4_read:");
  Serial.println(BloodClean_read[3]); 
  
  Serial.print("BloodClean5_read:");
  Serial.println(BloodClean_read[4]); 
  
  Serial.print("BloodClean6_read:");
  Serial.println(BloodClean_read[5]);
  }
  
  if(variante==6||variante==10){
  Serial.print("Cleanray1_read:");
  Serial.println(Cleanray_read[0]); 
  
  Serial.print("Cleanray2_read:");
  Serial.println(Cleanray_read[1]);
  
  Serial.print("Cleanray3_read:");
  Serial.println(Cleanray_read[2]); 
  
  Serial.print("Cleanray4_read:");
  Serial.println(Cleanray_read[3]);
  
  Serial.print("Cleanray5_read:");
  Serial.println(Cleanray_read[4]); 
  
  Serial.print("Cleanray6_read:");
  Serial.println(Cleanray_read[5]);
  }
  }
//Ausgabe der gelesenen Werte als Zeitwerte aber nur wenn error==0
//*************************************************************************************//
  if(error==0&&ausfuehrlich==1){
  if(variante==1||variante==10){
   
   // Serial.print("Con_Start_read:");//wird im folgenden Konvertiert
   // Serial.println(Con_Start_read); //wird im folgenden Konvertiert
    if(Con_Start_read==con_start_time){
      Serial.println(Con_Name);
     }
      else {
        Serial.println("noch nicht richtiges Con");
      }
  
   Serial.print("Letzte Buchung:"); //für Godzilla eigentlich "Last_Booking_read:"
   unix_converter(Last_Booking_read,UTC);
   
   // Serial.print("archtype_read:");//wird im folgenden Konvertiert
   // Serial.println(archtype_read); //wird im folgenden Konvertiert
    Serial.print("Archetyp:");
    if(archtype_read==100){
      Serial.println("Mensch");
      }//für Godzilla
      
    if(archtype_read==360){
      Serial.println("Mutant");
      }//für Godzilla
      
    if(archtype_read==250){
      Serial.println("Bunkerbewohner");
      }//für Godzilla 
    
   Serial.print("LifeCleanereffekt:");//für Godzilla eigentlich "LifeCleaner effekt_read:"
   Serial.println(LifeCleaner_effekt_read);
   // Serial.print("Ray_value_intern_read:"); //wird momentan nicht gebraucht
   // Serial.println(Ray_value_intern_read);  //wird momentan nicht gebraucht
   
    Serial.print("Raywert:");//für Godzilla eigentlich "Ray_value_extern_read:"
    Serial.println(Ray_value_extern_read);
   
  }
  
  if(variante==2||variante==10){
  Serial.print("NanoClean1_read:");
  unix_converter(NanoClean_read[0],UTC); 
  
  Serial.print("NanoClean2_read:");
  unix_converter(NanoClean_read[1],UTC);
  
  Serial.print("NanoClean3_read:");
  unix_converter(NanoClean_read[2],UTC); 
  
  Serial.print("NanoClean4_read:");
  unix_converter(NanoClean_read[3],UTC);
  }
  
  if(variante==3||variante==10){
  Serial.print("Dekon1_read:");
  unix_converter(Dekon_read[0],UTC); 
  
  Serial.print("Dekon2_read:");
  unix_converter(Dekon_read[1],UTC);
  
  Serial.print("Dekon3_read:");
  unix_converter(Dekon_read[2],UTC); 
  
  Serial.print("Dekon4_read:");
  unix_converter(Dekon_read[3],UTC);
  
  Serial.print("Dekon5_read:");
  unix_converter(Dekon_read[4],UTC); 
  
  Serial.print("Dekon6_read:");
  unix_converter(Dekon_read[5],UTC);
  }
  
  if(variante==4||variante==10){
  Serial.print("LifeCleaner1_read:");
  unix_converter(LifeCleaner_read[0],UTC); 
  
  Serial.print("LifeCleaner2_read:");
  unix_converter(LifeCleaner_read[1],UTC);
  
  Serial.print("LifeCleaner3_read:");
  unix_converter(LifeCleaner_read[2],UTC); 
  
  Serial.print("LifeCleaner4_read:");
  unix_converter(LifeCleaner_read[3],UTC);
  
  Serial.print("LifeCleaner5_read:");
  unix_converter(LifeCleaner_read[4],UTC); 
  
  Serial.print("LifeCleaner6_read:");
  unix_converter(LifeCleaner_read[5],UTC);
  } 
  
  if(variante==5||variante==10){ 
  Serial.print("BloodClean1_read:");
  unix_converter(BloodClean_read[0],UTC); 
  
  Serial.print("BloodClean2_read:");
  unix_converter(BloodClean_read[1],UTC);
  
  Serial.print("BloodClean3_read:");
  unix_converter(BloodClean_read[2],UTC); 
  
  Serial.print("BloodClean4_read:");
  unix_converter(BloodClean_read[3],UTC); 
  
  Serial.print("BloodClean5_read:");
  unix_converter(BloodClean_read[4],UTC); 
  
  Serial.print("BloodClean6_read:");
  unix_converter(BloodClean_read[5],UTC);
  }
  
  if(variante==6||variante==10){
  Serial.print("Cleanray1_read:");
  unix_converter(Cleanray_read[0],UTC); 
  
  Serial.print("Cleanray2_read:");
  unix_converter(Cleanray_read[1],UTC);
  
  Serial.print("Cleanray3_read:");
  unix_converter(Cleanray_read[2],UTC); 
  
  Serial.print("Cleanray4_read:");
  unix_converter(Cleanray_read[3],UTC);
  
  Serial.print("Cleanray5_read:");
  unix_converter(Cleanray_read[4],UTC); 
  
  Serial.print("Cleanray6_read:");
  unix_converter(Cleanray_read[5],UTC);
  }

  } 
 if(error==0){

    if(variante==1||variante==10){
  
  if(rights>0&&rights<11112){
  Serial.println("Rechte");
  Serial.println("NBCLD");
  if(rights<10000){Serial.print("0");}
  if(rights<1000){Serial.print("0");}
  if(rights<100){Serial.print("0");}
  if(rights<10){Serial.print("0");}
  Serial.println(rights); 
  }
    else{
    Serial.print("Rechte:");
    Serial.println("keine Rechte");
      }
    }
    
    if(variante==2||variante==10){
       Serial.print("Nanoclean heute:");
       Serial.print(Nanocounter_thisday);
       Serial.print("| Nanoclean insgesamt:");
       Serial.println(Nanocounter_allday);
      }
        
    if(variante==3||variante==10){
       Serial.print("Dekon heute:");
       Serial.print(Dekoncounter_thisday);
       Serial.print("| Dekon insgesamt:");
       Serial.println(Dekoncounter_allday);
      }
      
    if(variante==4||variante==10){
       Serial.print("Lifecleaner heute:");
       Serial.print(Lifecounter_thisday);
       Serial.print("| Lifecleaner insgesamt:");
       Serial.println(Lifecounter_allday);
      }
       
    if(variante==5||variante==10){   
       Serial.print("Cleanray heute:");
       Serial.print(Cleancounter_thisday);
       Serial.print("| Cleanray insgesamt:");
       Serial.println(Cleancounter_allday);
      }
        
    if(variante==6||variante==10){   
       Serial.print("Blutwäsche heute:");
       Serial.print(Bloodcounter_thisday);
       Serial.print("| Blutwäsche insgesamt:");
       Serial.println(Bloodcounter_allday);
      } 
 }
  //diese Abfragen müssen nicht im Check_RFID verbleiben, können aber erst nach ihm greifen
  if(variante==0){
    msg0="keine Auswahl getroffen";
  }
  else{
  if(Con_Start_read == con_start_time&&error==0){
    msg0="Normale Buchung";
    //effekt=1;   //effekt ist für die Buchungen nötig. 1= darf Buchen
  }   
  if(variante==2||variante==3||variante==4||variante==5||variante==6){
    msg0="Medicheck";
  }
  if(Con_Start_read ==0&&error==0&&variante==1){
    msg0="Leerer Dongel";
    //effekt=1;   //effekt ist für die Buchungen nötig. 1= darf Buchen
  }  
  if(error!=0){   //Wenn Fehler auftritt, keine Angaben machen und signalisieren, dass man es nochmal machen muss
    msg0="keine Auswertung";
  }
 }
/*  
    if(aktuell_time<con_start_time||con_tag==0){
    effekt =2; medi_effekt=1;error=1;  //effekt ist für die Buchungen nötig. 2= darf noch nicht Buchen // error=1 damit alle weiteren Buchungsschritte übersprungen werden
    msg="Zu früh";
    }
    */
    Serial.print("Ergebnis des Checks: ");
    Serial.println(msg0); 

}
//*************************************************************************************//

int Check_rfid_tag_PN532(int variante,bool ausfuehrlich){

/*varianten
 * 1 nur spieler infos ohne medi
 * 2 Nur Nanoclean infos
 * 3 Nur Dekon infos
 * 4 Nur Lifecleaner infos
 * 5 Nur Blutwäsche infos
 * 6 Nur Cleanray infos
 * 10 alle infos
 */
 
// Lesen der zufüllenden Werte

//Con und Spielerrelevante Daten
//*************************************************************************************//
if(variante==1||variante==10||variante==20){

error=error+reading_PN532(knownKeys[0],Admin1_block); //58

  Con_Start_read=ergebnisA2;
  Last_Booking_read=ergebnisB2; 

  ergebnisA2=0;ergebnisB2=0;    
    
error=error+reading_PN532(knownKeys[0],Admin2_block); //57

  archtype_read=ergebnisB2;
  LifeCleaner_effekt_read=ergebnisA2; 

  ergebnisA2=0;ergebnisB2=0;
    
error=error+reading_PN532(knownKeys[0],Ray_block); //56

  Ray_value_intern_read=ergebnisA2;
  Ray_value_extern_read=ergebnisB2; 

  ergebnisA2=0;ergebnisB2=0;  
}

//Nanocleaninformationen
//*************************************************************************************//
if( variante == 2 || variante == 10 ){
  
  int i;
 
  for(int x = Nano1_block; x >= Nano2_block; x--) { // 54 und 53
    
    error=error+reading_PN532(knownKeys[0],x);
 
    if(x == Nano1_block){
      i = 0;
    } else {
      i = 2;
    }
    
      NanoClean_read[i]=ergebnisA2;
      NanoClean_read[i+1]=ergebnisB2; 

      ergebnisA2=0;
      ergebnisB2=0;
    
  }

  for(int y = 0; y <= 3; y++) {

      if(NanoClean_read[y]>=con_start_time){
        Nanocounter_allday=Nanocounter_allday+1;
      }
  
      if(tagabgleich(con_tag,NanoClean_read[y])){
        Nanocounter_thisday=Nanocounter_thisday+1;
      } 
      
  }
  //zum Abfangen von falsch interpretierten Werten bei Buchungen bei Anreise
    if(Nanocounter_thisday>Nanocounter_allday){ 
    Nanocounter_allday=Nanocounter_thisday;
  }
}

//Dekoninformationen
//*************************************************************************************//
if(variante==3||variante==10){  
 int i;
 
  for(int x = Dekon1_block; x >= Dekon3_block; x--) { // 50,49,48
    
    error=error+reading_PN532(knownKeys[0],x);

    if(x == Dekon3_block){
      i = 4;

    }
    if(x == Dekon2_block){
      i = 2;

    }
    if(x == Dekon1_block){
      i = 0;

    }
    
      Dekon_read[i]=ergebnisA2;
      Dekon_read[i+1]=ergebnisB2; 

      ergebnisA2=0;
      ergebnisB2=0;
    
  }

  for(int y = 0; y <= 5; y++) {

      if(Dekon_read[y]>=con_start_time){
        Dekoncounter_allday=Dekoncounter_allday+1;
      }
  
      if(tagabgleich(con_tag,Dekon_read[y])){
        Dekoncounter_thisday=Dekoncounter_thisday+1;
      } 
      
  }
  //zum Abfangen von falsch interpretierten Werten bei Buchungen bei Anreise
      if(Dekoncounter_thisday>Dekoncounter_allday){
    Dekoncounter_allday=Dekoncounter_thisday;
  }
}

//Lifecleanerinformationen
//*************************************************************************************//
if(variante==4||variante==10){
 int i;
 
  for(int x = LifeCleaner1_block; x >= LifeCleaner3_block; x--) { // 46,45,44
    
    error=error+reading_PN532(knownKeys[0],x);

    if(x == LifeCleaner3_block){
      i = 4;

    }
    if(x == LifeCleaner2_block){
      i = 2;

    }
    if(x == LifeCleaner1_block){
      i = 0;

    }
    
      LifeCleaner_read[i]=ergebnisA2;
      LifeCleaner_read[i+1]=ergebnisB2; 

      ergebnisA2=0;
      ergebnisB2=0;
    
  }

  for(int y = 0; y <= 5; y++) {

      if(LifeCleaner_read[y]>=con_start_time){
        Lifecounter_allday=Lifecounter_allday+1;
      }
  
      if(tagabgleich(con_tag,LifeCleaner_read[y])){
        Lifecounter_thisday=Lifecounter_thisday+1;
      } 
      
  }
  //zum Abfangen von falsch interpretierten Werten bei Buchungen bei Anreise
    if(Lifecounter_thisday>Lifecounter_allday){
    Lifecounter_allday=Lifecounter_thisday;
  }
} 

//Blutwäscheinformationen
//*************************************************************************************//
if(variante==5||variante==10){  
 int i;
 
  for(int x = BloodClean1_block; x >= BloodClean3_block; x--) { // 42,41,40
    
    error=error+reading_PN532(knownKeys[0],x);

    if(x == BloodClean3_block){
      i = 4;

    }
    if(x == BloodClean2_block){
      i = 2;

    }
    if(x == BloodClean1_block){
      i = 0;

    }
    
      BloodClean_read[i]=ergebnisA2;
      BloodClean_read[i+1]=ergebnisB2; 

      ergebnisA2=0;
      ergebnisB2=0;
    
  }

  for(int y = 0; y <= 5; y++) {

      if(BloodClean_read[y]>=con_start_time){
        Bloodcounter_allday=Bloodcounter_allday+1;
      }
  
      if(tagabgleich(con_tag,BloodClean_read[y])){
        Bloodcounter_thisday=Bloodcounter_thisday+1;
      } 
      
  }
  //zum Abfangen von falsch interpretierten Werten bei Buchungen bei Anreise
  if(Bloodcounter_thisday>Bloodcounter_allday){
    Bloodcounter_allday=Bloodcounter_thisday;
  }
} 

//Cleanrayinformationen
//*************************************************************************************//
if(variante==6||variante==10){  
int i;
 
  for(int x = Cleanray1_block; x >= Cleanray3_block; x--) { // 38,37,36
    
    error=error+reading_PN532(knownKeys[0],x);

    if(x == Cleanray3_block){
      i = 4;

    }
    if(x == Cleanray2_block){
      i = 2;

    }
    if(x == Cleanray1_block){
      i = 0;

    }
    
      Cleanray_read[i]=ergebnisA2;
      Cleanray_read[i+1]=ergebnisB2; 

      ergebnisA2=0;
      ergebnisB2=0;
    
  }

  for(int y = 0; y <= 5; y++) {

      if(Cleanray_read[y]>=con_start_time){
        Cleancounter_allday=Cleancounter_allday+1;
      }
  
      if(tagabgleich(con_tag,Cleanray_read[y])){
        Cleancounter_thisday=Cleancounter_thisday+1;
      } 
      
  }
  //zum Abfangen von falsch interpretierten Werten bei Buchungen bei Anreise
  if(Cleancounter_thisday>Cleancounter_allday){
    Cleancounter_allday=Cleancounter_thisday;
  }
}

//Medirechte
//*************************************************************************************//
if(variante==1||variante==10){
  error=error+reading_PN532(knownKeys[0],1);

  rights=ergebnisB2;

  ergebnisA2=0;ergebnisB2=0;
}

//Ausgabe der gelesenen Werte als UNIX-werte aber nur wenn error==0
//*************************************************************************************//
  if(error==0&&ausfuehrlich==0){
  if(variante==1||variante==10){
   
   // Serial.print("Con_Start_read:");//wird im folgenden Konvertiert
   // Serial.println(Con_Start_read); //wird im folgenden Konvertiert
    if(Con_Start_read==con_start_time){
      Serial.println(Con_Name);
     }
      else {
        Serial.println("noch nicht richtiges Con");
      }
  
   Serial.print("Letzte Buchung:"); //für Godzilla eigentlich "Last_Booking_read:"
   Serial.println(Last_Booking_read);
   
   // Serial.print("archtype_read:");//wird im folgenden Konvertiert
   // Serial.println(archtype_read); //wird im folgenden Konvertiert
    Serial.print("Archetyp:");
    if(archtype_read==100){
      Serial.println("Mensch");
      }//für Godzilla
      
    if(archtype_read==360){
      Serial.println("Mutant");
      }//für Godzilla
      
    if(archtype_read==250){
      Serial.println("Bunkerbewohner");
      }//für Godzilla 
      
    if(archtype_read==0){
      Serial.println("Kein Typus");
    }//für Godzilla für Plots
    
   Serial.print("LifeCleanereffekt:");//für Godzilla eigentlich "LifeCleaner effekt_read:"
   Serial.println(LifeCleaner_effekt_read);
   // Serial.print("Ray_value_intern_read:"); //wird momentan nicht gebraucht
   // Serial.println(Ray_value_intern_read);  //wird momentan nicht gebraucht
   
    Serial.print("Raywert:");//für Godzilla eigentlich "Ray_value_extern_read:"
    Serial.println(Ray_value_extern_read);
   
  }
  
  if(variante==2||variante==10){
  Serial.print("NanoClean1_read:");
  Serial.println(NanoClean_read[0]);
   
  Serial.print("NanoClean2_read:");
  Serial.println(NanoClean_read[1]);
  
  Serial.print("NanoClean3_read:");
  Serial.println(NanoClean_read[2]); 
  
  Serial.print("NanoClean4_read:");
  Serial.println(NanoClean_read[3]);
  }
  
  if(variante==3||variante==10){
  Serial.print("Dekon1_read:");
  Serial.println(Dekon_read[0]); 
  
  Serial.print("Dekon2_read:");
  Serial.println(Dekon_read[1]);
  
  Serial.print("Dekon3_read:");
  Serial.println(Dekon_read[2]); 
  
  Serial.print("Dekon4_read:");
  Serial.println(Dekon_read[3]);
  
  Serial.print("Dekon5_read:");
  Serial.println(Dekon_read[4]); 
  
  Serial.print("Dekon6_read:");
  Serial.println(Dekon_read[5]);
  }
  
  if(variante==4||variante==10){
  Serial.print("LifeCleaner1_read:");
  Serial.println(LifeCleaner_read[0]); 
  
  Serial.print("LifeCleaner2_read:");
  Serial.println(LifeCleaner_read[1]);
  
  Serial.print("LifeCleaner3_read:");
  Serial.println(LifeCleaner_read[2]); 
  
  Serial.print("LifeCleaner4_read:");
  Serial.println(LifeCleaner_read[3]);
  
  Serial.print("LifeCleaner5_read:");
  Serial.println(LifeCleaner_read[4]); 
  
  Serial.print("LifeCleaner6_read:");
  Serial.println(LifeCleaner_read[5]);
  } 
  
  if(variante==5||variante==10){ 
  Serial.print("BloodClean1_read:");
  Serial.println(BloodClean_read[0]); 
  
  Serial.print("BloodClean2_read:");
  Serial.println(BloodClean_read[1]);
  
  Serial.print("BloodClean3_read:");
  Serial.println(BloodClean_read[2]); 
  
  Serial.print("BloodClean4_read:");
  Serial.println(BloodClean_read[3]); 
  
  Serial.print("BloodClean5_read:");
  Serial.println(BloodClean_read[4]); 
  
  Serial.print("BloodClean6_read:");
  Serial.println(BloodClean_read[5]);
  }
  
  if(variante==6||variante==10){
  Serial.print("Cleanray1_read:");
  Serial.println(Cleanray_read[0]); 
  
  Serial.print("Cleanray2_read:");
  Serial.println(Cleanray_read[1]);
  
  Serial.print("Cleanray3_read:");
  Serial.println(Cleanray_read[2]); 
  
  Serial.print("Cleanray4_read:");
  Serial.println(Cleanray_read[3]);
  
  Serial.print("Cleanray5_read:");
  Serial.println(Cleanray_read[4]); 
  
  Serial.print("Cleanray6_read:");
  Serial.println(Cleanray_read[5]);
  }
  }
//Ausgabe der gelesenen Werte als Zeitwerte aber nur wenn error==0
//*************************************************************************************//
  if(error==0&&ausfuehrlich==1){
  if(variante==1||variante==10){
   
   // Serial.print("Con_Start_read:");//wird im folgenden Konvertiert
   // Serial.println(Con_Start_read); //wird im folgenden Konvertiert
    if(Con_Start_read==con_start_time){
      Serial.println(Con_Name);
     }
      else {
        Serial.println("noch nicht richtiges Con");
      }
  
   Serial.print("Letzte Buchung:"); //für Godzilla eigentlich "Last_Booking_read:"
   unix_converter(Last_Booking_read,UTC);
   
   // Serial.print("archtype_read:");//wird im folgenden Konvertiert
   // Serial.println(archtype_read); //wird im folgenden Konvertiert
    Serial.print("Archetyp:");
    if(archtype_read==100){
      Serial.println("Mensch");
      }//für Godzilla
      
    if(archtype_read==360){
      Serial.println("Mutant");
      }//für Godzilla
      
    if(archtype_read==250){
      Serial.println("Bunkerbewohner");
      }//für Godzilla 
    
   Serial.print("LifeCleanereffekt:");//für Godzilla eigentlich "LifeCleaner effekt_read:"
   Serial.println(LifeCleaner_effekt_read);
   // Serial.print("Ray_value_intern_read:"); //wird momentan nicht gebraucht
   // Serial.println(Ray_value_intern_read);  //wird momentan nicht gebraucht
   
    Serial.print("Raywert:");//für Godzilla eigentlich "Ray_value_extern_read:"
    Serial.println(Ray_value_extern_read);
   
  }
  
  if(variante==2||variante==10){
  Serial.print("NanoClean1_read:");
  unix_converter(NanoClean_read[0],UTC); 
  
  Serial.print("NanoClean2_read:");
  unix_converter(NanoClean_read[1],UTC);
  
  Serial.print("NanoClean3_read:");
  unix_converter(NanoClean_read[2],UTC); 
  
  Serial.print("NanoClean4_read:");
  unix_converter(NanoClean_read[3],UTC);
  }
  
  if(variante==3||variante==10){
  Serial.print("Dekon1_read:");
  unix_converter(Dekon_read[0],UTC); 
  
  Serial.print("Dekon2_read:");
  unix_converter(Dekon_read[1],UTC);
  
  Serial.print("Dekon3_read:");
  unix_converter(Dekon_read[2],UTC); 
  
  Serial.print("Dekon4_read:");
  unix_converter(Dekon_read[3],UTC);
  
  Serial.print("Dekon5_read:");
  unix_converter(Dekon_read[4],UTC); 
  
  Serial.print("Dekon6_read:");
  unix_converter(Dekon_read[5],UTC);
  }
  
  if(variante==4||variante==10){
  Serial.print("LifeCleaner1_read:");
  unix_converter(LifeCleaner_read[0],UTC); 
  
  Serial.print("LifeCleaner2_read:");
  unix_converter(LifeCleaner_read[1],UTC);
  
  Serial.print("LifeCleaner3_read:");
  unix_converter(LifeCleaner_read[2],UTC); 
  
  Serial.print("LifeCleaner4_read:");
  unix_converter(LifeCleaner_read[3],UTC);
  
  Serial.print("LifeCleaner5_read:");
  unix_converter(LifeCleaner_read[4],UTC); 
  
  Serial.print("LifeCleaner6_read:");
  unix_converter(LifeCleaner_read[5],UTC);
  } 
  
  if(variante==5||variante==10){ 
  Serial.print("BloodClean1_read:");
  unix_converter(BloodClean_read[0],UTC); 
  
  Serial.print("BloodClean2_read:");
  unix_converter(BloodClean_read[1],UTC);
  
  Serial.print("BloodClean3_read:");
  unix_converter(BloodClean_read[2],UTC); 
  
  Serial.print("BloodClean4_read:");
  unix_converter(BloodClean_read[3],UTC); 
  
  Serial.print("BloodClean5_read:");
  unix_converter(BloodClean_read[4],UTC); 
  
  Serial.print("BloodClean6_read:");
  unix_converter(BloodClean_read[5],UTC);
  }
  
  if(variante==6||variante==10){
  Serial.print("Cleanray1_read:");
  unix_converter(Cleanray_read[0],UTC); 
  
  Serial.print("Cleanray2_read:");
  unix_converter(Cleanray_read[1],UTC);
  
  Serial.print("Cleanray3_read:");
  unix_converter(Cleanray_read[2],UTC); 
  
  Serial.print("Cleanray4_read:");
  unix_converter(Cleanray_read[3],UTC);
  
  Serial.print("Cleanray5_read:");
  unix_converter(Cleanray_read[4],UTC); 
  
  Serial.print("Cleanray6_read:");
  unix_converter(Cleanray_read[5],UTC);
  }

  } 
 if(error==0){

    if(variante==1||variante==10){
  
  if(rights>0&&rights<11112){
  Serial.println("Rechte");
  Serial.println("NBCLD");
  if(rights<10000){Serial.print("0");}
  if(rights<1000){Serial.print("0");}
  if(rights<100){Serial.print("0");}
  if(rights<10){Serial.print("0");}
  Serial.println(rights); 
  }
    else{
    Serial.print("Rechte:");
    Serial.println("keine Rechte");
      }
    }
    
    if(variante==2||variante==10){
       Serial.print("Nanoclean heute:");
       Serial.print(Nanocounter_thisday);
       Serial.print("| Nanoclean insgesamt:");
       Serial.println(Nanocounter_allday);
      }
        
    if(variante==3||variante==10){
       Serial.print("Dekon heute:");
       Serial.print(Dekoncounter_thisday);
       Serial.print("| Dekon insgesamt:");
       Serial.println(Dekoncounter_allday);
      }
      
    if(variante==4||variante==10){
       Serial.print("Lifecleaner heute:");
       Serial.print(Lifecounter_thisday);
       Serial.print("| Lifecleaner insgesamt:");
       Serial.println(Lifecounter_allday);
      }
       
    if(variante==5||variante==10){   
       Serial.print("Cleanray heute:");
       Serial.print(Cleancounter_thisday);
       Serial.print("| Cleanray insgesamt:");
       Serial.println(Cleancounter_allday);
      }
        
    if(variante==6||variante==10){   
       Serial.print("Blutwäsche heute:");
       Serial.print(Bloodcounter_thisday);
       Serial.print("| Blutwäsche insgesamt:");
       Serial.println(Bloodcounter_allday);
      } 
 }
  //diese Abfragen müssen nicht im Check_RFID verbleiben, können aber erst nach ihm greifen
  if(variante==0){
    msg0="keine Auswahl getroffen";
  }
  else{
  if(Con_Start_read == con_start_time&&error==0){
    msg0="Normale Buchung";
    //effekt=1;   //effekt ist für die Buchungen nötig. 1= darf Buchen
  }   
  if(variante==2||variante==3||variante==4||variante==5||variante==6){
    msg0="Medicheck";
  }
  if(Con_Start_read ==0&&error==0&&variante==1){
    msg0="Leerer Dongel";
    //effekt=1;   //effekt ist für die Buchungen nötig. 1= darf Buchen
  }  
  if(error!=0){   //Wenn Fehler auftritt, keine Angaben machen und signalisieren, dass man es nochmal machen muss
    msg0="keine Auswertung";
  }
 }
/*  
    if(aktuell_time<con_start_time||con_tag==0){
    effekt =2; medi_effekt=1;error=1;  //effekt ist für die Buchungen nötig. 2= darf noch nicht Buchen // error=1 damit alle weiteren Buchungsschritte übersprungen werden
    msg="Zu früh";
    }
    */
    Serial.print("Ergebnis des Checks: ");
    Serial.println(msg0); 

}
//*************************************************************************************//
