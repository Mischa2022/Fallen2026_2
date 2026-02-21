/*Auflistung Unterfunktionen, die von anderen Funktionen benötigt werden
 * 
 * reset_variablen //löschen aller zwischengepeicherten Werte aus den Variablen
 * buzzer_play // für töne
 * relais_switch // für relais und anzeigeservo
 */
 


int reset_variablen(){

  memset( NanoClean_read, 0, sizeof( NanoClean_read));
  memset( Dekon_read, 0, sizeof( Dekon_read));
  memset( LifeCleaner_read, 0, sizeof( LifeCleaner_read));
  memset( Cleanray_read, 0, sizeof( Cleanray_read));
  memset( BloodClean_read, 0, sizeof( BloodClean_read));
  memset( knownKeys[last_key], 0, sizeof(knownKeys[last_key]));
  memset( Speicherwerte_Konfig,0, sizeof(Speicherwerte_Konfig)); 
  memset( Speicherwerte_Konfigread,0, sizeof(Speicherwerte_Konfigread)); 
  test=0;
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
  msg1="";
  msg2="";
  msg3="";
  msg4="";
  
  sorte=0;
  
    mfrc522.PICC_HaltA();   //finale stopfunktion
    mfrc522.PCD_StopCrypto1();//finale stopfunktion

}

//*****************************************************************************************//


void buzzer_play( int replay,int run_time){
 
  
  for (int x=0; x<replay;x++){
    
    digitalWrite(buzzer_pin,HIGH);
    delay(run_time);
    
    digitalWrite(buzzer_pin,LOW);
    delay(run_time);
  }
}
//*****************************************************************************************//
int relais_switch(unsigned long state,long pause){
  int servo_value2;
  int relais;
            if(state==0)             {      relais=0;       } //farblos
            if(state>=1&&state<=50)  {      relais=1;       } //grün1
            if(state>50&&state<=100) {      relais=2;       } //grün2
            if(state>100&&state<=150){      relais=3;       } //grün3
            if(state>150&&state<=200){      relais=4;       } //gelb1
            if(state>200&&state<=250){      relais=5;       } //gelb2
            if(state>250&&state<=300){      relais=6;       } //gelb3
            if(state>300&&state<=350){      relais=7;       } //rot1
            if(state>350&&state<=400){      relais=8;       } //rot2
            if(state>400)            {      relais=9;       } //rot3


servo_value2 = map(state, 0, 450, 180, 0);
      
switch(relais){
  case 0: digitalWrite(relaisPin[1], geschaltet);
          digitalWrite(relaisPin[2], geschaltet);
          digitalWrite(relaisPin[3], geschaltet);
           
          servo_value2=175;
  break;
  
  case 1: digitalWrite(relaisPin[1],!geschaltet);
          digitalWrite(relaisPin[2], geschaltet);
          digitalWrite(relaisPin[3], geschaltet);
          
          servo_value2=160;
  break;
  
  case 2: digitalWrite(relaisPin[1], !geschaltet);
          digitalWrite(relaisPin[2], geschaltet);
          digitalWrite(relaisPin[3], geschaltet);
           
          servo_value2=140;
  break;
  
  case 3: digitalWrite(relaisPin[1], !geschaltet);
          digitalWrite(relaisPin[2], geschaltet);
          digitalWrite(relaisPin[3], geschaltet);
          
          servo_value2=120;
  break;
  
  case 4: digitalWrite(relaisPin[1], geschaltet);
          digitalWrite(relaisPin[2], !geschaltet);
          digitalWrite(relaisPin[3], geschaltet);
          
          servo_value2=100;
  break;
  
  case 5: digitalWrite(relaisPin[1], geschaltet);
          digitalWrite(relaisPin[2], !geschaltet);
          digitalWrite(relaisPin[3], geschaltet);
          
          servo_value2=80;
  break;
  
  case 6: digitalWrite(relaisPin[1], geschaltet);
          digitalWrite(relaisPin[2], !geschaltet);
          digitalWrite(relaisPin[3], geschaltet);
          
          servo_value2=60;
  break;
  
  case 7: digitalWrite(relaisPin[1], geschaltet);
          digitalWrite(relaisPin[2], geschaltet);
          digitalWrite(relaisPin[3], !geschaltet);
          
          servo_value2=40;
  break;
  
  case 8: digitalWrite(relaisPin[1], geschaltet);
          digitalWrite(relaisPin[2], geschaltet);
          digitalWrite(relaisPin[3], !geschaltet);
          
          servo_value2=20;
  break;
  
  case 9: digitalWrite(relaisPin[1], geschaltet);
          digitalWrite(relaisPin[2], geschaltet);
          digitalWrite(relaisPin[3], !geschaltet);
          
          servo_value2=5;
  break;
}


  myservo_anzeige.write(servo_value2);
          delay(pause);
          digitalWrite(relaisPin[1], geschaltet);
          digitalWrite(relaisPin[2], geschaltet);
          digitalWrite(relaisPin[3], geschaltet);

}

//*****************************************************************************************//
