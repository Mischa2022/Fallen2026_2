// Konfiguration: Spieler-TAG = MFRC522 / Medi-TAG = PN532
  void main_rayomat(){
     
 long currentMillis;
t = rtc.now();      
aktuell_time=t.unixtime();


myservo_wippe.write(rueckgabe);
myservo_anzeige.write(175);
//Helfer falls während der Nutzung die verbindung zur Uhr abbricht.
 if( aktuell_time<1640991601||aktuell_time > 1893452460){
  Serial.println("Uhr ist verstellt");
  return;
 }
   serial_read(ziel_char,ziel_long,'\n');

  switch (ziel_char){


//Buchungslog ausgeben
      case 'g':     buzzer_play( 1,100);
                     buchunglog = SD.open("blog.txt");
                      if (buchunglog) {
                        while (buchunglog.available()) {
                          Serial.write(buchunglog.read());
                          }
                        buchunglog.close();
                        }
                       else {
                     // myprint("blog.txt nicht vorhanden","","",true,true,false,1,0);
                      Serial.println("blog.txt nicht vorhanden");
                      }
                      
                   ziel_long=0;
                   ziel_char=' ';          
      break;
    
//Buchungslogs löschen
      case '}':    buzzer_play( 1,100);
                  // myprint("Buchungslogs gelöscht","","",true,true,false,1,port);
                   Serial.println("Buchungslogs gelöscht");
                   SD.remove("blog.txt");
                   ziel_long=0;
                   ziel_char=' ';  
              
      break;
  

    
//konfig einlesen
      case 'c':    buzzer_play( 1,100);
                   char read_Char3;  //konfig import seriell
                   neu_konfig=' ';
                   warten=false;
                   Serial.println("Warten auf neue Konfig");

              while(warten==false){
                while (Serial.available()){
               
                 read_Char3 = (char)Serial.read();
                    if (read_Char3 != '\n') {
                  neu_konfig += read_Char3;
                    }
                  else{
                     if (SD.exists("konfig.txt")) {
                      SD.remove("konfig.txt");
                      delay(100);
                      Serial.println("alte Konfig gelöscht");
                      }
                    Serial.print("Konfi:");Serial.println(neu_konfig);
                      konfigFile = SD.open("konfig.txt", FILE_WRITE);
                if (konfigFile) {
    
                  Serial.write("Writing to konfig...");
                  Serial.write('\n');delay(50);
                  konfigFile.print(neu_konfig);
                  konfigFile.println("");
                  konfigFile.close(); 
                  Serial.write("Save done.");
                  Serial.write('\n');
                }
                    warten=true;
                    ziel_long=0;
                    ziel_char=' ';  
                    }     
                  } 
                }
                            
                          
      break;
// Uhr stellen serial
      case 'j':  buzzer_play( 3,100);
      
      rtc_stellen(hour(ziel_long), minute(ziel_long), second(ziel_long),day(ziel_long),month(ziel_long), year(ziel_long),  UTC);
    delay(100);
    t = rtc.now(); 
  
  
        Serial.print(t.hour(), DEC);
        Serial.print(':');
        Serial.print(t.minute(), DEC);
        Serial.print(':');
        Serial.print(t.second(), DEC); 
        Serial.print("-");
        Serial.print(t.day(), DEC);
        Serial.print('.');
        Serial.print(t.month(), DEC);
        Serial.print('.');
        Serial.print(t.year(), DEC);
        Serial.print(':');
        Serial.println(UTC);
        Serial.print("Zeit jetzt:");Serial.println(t.unixtime());
     
        t = rtc.now();
        
        delay(2000);

        
                ziel_long=0;
                ziel_char=' '; 
                
      break;    
      //Medilog ausgeben
      case 'k':      buzzer_play( 1,100);
                     medilog = SD.open("medi.txt");
                     
                      if (medilog) {
                        
                        while (medilog.available()) {
                          read_String2 =read_String2 + (char)medilog.read();
                          
                          if ( read_String2 == '\n') {
                            medilog.close();
                            }
                          }

                   Serial.println("Deko|Nano|Life|Clea|Bloo|Draw|");
                   Serial.println(read_String2);
                        }
                       else {
                
                  Serial.println("medi.txt nicht vorhanden");
                      }
                   
                      
                      
                   ziel_long=0;
                   read_String2="";
                   ziel_char=' '; 
                            
      break;
//Medilogs löschen
      case '=':    buzzer_play( 1,100);
          
                   Serial.println("medilogs gelöscht");
                   SD.remove("medi.txt");
                   ziel_long=0;
                   ziel_char=' ';  
              
      break;  
  }
  
  if ( ! mfrc522.PICC_IsNewCardPresent()){
        
        
   
        neo_select=random(0,2);
        blinki(99,99,neo_select);
        
     
        currentMillis = millis();
        previousMillis=millis();

        digitalWrite(ledPin1,LOW);
        
    ziel_long=0;
    ziel_char=' ';  

    return;
  
  } 

  else{
    digitalWrite(ledPin1,HIGH); //Optisches Signal für Erkennung ob Dongel anwesend
   myservo_wippe.write(geschlossen);
  }
  
  if ( ! mfrc522.PICC_ReadCardSerial()){
      
    return;
  
  }

  //Hauptfunktion um Medis zu erkennen, die eingeworfen wurden. Gibt ziel_char und ziel_long weiter als ob man es per seriell eingegeben hat
  //je nach Reader muss der richtige aktiviert werden
 
  while( sorte==0){
    
    currentMillis = millis();
    
    Mediread_PN532();
               
      }

  //Serielle Abfrage was aufgerufen werden soll
  serial_read(ziel_char,ziel_long,'\n');
        
  switch (ziel_char){   

//Ausführliche Analyse
    case '%':           
      
      Tag_analyse(10,1); 
            
      ziel_char=' ';  
      ziel_long=0;
      flow=1;

    break;
      
//Einfache Analyse
    case 'a':    
        
 
      Tag_analyse(ziel_long,0);     
      /*wert um check_rfid zu beeinflussen, zweiter wert für ausführlich==1 oder standard ==0
      * Man könnte auch eine Funktionalität schaffen um die Analsyse auch über Seriell zu wählen.
      * Tag_analyse(1,0); 
      *
      * 1 nur spieler infos ohne medi
      * 2 Nur Nanoclean infos
      * 3 Nur Dekon infos
      * 4 Nur Lifecleaner infos
      * 5 Nur Blutwäsche infos
      * 6 Nur Cleanray infos
      * 10 alle infos
      */
      
      ziel_long=0;
      ziel_char=' ';  
      flow=1;
    break;




//Medikamtent buchen
      case 'b':
      buzzer_play( 1,100);
      Serial.print("Grund:");Serial.println(Medi[ziel_long-1]);
    
      if(ziel_long>0&&ziel_long<9){
         if(ziel_long>1&&ziel_long<=7){
        
              check_medi_log();
          }
      medibuchung_MFRC522(ziel_long);
      booking_save();
    //  reset_variablen();
  
      Tag_analyse(10,0);
      myprint("------------------------------------------------","","",true,true,false,1,port);
      if(ziel_long>1&&ziel_long<=7){
            
            SD.remove("medi.txt");
            delay(100);
              write_medi_log(Menge_Dekon,Menge_Nanoclean,Menge_Life,Menge_Clean,Menge_Blood,Menge_Draw);
              myprint("------------------------------------------------","","",true,true,false,1,port);
          }
          
      reset_variablen();
      }  
      
      ziel_char=' ';  
      ziel_long=0;
      flow=1;
       /*
      * 1 Update
      * 2 Nanoclean 
      * 3 Dekon
      * 4 Lifecleaner 
      * 5 Blutwaesche
      * 6 Cleanray
      * 7 Drawback
      */
      
      break;
   

    
    default:
      
      ziel_long=0;
      ziel_char=' ';

    break;
  }     
     
  // Ausgabe, Switch Ende und Status Reset 
  if(flow==1){
    
    if(msg1!=""){
      Serial.println(msg1);
        }
    if(msg2!=""){
      Serial.print(msg2);
        }
    if(msg3!=""){
      Serial.println(msg3);
        }
    if(msg4!=""){
      Serial.println(msg4);
        }
       digitalWrite(ledPin2,LOW);
       digitalWrite(ledPin1,LOW);
       relais_switch(raywert,wartezeit);
      
    mfrc522.PICC_HaltA();   //finale stopfunktion
    mfrc522.PCD_StopCrypto1();//finale stopfunktion
    reset_variablen();
    raywert=0;
    Serial.println();
    

    flow=0;
    interruptPin_state=LOW;
  }

}
