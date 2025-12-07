 /*Auflistung Unterfunktionen, die fuer Check einens Dongels benoetigt werden
 * 
 * Check_rfid_tag     //2025 Helferfunktion um einen Spieler_Dongel auf gespeicherte Werte zu pruefen
 */

int Check_rfid_tag(int variante,bool ausfuehrlich){
//port=0;//kommunikation bei analyse ist nicht schnell genug im moment
/*varianten
 * 1 nur spieler infos ohne medi
 * 2 Nur Nanoclean infos
 * 3 Nur Dekon infos
 * 4 Nur Lifecleaner infos
 * 5 Nur Blutwaesche infos
 * 6 Nur Cleanray infos
 * 10 alle infos
 */


  Dekoncounter_thisday=0;
  Dekoncounter_allday=0;
  Nanocounter_thisday=0;
  Nanocounter_allday=0;
  Lifecounter_thisday=0;
  Lifecounter_allday=0;
  Cleancounter_thisday=0;
  Cleancounter_allday=0;
  Bloodcounter_thisday=0;
  Bloodcounter_allday=0;


 char* schrift[]{"Letzte Buchung:","Archetyp:","LifeCleanereffekt:","statischer Raywert:",
 "NanoClean 1:","NanoClean 2:","NanoClean 3:","NanoClean 4:","NanoClean 5:","NanoClean 6:","NanoClean 7:","NanoClean 8:",
 "Dekon 1:","Dekon 2:","Dekon 3:","Dekon 4:","Dekon 5:","Dekon 6:","Dekon 7:","Dekon 8:","Dekon 9:","Dekon 10:","Dekon 11:","Dekon 12:","Dekon 13:","Dekon 14:",
  "LifeCleaner 1:","LifeCleaner 2:","LifeCleaner 3:","LifeCleaner 4:","LifeCleaner 5:","LifeCleaner 6:","LifeCleaner 7:","LifeCleaner 8:","LifeCleaner 9:","LifeCleaner 10:",
  "BloodClean 1:","BloodClean 2:","BloodClean 3:","BloodClean 4:","BloodClean 5:","BloodClean 6:","BloodClean 7:","BloodClean 8:","BloodClean 9:","BloodClean 10:",
  "Cleanray 1:","Cleanray 2:","Cleanray 3:","Cleanray 4:","Cleanray 5:","Cleanray 6:","Cleanray 7:","Cleanray 8:",
  
  "Nanoclean","| Nanoclean",
  "Dekon","| Dekon",
  "Lifecleaner","| Lifecleaner",
  "Blutwaesche","| Blutwaesche",
  "Cleanray","| Cleanray"
  
  };
  
 char* typen[]{"Kein Typus","Mensch","Mutant","Bunkerbewohner"};
 char* typen2[]{" heute:"," insgesamt:"};
 int typ=0;

t = rtc.now();      
aktuell_time=t.unixtime();



con_tag=con_tag_bestimmen(aktuell_time,con_start_time,rest_time);
  
// Lesen der zufuellenden Werte

//Con und Spielerrelevante Daten
//*************************************************************************************//
if(variante==1||variante==10||variante==20){

error=error+rfid_reading(knownKeys[0],Admin1_block); //58
//Serial.print(F("Error Admin1:"));Serial.println(error);
  Con_Start_read=ergebnisA;
  Last_Booking_read=ergebnisB; 

  ergebnisA=0;ergebnisB=0;    
    
error=error+rfid_reading(knownKeys[0],Admin2_block); //57
//Serial.print(F("Error Admin2:"));Serial.println(error);
  archtype_read=ergebnisB;
  LifeCleaner_effekt_read=ergebnisA; 

  ergebnisA=0;ergebnisB=0;
    
error=error+rfid_reading(knownKeys[0],Admin3_block); //56
//Serial.print(F("Error Admin3:"));Serial.println(error);
  Con_End_read=ergebnisA;
  Ray_value_extern_read=ergebnisB; 
  
  ergebnisA=0;ergebnisB=0;  
}

//Nanocleaninformationen
//*************************************************************************************//
if( variante == 2 || variante == 10 ){
  
  int i;
  
  for(int x = 0; x <= 3; x++) { // 54, 53,52,50
    
    error=error+rfid_reading(knownKeys[0],block_nano[x]);
 //   Serial.print(F("Error Nano:"));Serial.println(error);
   i=x*2;

      NanoClean_read[i]=ergebnisA;
      NanoClean_read[i+1]=ergebnisB; 
 
      delay(10);
      ergebnisA=0;
      ergebnisB=0;
   
  }

  for(int y = 0; y <= 7; y++) {

      if(NanoClean_read[y]>=con_start_time){
        Nanocounter_allday=Nanocounter_allday+1;
        
      }
      
  
      if(tagabgleich(con_tag,NanoClean_read[y])){
        Nanocounter_thisday=Nanocounter_thisday+1;
        delay(50);
      } 
      //Serial.print("Nano");Serial.print(y);Serial.print(" :");Serial.println(Nanocounter_thisday);
      
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
  
  for(int x = 0; x <= 6; x++) { // 49,48,46,45,44,42,41
    
    error=error+rfid_reading(knownKeys[0],block_dekon[x]);
 //   Serial.print(F("Error Dekon:"));Serial.println(error);
    i=x*2;

      Dekon_read[i]=ergebnisA;
      Dekon_read[i+1]=ergebnisB;  
      delay(10);
      ergebnisA=0;
      ergebnisB=0;
 
  }

  for(int y = 0; y <= 11; y++) {

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
  
  for(int x = 0; x <= 4; x++) { //37,36,34,33,32
    
    error=error+rfid_reading(knownKeys[0],block_life[x]);
  //  Serial.print(F("Error Life:"));Serial.println(error);
       i=x*2;
 
    
      LifeCleaner_read[i]=ergebnisA;
      LifeCleaner_read[i+1]=ergebnisB; 
  
    delay(10);
      ergebnisA=0;
      ergebnisB=0;

  }

  for(int y = 0; y <= 9; y++) {

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

//Blutwaescheinformationen
//*************************************************************************************//
if(variante==5||variante==10){  
 int i;

  for(int x = 0; x <= 4; x++) { // 30,29,28,26,25
    
    error=error+rfid_reading(knownKeys[0],block_blood[x]);
  //  Serial.print(F("Error Blood:"));Serial.println(error);
    i=x*2;
   
    
      BloodClean_read[i]=ergebnisA;
      BloodClean_read[i+1]=ergebnisB; 
 
      delay(10);
      ergebnisA=0;
      ergebnisB=0;

  }

  for(int y = 0; y <= 9; y++) {

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
 
  for(int x = 0; x <= 3; x++) { // 18,17,16,14
    
    error=error+rfid_reading(knownKeys[0],block_clean[x]);
//    Serial.print(F("Error Clean:"));Serial.println(error);
   i=x*2;
       
      Cleanray_read[i]=ergebnisA;
      Cleanray_read[i+1]=ergebnisB; 
  
      delay(10);
      ergebnisA=0;
      ergebnisB=0;
      
  }

  for(int y = 0; y <= 7; y++) {

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
  error=error+rfid_reading(knownKeys[0],1);

  rights=ergebnisB;

  ergebnisA=0;ergebnisB=0;
}

//Ausgabe der gelesenen Werte als UNIX-werte aber nur wenn error==0
//*************************************************************************************//
  if(error==0){
   
  if(variante==1||variante==10){

        myprint("Con-Start:","",Con_Start_read,true,true,ausfuehrlich,1,port);
        myprint(schrift[0],"",Last_Booking_read,true,true,ausfuehrlich,1,port);
        if(Con_Start_read!=0&&Last_Booking_read!=0){
          if(aktuell_time>Last_Booking_read){
        Serial.print(F("Delta in Sekunden:"));Serial.println(aktuell_time-Last_Booking_read);
        Serial.print(F("Delta in Ray:"));Serial.println(((aktuell_time-Last_Booking_read)*1000)/1800);
          }
        }
    if(archtype_read==100){
      typ=1;

      }//fuer Godzilla
      
    if(archtype_read==360){
      typ=2;

      }//fuer Godzilla
      
    if(archtype_read==250){
      typ=3;

      }//fuer Godzilla 
      
    if(archtype_read==0){
      typ=0;

    }//fuer Godzilla fuer Plots

        myprint(schrift[1],typen[typ],"",true,true,false,1,port); 
        myprint(schrift[2],"",LifeCleaner_effekt_read,true,true,ausfuehrlich,1,port);      
        myprint(schrift[3],"",Ray_value_extern_read,true,true,false,1,port);
        myprint("Con Ende:","",Con_End_read,true,true,ausfuehrlich,1,port);
        myprint("------------------------------------------------","","",true,true,false,1,port);
  }


  
  if(variante==2||variante==10){
    for(int y = 0; y <= 7; y++) {
      if(NanoClean_read[y]!=0){
        myprint(schrift[y+4],"",NanoClean_read[y],true,true,ausfuehrlich,1,port);
      }
    }
  }
  
  if(variante==3||variante==10){
    for(int y = 0; y <= 13; y++) {
      if(Dekon_read[y]!=0){
        myprint(schrift[y+12],"",Dekon_read[y],true,true,ausfuehrlich,1,port);
      }
    }
  }
  
  if(variante==4||variante==10){
    for(int y = 0; y <= 9; y++) {
      if(LifeCleaner_read[y]!=0){
        myprint(schrift[y+26],"",LifeCleaner_read[y],true,true,ausfuehrlich,1,port);
      }
    }
  } 
  
  if(variante==5||variante==10){ 
    for(int y = 0; y <= 9; y++) {
      if(BloodClean_read[y]!=0){
        myprint(schrift[y+36],"",BloodClean_read[y],true,true,ausfuehrlich,1,port);
      }
    }
  }
  
  if(variante==6||variante==10){
    for(int y = 0; y <= 7; y++) {
      if(Cleanray_read[y]!=0){
        myprint(schrift[y+46],"",Cleanray_read[y],true,true,ausfuehrlich,1,port);
      }
    }
  }
 /* 

  if(variante==2||variante==10){
    for(int y = 0; y <= 7; y++) {
        myprint(schrift[y+4],"",NanoClean_read[y],true,true,ausfuehrlich,1,port);
    }
  }
  
  if(variante==3||variante==10){
    for(int y = 0; y <= 13; y++) {
        myprint(schrift[y+12],"",Dekon_read[y],true,true,ausfuehrlich,1,port);
    }
  }
  
  if(variante==4||variante==10){
    for(int y = 0; y <= 9; y++) {
        myprint(schrift[y+26],"",LifeCleaner_read[y],true,true,ausfuehrlich,1,port);
    }
  } 
  
  if(variante==5||variante==10){ 
    for(int y = 0; y <= 9; y++) {
        myprint(schrift[y+36],"",BloodClean_read[y],true,true,ausfuehrlich,1,port);
    }
  }
  
  if(variante==6||variante==10){
    for(int y = 0; y <= 7; y++) {
        myprint(schrift[y+46],"",Cleanray_read[y],true,true,ausfuehrlich,1,port);
    }
  }
*/
  
  }
 
 if(error==0){

    if(variante==1||variante==10){
  
  if(rights>0&&rights<11112){
    myprint("Rechte:NBCLD","","",true,true,false,1,port);
    myprint("       ","","",true,false,false,1,port);

  if(rights<10000){
  
  myprint("0","","",true,false,false,1,port);}
  if(rights<1000){
   
  myprint("0","","",true,false,false,1,port);}
  if(rights<100){
   
  myprint("0","","",true,false,false,1,port);}
  if(rights<10){
  
  myprint("0","","",true,false,false,1,port);}
  myprint("","",rights,true,true,false,1,port);

  }
    else{
          myprint("Rechte: keine","","",true,true,false,1,port);

    }
  }  
  myprint("------------------------------------------------","","",true,true,false,1,port);
    if(variante==2||variante==10){
      if(Nanocounter_allday>0){
          myprint(schrift[54],typen2[0],Nanocounter_thisday,true,false,false,1,port);
          myprint(schrift[55],typen2[1],Nanocounter_allday,true,true,false,1,port);
        }
      }
        
    if(variante==3||variante==10){
      if(Dekoncounter_allday>0){
          myprint(schrift[56],typen2[0],Dekoncounter_thisday,true,false,false,1,port);
          myprint(schrift[57],typen2[1],Dekoncounter_allday,true,true,false,1,port);
        }
      }
      
    if(variante==4||variante==10){
      if(Lifecounter_allday>0){
          myprint(schrift[58],typen2[0],Lifecounter_thisday,true,false,false,1,port);
          myprint(schrift[59],typen2[1],Lifecounter_allday,true,true,false,1,port);
      }
      }

    if(variante==5||variante==10){   
      if(Bloodcounter_allday>0){
          myprint(schrift[60],typen2[0],Bloodcounter_thisday,true,false,false,1,port);
          myprint(schrift[61],typen2[1],Bloodcounter_allday,true,true,false,1,port);
        }
      }
       
    if(variante==6||variante==10){  
      if( Cleancounter_allday>0){
          myprint(schrift[62],typen2[0],Cleancounter_thisday,true,false,false,1,port);
          myprint(schrift[63],typen2[1],Cleancounter_allday,true,true,false,1,port);
        }
      }
        
 

 }

    error=0;
 
}
//*************************************************************************************//
