// Konfiguration: Spieler-TAG = PN532 / Medi-TAG = MFRC522
  void main_rayomat_2(){
      uint8_t success=0;
       uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 }; 
  uint8_t uidLength=4; 
 unsigned long start=0;

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

   success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
 

  if (success) {
    
    digitalWrite(ledPin1,HIGH); //Optisches Signal für Erkennung ob Dongel anwesend
       myservo_wippe.write(geschlossen);
  } 

 
  else{
 
    digitalWrite(ledPin1,LOW);
    previousMillis=millis();
    currentMillis = millis();
    ziel_long=0;
    ziel_char=' ';  

   // return;
  
  } 
  

  //Hauptfunktion um Medis zu erkennen, die eingeworfen wurden. Gibt ziel_char und ziel_long weiter als ob man es per seriell eingegeben hat
  //je nach Reader muss der richtige aktiviert werden
 
 

  Mediread_MFRC522();
  currentMillis = millis();
   //Serial.print("current3:");
  // Serial.print(currentMillis);
  // Serial.print(" | previous3:");
   //Serial.println(previousMillis);
  if (currentMillis - previousMillis >= intervall) { 
    ziel_char='b';ziel_long=1;  
    }            
       



  //Serielle Abfrage was aufgerufen werden soll
  serial_read(ziel_char,ziel_long,'\n');

  switch (ziel_char){   

//Ausführliche Analyse
    case '%':           
      
      Tag_analyse_PN532(10,1); 
            
      ziel_char=' ';  
      ziel_long=0;
      flow=1;

    break;
      
//Einfache Analyse
    case 'a':    
    
      Tag_analyse_PN532(ziel_long,0);     
      /*wert um check_rfid zu beeinflussen, zweiter wert für ausführlich==1 oder standard ==0
      * Man könnte auch eine Funktionalität schaffen um die Analsyse auch über Seriell zu wählen.
      * Tag_analyse_MFRC522(1,0); 
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
      if(ziel_long>0&&ziel_long<8){
        buzzer_play(1,100); 
      medibuchung_PN532(ziel_long);
      }
      
      booking_save();
      ziel_char=' ';  
      ziel_long=0;
      flow=1;
       /*
      * 1 Update
      * 2 Nanoclean 
      * 3 Dekon
      * 4 Lifecleaner 
      * 5 Blutwäsche
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
       
   
      relais_switch(raywert,wartezeit);
   digitalWrite(ledPin1,LOW);
   success=0;
    reset_variablen();
    Serial.println();
    flow=0;
    previousMillis=millis();
    currentMillis = millis();

  }
    
    ziel_long=0;
    ziel_char=' ';  
    delay(500);  
    success=0;

    digitalWrite(ledPin1,LOW);
  

}
