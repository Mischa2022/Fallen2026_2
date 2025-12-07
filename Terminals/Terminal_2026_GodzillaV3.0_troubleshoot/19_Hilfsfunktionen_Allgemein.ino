/*Auflistung Unterfunktionen, die von anderen Funktionen benoetigt werden
 * 
 * reset_variablen // 2025 loeschen aller zwischengepeicherten Werte aus den Variablen
 * buzzer_play     // 2025 fuer toene
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
    /*   msg1="";
     msg2="";
     msg3="";
     msg4="";
     msg5="";
     msg6="";*/
   //  counterx = 0;
   
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
