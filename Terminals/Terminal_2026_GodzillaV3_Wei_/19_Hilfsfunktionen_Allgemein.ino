/*Auflistung Unterfunktionen, die von anderen Funktionen benoetigt werden
 * 
 * reset_variablen // 2025 loeschen aller zwischengepeicherten Werte aus den Variablen
 * buzzer_play     // 2025 fuer toene
 * prozess         // 2025 fuer die LCDausgabe um bewegung zu zeigen
 * rechte_check    // 2025 ueberpruefen ob ein Dongel fuer Buchungen Rechte enthaelt
 */
 


int reset_variablen(){
  wdt_reset();
  memset( NanoClean_read, 0, sizeof( NanoClean_read));
  memset( Dekon_read, 0, sizeof( Dekon_read));
  memset( LifeCleaner_read, 0, sizeof( LifeCleaner_read));
  memset( Cleanray_read, 0, sizeof( Cleanray_read));
  memset( BloodClean_read, 0, sizeof( BloodClean_read));
  memset( knownKeys[last_key], 0, sizeof(knownKeys[last_key]));
  memset( Speicherwerte_Konfig,0, sizeof(Speicherwerte_Konfig)); 
 // memset( Speicherwerte_Konfigread,0, sizeof(Speicherwerte_Konfigread)); 
  ziel_long=0;
  ziel_char=' '; 
  ray_writing=0;
  buchungsgrund="";
  buchungsgrund2="";
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
  rights=0; 
  LifeCleaner_effekt_read=0;     
  Con_Start_read=0;
  Last_Booking_read=0;             
  Ray_value_intern_read=0;
  Ray_value_extern_read=0;
  error=0;
  ergebnis=0;
  feedback=0;
  typus=0;
  read_String2="";
 /*      msg1="";
     msg2="";
     msg3="";
     msg4="";
     msg5="";
     msg6="";*/
     counterx = 0;
       myprint("","","",true,true,false,1,port);


}

//**************************************************************************************************************************************


void buzzer_play( int replay,int run_time){
 wdt_reset();
  
  for (int x=0; x<replay;x++){
    
    digitalWrite(buzzer_pin,HIGH);
    delay(run_time);
    
    digitalWrite(buzzer_pin,LOW);
    delay(run_time);
  }
}
//*****************************************************************************************//
int prozess(){
  char* zeichen[] {"|","/","-","|","/","-","|","/","-"};
wdt_reset();
 if (modus!=0){
  lcd.setCursor(0,1);
  lcd.print("Prozess:");
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print("                    ");
    for(int x=0;x<8;x++){
      lcd.setCursor(8,1);
      lcd.print(zeichen[x]);
      delay(50);
    }
    }  
  }
//*****************************************************************************************//

  void rechte_check(long rechte_basis){
  long buffer_wert[6];
wdt_reset();
Anzeige_update =true;//automatisch immer frei, sobald Rechte vorhanden
Anzeige_drawback =true;//automatisch immer frei, sobald Rechte vorhanden

//Serial.println("NBCLD");

if(rechte_basis>=10000){Anzeige_Nanoclean =true;buffer_wert[0]=rechte_basis-10000;}
else{Anzeige_Nanoclean =false;buffer_wert[0]=rechte_basis;}

if(buffer_wert[0]>=1000&&buffer_wert[0]<10000){Anzeige_Blutwaesche =true;buffer_wert[1]=buffer_wert[0]-1000;}
else{Anzeige_Blutwaesche =false;buffer_wert[1]=buffer_wert[0];}

if(buffer_wert[1]>=100&&buffer_wert[1]<1000){Anzeige_Cleanray =true;buffer_wert[2]=buffer_wert[1]-100;}
else{Anzeige_Cleanray =false;buffer_wert[2]=buffer_wert[1];}

if(buffer_wert[2]>=10&&buffer_wert[2]<100){Anzeige_Lifecleaner =true;buffer_wert[3]=buffer_wert[2]-10;}
else{Anzeige_Lifecleaner =false;buffer_wert[3]=buffer_wert[2];}

if(buffer_wert[3]>=1&&buffer_wert[3]<10){Anzeige_Dekon =true;}
else{Anzeige_Dekon =false;}

/*

Serial.print("Nano:");Serial.println(Anzeige_Nanoclean);
Serial.print("Blood:");Serial.println(Anzeige_Blutwaesche);
Serial.print("Clean:");Serial.println(Anzeige_Cleanray);
Serial.print("Life:");Serial.println(Anzeige_Lifecleaner);
Serial.print("Deko:");Serial.println(Anzeige_Dekon);
Serial.print("Update:");Serial.println(Anzeige_update);
Serial.print("Draw:");Serial.println(Anzeige_drawback);
*/
entsperrzeit=millis();
//Serial.print("Entsperrzeit:");Serial.println(entsperrzeit);
//Serial.print("Locked:");Serial.println(locked);

locked=0;
menue_print_lcd(modus,0); 
 } 
