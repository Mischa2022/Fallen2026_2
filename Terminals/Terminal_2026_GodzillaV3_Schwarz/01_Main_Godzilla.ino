
void loop() {

  button.update(); 
  result = rotary.process();


  
      if(modus==2||modus==20){
        if(modus==20){modus=2;}
        if(Anzeige_update ==true){maxebene=1;}
        if(Anzeige_Nanoclean ==true){maxebene=2;}
        if(Anzeige_Dekon ==true){maxebene=3;}
        if(Anzeige_Lifecleaner ==true){maxebene=4;}
        if(Anzeige_Blutwaesche ==true){maxebene=5;}
        if(Anzeige_Cleanray ==true){maxebene=6;}
         if(Anzeige_drawback ==true){maxebene=7;}
    if(input_over_rotary==true){       
        rotary_read(0,maxebene);
        }
     if(input_over_rotary==false){
        poti_read(0,maxebene);
          }
      }
    else{  
     if(input_over_rotary==true){
      rotary_read(0,2);
     }
     if(input_over_rotary==false){
        poti_read(0,2);
          }
      }

 
t = rtc.now();      
aktuell_time=t.unixtime();
aktuelle_millis=millis();
char* infos[] {"Analyse gestartet   ","Checkin gestartet   ","Reset gestartet     ","Medibuchen gestartet"};

/*
//Helfer falls waehrend der Nutzung die verbindung zur Uhr abbricht.
 if( aktuell_time<(con_start_time-432000)||aktuell_time > 1893452460){
  myprint("Uhr ist verstellt","","",true,true,false,1,0);
    lcd.setCursor(0,0);
  lcd.print("Uhr ist verstellt");  
  return;
 }*/
  serial_read(ziel_char,ziel_long,'\n');
//Serial.print("Char:");Serial.print(ziel_char);Serial.print(" ziel_long:");Serial.println(ziel_long);
  switch (ziel_char){


//verbindung aufbauen
/*
    case 'x':           
      buzzer_play( 1,100);
      Serial3.print("x");Serial3.print(ziel_long);Serial3.println( '\n');
         Serial.println("es wird versucht eine verbindung aufzubauen");   
      ziel_char=' ';  
      ziel_long=0;
      flow=1;

    break;
*/
//Modus aendern
      case 't':      buzzer_play( 3,100);
 
                 
                     if(ziel_long==2||ziel_long==20||ziel_long==200){
                      
                      modus=2;
                      locked=true;
                      counterx = 0; 
                      }
                     else if(ziel_long==1||ziel_long==10||ziel_long==100){
                    
                      modus=1;  
                      locked=false;
                      counterx = 0;
                      }
                     else {
                      
                      modus=0; 
                      locked=false;
                      counterx = 0;
                      }
                     
                   
                     
                     SD.remove("moduslog.txt");
                     moduslog = SD.open("moduslog.txt", FILE_WRITE);
                      if (moduslog) {
                        Serial.println(F("Writing to moduslog..."));
                        
                        moduslog.println(modus);
                        lcd.clear();
                        delay(50);
                        
                        lcd.setCursor(0,0);
                        

                        moduslog.close();
                        Serial2.print("y");Serial2.print(modus);Serial2.write('\n');
                          }

                       else {
                    
                        myprint("moduslog.txt nicht vorhanden","","",true,true,false,1,port);
                      }
                   menue_print_lcd(modus,0);   
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
                while (Serial.available()||Serial2.available()){
               
                 read_Char3 = (char)Serial.read();
                 read_Char3 = (char)Serial2.read();
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
    
                  Serial.print(F("Writing to konfig..."));
                  Serial.write('\n');delay(write_pause);
                  konfigFile.print(neu_konfig);
                  konfigFile.println("");
                  konfigFile.close(); 
                  Serial.print(F("Save done."));
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
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Uhr gestellt");        
        t = rtc.now();
        
        delay(2000);

        lcd.clear();
        initialisierung2();
                wdt_reset();
                ziel_long=0;
                ziel_char=' '; 
                
      break;           
case 'u':
            serial_print_konfig();
                    wdt_reset();
                    ziel_long=0;
                    ziel_char=' ';  
break;

            /*
case 'u':
char signal1='*';
char signal2='\n';
  Serial2.write(signal1);Serial2.print( Con_Name               );Serial2.print(signal2);delay(10); 
  Serial2.write(signal1);Serial2.print( con_start_time         );Serial2.print(signal2);delay(10); 
  Serial2.write(signal1);Serial2.print( "0"                    );Serial2.print(signal2);delay(10); 
  Serial2.write(signal1);Serial2.print( "60"                   );Serial2.print(signal2);delay(10); 
  Serial2.write(signal1);Serial2.print( anzahl_tage            );Serial2.print(signal2);delay(10); 
  Serial2.write(signal1);Serial2.print( tagesdosis             );Serial2.print(signal2);delay(10); 
 
  
  Serial2.write(signal1);Serial2.print( Cleanray_min_effekt    );Serial2.print(signal2);delay(10); 
  Serial2.write(signal1);Serial2.print( Cleanray_max_effekt    );Serial2.print(signal2);delay(10); 
  
  Serial2.write(signal1);Serial2.print( Clean_per_con          );Serial2.print(signal2);delay(10); 
  Serial2.write(signal1);Serial2.print( Clean_per_day          );Serial2.print(signal2);delay(10);                  
     
  Serial2.write(signal1);Serial2.print( LifeCleaner_buffer/3600);Serial2.print(signal2);delay(10); 
  Serial2.write(signal1);Serial2.print( Life_per_con           );Serial2.print(signal2);delay(10); 
  Serial2.write(signal1);Serial2.print( LifeCleaner_per_day    );Serial2.print(signal2);delay(10); 

  Serial2.write(signal1);Serial2.print( Bloodclean_min_effekt  );Serial2.print(signal2);delay(10); 
  Serial2.write(signal1);Serial2.print( Bloodclean_max_effekt  );Serial2.print(signal2);delay(10); 
  Serial2.write(signal1);Serial2.print( Blood_per_con          );Serial2.print(signal2);delay(10); 
  Serial2.write(signal1);Serial2.print( Blood_per_day          );Serial2.print(signal2);delay(10); 
                  
  Serial2.write(signal1);Serial2.print( Nanoclean_min_effekt   );Serial2.print(signal2);delay(10); 
  Serial2.write(signal1);Serial2.print( Nanoclean_max_effekt   );Serial2.print(signal2);delay(10); 
  Serial2.write(signal1);Serial2.print( Nano_per_con           );Serial2.print(signal2);delay(10); 
  Serial2.write(signal1);Serial2.print( Nano_per_day           );Serial2.print(signal2);delay(10); 
                              
  Serial2.write(signal1);Serial2.print( Dekon_min_effekt       );Serial2.print(signal2);delay(10); 
  Serial2.write(signal1);Serial2.print( Dekon_max_effekt       );Serial2.print(signal2);delay(10);             
  Serial2.write(signal1);Serial2.print( Dekon_per_con          );Serial2.print(signal2);delay(10);          
  Serial2.write(signal1);Serial2.print( Dekon_per_day          );Serial2.print(signal2);delay(10); 
  Serial2.write(signal1);Serial2.print(signal2);delay(10); 
  
                    wdt_reset();
                    ziel_long=0;
                    ziel_char=' ';  
                    
break;
*/

/*
//Menue drucken
case '!':
                    print_menu();
                    wdt_reset();
                    ziel_long=0;
                    ziel_char=' ';  
break;*/


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
                
                     lcd_print_medi_log();
                      
                   wdt_reset();
                   ziel_long=0;
                   read_String2="";
                   ziel_char=' '; 
                            
      break;
/*      
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
  */

  }  
if(locked==true){
      entsperrzeit=millis();
    if (  mfrc522.PICC_IsNewCardPresent()) {
          
          }else{
            wdt_reset(); 
            return;
            }
         
      if (  mfrc522.PICC_ReadCardSerial()) {

            for (byte j = 0; j < mfrc522.uid.size; j++) {
                id_buffer[j]=mfrc522.uid.uidByte[j];
               //     Serial.print(id_buffer[j] < 0x10 ? " 0" : " ");
               //     Serial.print(id_buffer[j], HEX);
                }
              //  Serial.println();


int x=0;
if(memcmp(id_buffer, known_id[9], sizeof(id_buffer)) == 0){
                known=true;x=1;delay(500);
                }
if(memcmp(id_buffer, known_id[8], sizeof(id_buffer)) == 0){
                known=true;x=1;delay(500);
                }
if(memcmp(id_buffer, known_id[7], sizeof(id_buffer)) == 0){
                known=true;x=1;delay(500);
                }
if(memcmp(id_buffer, known_id[6], sizeof(id_buffer)) == 0){
                known=true;x=1;delay(500);
                }                
if(memcmp(id_buffer, known_id[5], sizeof(id_buffer)) == 0){
                known=true;x=1;delay(500);
                }
if(memcmp(id_buffer, known_id[0], sizeof(id_buffer)) == 0){
                known=true;x=2;delay(500);
                }  
if(memcmp(id_buffer, known_id[1], sizeof(id_buffer)) == 0){
                known=true;x=2;delay(500);
                }    
if(memcmp(id_buffer, known_id[2], sizeof(id_buffer)) == 0){
                known=true;x=2;delay(500);
                }  
if(memcmp(id_buffer, known_id[3], sizeof(id_buffer)) == 0){
                known=true;x=2;delay(500);
                }  
if(memcmp(id_buffer, known_id[4], sizeof(id_buffer)) == 0){
                known=true;x=2;delay(500);
                }                    
  if(known==true){
digitalWrite(ledPin,HIGH);
          buzzer_play( 1,100);
if(x==1){

  modus=modus+1;
  
                     if(modus>2){modus=0;}
                     else if(modus<=0){modus=2;}
                     
                     
                     SD.remove("moduslog.txt");
                     moduslog = SD.open("moduslog.txt", FILE_WRITE);
                      if (moduslog) {
                        Serial.println(F("Writing to moduslog..."));
                        
                        moduslog.println(modus);
                        lcd.clear();
                        delay(50);
                        //modus=ziel_long;
                        lcd.setCursor(0,0);
                        
                        
   if (modus==0){

    locked=false;
    counterx = 0;
    }    
   if (modus==1){
    
    locked=false;
    counterx = 0;
     }  
   if (modus==2){
    
    locked=true;
    counterx = 0;
    } 
                        moduslog.close();
                        Serial2.print("y");Serial2.print(modus);Serial2.write('\n');
                        
                          }

                       else {
                    
                        myprint("moduslog.txt nicht vorhanden","","",true,true,false,1,port);
                      }
                   menue_print_lcd(modus,0);   
                   ziel_long=0;
                  mfrc522.PICC_HaltA();
                  mfrc522.PCD_StopCrypto1(); 
                  digitalWrite(ledPin,LOW);
}
if(x==2){
          lcd_print_medi_log();
          wdt_reset();
          mfrc522.PICC_HaltA();
          mfrc522.PCD_StopCrypto1(); 
     
      }

    //known=false;

  }
  if(known==false){
                
          rfid_reading(knownKeys[0],1);   
          rights=ergebnisB;
      
        if(rights>0&&rights<11112){
            rechte_check(rights);
            wdt_reset();
            mfrc522.PICC_HaltA();
            mfrc522.PCD_StopCrypto1(); 
                   Serial2.print("p");
            if(rights<10000){Serial2.print("0");}
            if(rights<1000){Serial2.print("0");}
            if(rights<100){Serial2.print("0");}
            if(rights<10){Serial2.print("0");}
            Serial2.println(rights);
            digitalWrite(ledPin,LOW);
            buzzer_play( 3,100);
            return;
          }
      
        if(rights>11111||rights==0){
          lcd.setCursor(0, 0);
          lcd.print("                    "); 
          lcd.setCursor(0, 1);
          lcd.print("     Blockiert      ");       
          lcd.setCursor(0, 2);
          lcd.print("    keine Rechte    ");
          lcd.setCursor(0, 3);
          lcd.print("                    "); 
          delay(1000);
          lcd.setCursor(0, 2);
          lcd.print("                    ");  
          wdt_reset();             
          mfrc522.PICC_HaltA();
          mfrc522.PCD_StopCrypto1(); 
           digitalWrite(ledPin,LOW);
          return;
          }
        } 
      }
     
  }
  
if(locked==false){

  if(modus==2&&(aktuelle_millis-entsperrzeit>=sperrzeit)){ 
  Anzeige_update =false;
  Anzeige_Nanoclean =false;
  Anzeige_Dekon =false;
  Anzeige_Lifecleaner =false;
  Anzeige_Blutwaesche =false;
  Anzeige_Cleanray =false;
  Anzeige_drawback =false;
  Serial2.println("p");
  locked=true;
  
   menue_print_lcd(modus,0);  
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
  
            for (byte j = 0; j < mfrc522.uid.size; j++) {
                id_buffer[j]=mfrc522.uid.uidByte[j];
                //    Serial.print(id_buffer[j] < 0x10 ? " 0" : " ");
                //    Serial.print(id_buffer[j], HEX);
                }
                //Serial.println();


int x=0;
if(memcmp(id_buffer, known_id[9], sizeof(id_buffer)) == 0){
                known=true;x=1;delay(500);
                }
if(memcmp(id_buffer, known_id[8], sizeof(id_buffer)) == 0){
                known=true;x=1;delay(500);
                }
if(memcmp(id_buffer, known_id[7], sizeof(id_buffer)) == 0){
                known=true;x=1;delay(500);
                }
if(memcmp(id_buffer, known_id[6], sizeof(id_buffer)) == 0){
                known=true;x=1;delay(500);
                }                
if(memcmp(id_buffer, known_id[5], sizeof(id_buffer)) == 0){
                known=true;x=1;delay(500);
                }
if(memcmp(id_buffer, known_id[0], sizeof(id_buffer)) == 0){
                known=true;x=2;delay(500);
                }  
if(memcmp(id_buffer, known_id[1], sizeof(id_buffer)) == 0){
                known=true;x=2;delay(500);
                }    
if(memcmp(id_buffer, known_id[2], sizeof(id_buffer)) == 0){
                known=true;x=2;delay(500);
                }  
if(memcmp(id_buffer, known_id[3], sizeof(id_buffer)) == 0){
                known=true;x=2;delay(500);
                }  
if(memcmp(id_buffer, known_id[4], sizeof(id_buffer)) == 0){
                known=true;x=2;delay(500);
                } 
  
if(known==true){
  digitalWrite(ledPin,HIGH);
  buzzer_play( 1,100);
  if(x==1){
  modus=modus+1;
  
                     if(modus>2){modus=0;}
                     else if(modus<=0){modus=2;}
                     
                     if(ziel_long>2){ziel_long=0;}
                     
                     SD.remove("moduslog.txt");
                     moduslog = SD.open("moduslog.txt", FILE_WRITE);
                      if (moduslog) {
                        Serial.println(F("Writing to moduslog..."));
                        
                        moduslog.println(modus);
                        lcd.clear();
                        delay(50);
                        //modus=ziel_long;
                        lcd.setCursor(0,0);
                        
   if (modus==0){

    locked=false;
    counterx = 0;
    }    
   if (modus==1){
    
    locked=false;
    counterx = 0;
     }  
   if (modus==2){
    
    locked=true;
    counterx = 0;
    } 
                        moduslog.close();
                           Serial2.print("y");Serial2.print(modus);Serial2.write('\n');
             
                          }

                       else {
                    
                        myprint("moduslog.txt nicht vorhanden","","",true,true,false,1,port);
                      }
                   menue_print_lcd(modus,0);   
                   ziel_long=0;
                   mfrc522.PICC_HaltA();
            mfrc522.PCD_StopCrypto1(); 
            digitalWrite(ledPin,LOW);
    }        
if(x==2){
              lcd_print_medi_log();
              wdt_reset();
              mfrc522.PICC_HaltA();
              mfrc522.PCD_StopCrypto1(); 
              //digitalWrite(ledPin,LOW); 

}
    known=false;
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
    lcd.setCursor(0,0);
      lcd.print(infos[0]);
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
      lcd.setCursor(0,0);
      lcd.print(infos[1]);
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
      lcd.setCursor(0,0);
      lcd.print(infos[1]);
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
     lcd.setCursor(0,0);
      lcd.print(infos[2]);
      rfid_reset();
      reset_variablen();
      Tag_analyse(10,1);           
      ziel_char=' ';
      ziel_long=0;
      flow=1;
    
    break;

//Medikamtent buchen
      case 'b':
      buzzer_play( 1,100);
     // Serial.print("Grund:");Serial.println(Medi[ziel_long-1]);
      lcd.setCursor(0,0);
      lcd.print(infos[3]);
      if(ziel_long>0&&ziel_long<8){
         if(ziel_long>1&&ziel_long<=7){
              check_medi_log();
          }
      medibuchung(ziel_long);
      booking_save();
      //reset_variablen();
  
      Tag_analyse(10,0);
      myprint("------------------------------------------------","","",true,true,false,1,port);
      
      if(ziel_long>1&&ziel_long<=7){
            SD.remove("medi.txt");
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
 /*     
//Typus aendern
    case 'm':  
      buzzer_play( 1,100);
      Typus_aendern(ziel_long);
      //100 fuer Mensch
      //250 Bunkerbewohner
      //360 fuer Mutant  
      ziel_char=' ';
      ziel_long=0;
      flow=1;

    break;   
*/


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
    lcd.clear();
    if(msg1!=""){
  
       myprint(msg1,"","",true,true,false,1,port);
       lcd.setCursor(0,0);
        lcd.print(msg1);
        }
    if(msg2!=""){
    
       myprint(msg2,"","",true,false,false,1,port);
       lcd.setCursor(0,1);
       lcd.print(msg2);
        }
    if(msg3!=""){
 
       myprint(msg3,"","",true,true,false,1,port);
       lcd.print(msg3);
        }
    if(msg4!=""){
 
       myprint(msg4,"","",true,false,false,1,port);
         lcd.setCursor(0,3);
        lcd.print(msg4);
        }
    if(msg5!=""){

       myprint(msg5,"","",true,true,false,1,port);
       lcd.print(msg5);
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
    lcd.clear();
    ebene=false;// zurueck zum startbild
     menue_print_lcd(modus,0);  
    flow=0;
  }
}  

}
