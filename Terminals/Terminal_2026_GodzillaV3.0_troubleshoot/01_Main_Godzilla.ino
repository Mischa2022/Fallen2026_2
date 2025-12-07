
void loop() {


t = rtc.now();      
aktuell_time=t.unixtime();
aktuelle_millis=millis();



  serial_read(ziel_char,ziel_long,'\n');
//Serial.print("Char:");Serial.print(ziel_char);Serial.print(" ziel_long:");Serial.println(ziel_long);
  switch (ziel_char){

case 'u':
            serial_print_konfig();
                    wdt_reset();
                    ziel_long=0;
                    ziel_char=' ';  
break;


//Menue drucken
case '!':
                    print_menu();
                    wdt_reset();
                    ziel_long=0;
                    ziel_char=' ';  
break;

 //konfig einlesen
      case 'c':    buzzer_play( 3,100);
                   char read_Char3;  //konfig import seriell
                   neu_konfig=' ';
                   warten=false;
                   wdt_reset();
                   Serial.println(F("Warten auf neue Konfig"));

              while(warten==false){
                wdt_reset();
                while (Serial.available()){
               
                 read_Char3 = (char)Serial.read();
                 
                    if (read_Char3 != '\n') {
                  neu_konfig += read_Char3;
                    }
                  else{
                     if (SD.exists("konfig.txt")) {
                      SD.remove("konfig.txt");
                      delay(100);
                      Serial.println(F("alte Konfig geloescht"));
                      }
                    Serial.print(F("Konfi:"));Serial.println(neu_konfig);
                      konfigFile = SD.open("konfig.txt", FILE_WRITE);
                if (konfigFile) {
    
                  Serial.write("Writing to konfig...");
                  Serial.write('\n');delay(write_pause);
                  konfigFile.print(neu_konfig);
                  konfigFile.println("");
                  konfigFile.close(); 
                  Serial.write("Save done.");
                  Serial.write('\n');
                }
                initialisierung2();
                    warten=true;
                    wdt_reset();
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
        Serial.print(F(":"));
        Serial.print(t.minute(), DEC);
        Serial.print(F(":"));
        Serial.print(t.second(), DEC); 
        Serial.print(F("-"));
        Serial.print(t.day(), DEC);
        Serial.print(F("."));
        Serial.print(t.month(), DEC);
        Serial.print(F("."));
        Serial.print(t.year(), DEC);
        Serial.print(F(":"));
        Serial.println(UTC);
        Serial.print(F("Zeit jetzt:"));Serial.println(t.unixtime());
          
        t = rtc.now();
        
        delay(2000);

      
        initialisierung2();
                wdt_reset();
                ziel_long=0;
                ziel_char=' '; 
                
      break;                 


//Checkinlog ausgeben
      case 'f':      buzzer_play( 1,100);
                     checkinlog = SD.open("clog.txt");
                      if (checkinlog) {
                        while (checkinlog.available()) {
                          Serial.write(checkinlog.read());
                          }
                        checkinlog.close();
                        }
                       else {
                    
                        myprint("clog.txt nicht vorhanden","","",true,true,false,1,port);
                      }
                   wdt_reset();
                   ziel_long=0;
                   ziel_char=' '; 
                            
      break;

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
                      myprint("blog.txt nicht vorhanden","","",true,true,false,1,port);
                      }
                   wdt_reset();
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
                 
                   myprint("Deko|Nano|Life|Clea|Bloo|Draw|","","",true,true,false,1,port);
                   myprint("",read_String2,"",true,true,false,1,port);
                        }
                       else {
                
                  myprint("medi.txt nicht vorhanden","","",true,true,false,1,port);
                      }
                
                    // lcd_print_medi_log();
                      
                   wdt_reset();
                   ziel_long=0;
                   read_String2="";
                   ziel_char=' '; 
                            
      break;

//Medilogs loeschen
      case '=':    buzzer_play( 1,100);
          
                   myprint("medilogs geloescht","","",true,true,false,1,port);
                   SD.remove("medi.txt");
                   wdt_reset();
                   ziel_long=0;
                   ziel_char=' ';  
              
      break;
      
//Checkinlogs loeschen
      case '{':    buzzer_play( 1,100);
          
                   myprint("Checkinlogs geloescht","","",true,true,false,1,port);
                   SD.remove("clog.txt");
                   wdt_reset();
                   ziel_long=0;
                   ziel_char=' ';  
              
      break;
      
//Buchungslogs loeschen
      case '}':    buzzer_play( 1,100);
                   myprint("Buchungslogs geloescht","","",true,true,false,1,port);
                   SD.remove("blog.txt");
                   wdt_reset();
                   ziel_long=0;
                   ziel_char=' ';  
              
      break;
  
  }  

  



  
  if ( ! mfrc522.PICC_IsNewCardPresent()){
       
    digitalWrite(ledPin,LOW);
     
 
    wdt_reset();
    return;
    }
   else {  
   digitalWrite(ledPin,HIGH);
   
 
  }
 
  if ( ! mfrc522.PICC_ReadCardSerial()){
    
    wdt_reset();  
    return;
  }
  else{
  
  }



if(ziel_char==' '){

  serial_read(ziel_char,ziel_long,'\n');
}
  
  switch (ziel_char){   

//Ausfuehrliche Analyse
    case '%':           
      buzzer_play( 1,100);
      Tag_analyse(10,1);
      wdt_reset();     
      ziel_char=' ';  
      ziel_long=0;
      flow=1;

    break;
      
//Einfache Analyse
    case 'a':    
    buzzer_play( 1,100);
 
      if(ziel_long==100||ziel_long==20){ //hat die selbe Funktion wie beim Heart_Terminal mit a20 um ausgabe auf dem TFT etwas zu verkuerzen
        Tag_analyse(10,1);  
      }
      else{
      Tag_analyse(ziel_long,0);     
      }
      /*wert um check_rfid zu beeinflussen, zweiter wert fuer ausfuehrlich==1 oder standard ==0
      * Man koennte auch eine Funktionalitaet schaffen um die Analsyse auch ueber Seriell zu waehlen.
      * Tag_analyse(1,0,0); 
      *
      * 1 nur spieler infos ohne medi
      * 2 Nur Nanoclean infos
      * 3 Nur Dekon infos
      * 4 Nur Lifecleaner infos
      * 5 Nur Blutwaesche infos
      * 6 Nur Cleanray infos
      * 10 alle infos
      */
      
      wdt_reset();
      ziel_long=0;
      ziel_char=' ';  
      flow=1;
    break;

//CheckIn Mensch von Constart an inklusive update
    case 'h':         
      buzzer_play( 1,100);
      
      checkin(oedlaender,false,ziel_long,0);
      myprint("Neue Werte:","","",true,true,false,1,port);
      wdt_reset();
      medibuchung(1);
      booking_save();
      reset_variablen();

      wdt_reset();
     
      Tag_analyse(10,0); 
      typus=1;//fuer Logs
      checkin_save();
      wdt_reset();
      ziel_char=' ';
      ziel_long=0;   
      flow=1;
    
    break;
    
//CheckIn Mensch von jetzt an inklusive update
    case 'H':         //für späteren checkin
      buzzer_play( 1,100);
    
      checkin(oedlaender,false,ziel_long,1);
      myprint("Neue Werte:","","",true,true,false,1,port);
        medibuchung(1);
      booking_save();
      reset_variablen();

      Tag_analyse(10,0); 
      typus=1;//fuer Logs
      checkin_save();
      wdt_reset();
      ziel_char=' ';
      ziel_long=0;   
      flow=1;
    
    break;    
/*
//CheckIn Mensch mit Sold
    case 's':
      buzzer_play( 1,100);
      lcd.setCursor(0,0);
      lcd.print(infos[1]);
      checkin(oedlaender,true,0);
 
       myprint("Neue Werte:","","",true,true,false,1,port);
      Tag_analyse(2,0); //fuer ausgabe der Con-Daten
      //Tag_analyse(2,0); //fuer ausgabe der Nanoclean-Daten
      typus=3;//fuer Logs
      checkin_save();
      ziel_char=' ';
      ziel_long=0;
      flow=1;
    
    break;*/
/*                    
//CheckIn Mutant
    case 'n':
      buzzer_play( 1,100);
      lcd.setCursor(0,0);
      lcd.print(infos[1]);
      checkin(mutant,false,0);

       myprint("Neue Werte:","","",true,true,false,1,port);
      Tag_analyse(10,0,0);
      typus=2;//fuer Logs
      checkin_save();
      ziel_char=' ';
      ziel_long=0;
      flow=1;
    
    break;
*/
// Dongel Inhalt loeschen
    case 'v':
    buzzer_play( 1,100);
  
      rfid_reset();
      reset_variablen();
      Tag_analyse(10,1);     
      wdt_reset();      
      ziel_char=' ';
      ziel_long=0;
      flow=1;
    
    break;

//Medikamtent buchen
      case 'b':
      buzzer_play( 1,100);
     // Serial.print("Grund:");Serial.println(Medi[ziel_long-1]);
    
      if(ziel_long>0&&ziel_long<8){
         if(ziel_long>1&&ziel_long<=7){
        
              check_medi_log();
          }
      medibuchung(ziel_long);
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
      wdt_reset();
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
      
//Typus aendern
    case 'm':  
      buzzer_play( 1,100);
      Typus_aendern(ziel_long);
      //100 fuer Mensch
      //250 Bunkerbewohner
      //360 fuer Mutant  
      wdt_reset();
      ziel_char=' ';
      ziel_long=0;
      flow=1;

    break;   
case 'p': //korrektur(B,01,2025-02-06_13:59:17);
Serial.println(F("Warten auf Korrektur"));
Serial.println(F("Bitte gib folgendes Format ein"));
Serial.println(F("Medikament,Nr(2d),JJJJ.MM.TT-SS:MM:SS")); 
Serial.println(F("Beispiel:"));
Serial.println(F("B,01,2025-02-06 13:59:17")); 

                   char read_Char4;  //konfig import seriell
                   korrekturen=' ';
                   warten=false;
                   
while(warten==false){
    while (Serial.available()){
               
                 read_Char4 = (char)Serial.read();
                 
                    if (read_Char4 != '\n') {
                  korrekturen += read_Char4;
                    }
                    else{
                      korrektur(korrekturen);
      warten=true;
      Serial.println(korrekturen);
      wdt_reset();
      ziel_char=' ';
      ziel_long=0;
      flow=1;
                    }
                    
    }
    
}



    break;   
//Raywert editieren 
//Und Dongel fuer Plot beschreiben
    case 'r': 
      buzzer_play( 1,100);
      if(ziel_long==1||ziel_long==10){
        ray_manipulation(random(10,150)*1000UL);
      }
      else if(ziel_long==2||ziel_long==20){
         ray_manipulation(random(151,300)*1000UL);
      }
      else if(ziel_long==3||ziel_long==30){
         ray_manipulation(random(301,450)*1000UL);
      }
      else{
     ray_manipulation(ziel_long);
      }
      wdt_reset();
      ziel_char=' ';
      ziel_long=0;
      flow=1;
    
    break;   

//Lifecleaner schreiben ohne medi
       case 'l': 
      buzzer_play( 1,100);
       lifecleaner_write(ziel_long); //ziel_long=Stunden effekt
      wdt_reset();
      ziel_char=' ';
      ziel_long=0;
      flow=1;
    break;   
  
//Medirechte schreiben
    case 'o':
      buzzer_play( 1,100);
      medi_rechte(ziel_long);

      wdt_reset();
      ziel_char=' ';
      ziel_long=0;
      flow=1;
 
    break;   

    
    default:
      
      ziel_long=0;
      ziel_char=' ';

    break;
  }     
     
 // Ausgabe, Switch Ende und Status Reset 
  if(flow==1){
    delay(100);
   
    if(msg1!=""){
  
       myprint(msg1,"","",true,true,false,1,port);
     
        }
    if(msg2!=""){
    
       myprint(msg2,"","",true,false,false,1,port);
      
        }
    if(msg3!=""){
 
       myprint(msg3,"","",true,true,false,1,port);
      
        }
    if(msg4!=""){
 
       myprint(msg4,"","",true,false,false,1,port);
         
        }
    if(msg5!=""){

       myprint(msg5,"","",true,true,false,1,port);
      
        }
        
    mfrc522.PICC_HaltA();   //finale stopfunktion
    mfrc522.PCD_StopCrypto1();//finale stopfunktion
    reset_variablen();
     msg1="";
     msg2="";
     msg3="";
     msg4="";
     msg5="";
     msg6="";
    delay(2000);

  
    flow=0;
  }
}  
