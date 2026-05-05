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
     msg1="";
     msg2="";
     msg3="";
     msg4="";
     msg5="";
     msg6="";
     //counterx = 0;
     sorte=0;
     //raywert=0;
    myprint("","","",true,true,false,1,port);
    pixels1.clear();
    pixels2.clear();
    pixels1.show();
    pixels2.show();
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



      
switch(relais){
  case 0: digitalWrite(relaisPin[1], geschaltet);
          digitalWrite(relaisPin[2], geschaltet);
          digitalWrite(relaisPin[3], geschaltet);

          servo_value2=165;

  break;
  
  case 1: digitalWrite(relaisPin[1],!geschaltet);
          digitalWrite(relaisPin[2], geschaltet);
          digitalWrite(relaisPin[3], geschaltet);

          servo_value2=155;

  break;
  
  case 2: digitalWrite(relaisPin[1], !geschaltet);
          digitalWrite(relaisPin[2], geschaltet);
          digitalWrite(relaisPin[3], geschaltet);

          servo_value2=145;

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

          servo_value2=90;

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

          servo_value2=30;

  break;
  
  case 9: digitalWrite(relaisPin[1], geschaltet);
          digitalWrite(relaisPin[2], geschaltet);
          digitalWrite(relaisPin[3], !geschaltet);
 
          servo_value2=10;


  break;
}

myservo_anzeige.attach(11);

for (int x=0;x<=servo_value2;x++){
myservo_anzeige.write(x);

delay(5);
}

delay(100);
myservo_anzeige.detach();

myservo_wippe.attach(13);
myservo_wippe.write(servo_value);
delay(100);
myservo_wippe.detach();

        
          delay(pause);
          digitalWrite(relaisPin[1], geschaltet);
          digitalWrite(relaisPin[2], geschaltet);
          digitalWrite(relaisPin[3], geschaltet);

}

//*****************************************************************************************//

void blinki(int muster, int farbe,int neo){

#define DELAYVAL 50 // Time (in milliseconds) to pause between pixels
int r,g,b;
int intens=50; //farbstärke
int pixels;//auswahl welcher led-ring
pixels1.clear();
pixels1.show(); 
pixels2.clear();
pixels2.show(); 
if(muster==99){
  muster=random(0,4);
  }
  
if(farbe==99){
    farbe=random(0,6);
}
    if(farbe==0){r=intens;g=0;b=0;}
    if(farbe==1){r=0;g=intens;b=0;}
    if(farbe==2){r=0;g=0;b=intens;}
    if(farbe==3){r=intens;g=intens;b=0;}
    if(farbe==4){r=0;g=intens;b=intens;}
    if(farbe==5){r=intens;g=0;b=intens;}


if(neo==1){

pixels1.clear();
  
if(muster==0){


    
  for(int i=0; i<NUMPIXELS; i++) {
    pixels2.setPixelColor(i, pixels2.Color(r, g, b));
    pixels2.show();   
    delay(DELAYVAL); 
      }
  for(int i=NUMPIXELS; i>=0; i--) {
    pixels2.setPixelColor(i, pixels2.Color(0, 0, 0));
    pixels2.show();   
    delay(DELAYVAL); 
      }  

  }

if(muster==1){

  
   for(int i=0; i<13; i++) {
    pixels2.setPixelColor(i, pixels2.Color(r, g, b));
    pixels2.setPixelColor(23-i, pixels2.Color(r, g, b));
    pixels2.show();   
    delay(DELAYVAL); 
    }
 
  }

if(muster==2){


   for(int i=0; i<14; i++) {
    pixels2.setPixelColor(i, pixels2.Color(r, g, b));
    pixels2.setPixelColor(i-1, pixels2.Color(0, 0, 0));
    pixels2.setPixelColor(13+i, pixels2.Color(r, g, b));
    pixels2.setPixelColor(12+i, pixels2.Color(0, 0, 0));
    pixels2.show();   
    delay(DELAYVAL); 
    }

  }

if(muster==3){


   for(int i=12; i<25; i++) {
    pixels2.setPixelColor(i, pixels2.Color(r, g, b));
    pixels2.setPixelColor(24-i, pixels2.Color(r, g, b));
    pixels2.show();   
    delay(DELAYVAL); 
    }

  }
 
}
else{
pixels2.clear(); 

if(muster==0){


    
  for(int i=0; i<NUMPIXELS; i++) {
    pixels1.setPixelColor(i, pixels1.Color(r, g, b));
    pixels1.show();   
    delay(DELAYVAL); 
      }
  for(int i=NUMPIXELS; i>=0; i--) {
    pixels1.setPixelColor(i, pixels1.Color(0, 0, 0));
    pixels1.show();   
    delay(DELAYVAL); 
      }  

  }

if(muster==1){

  
   for(int i=0; i<13; i++) {
    pixels1.setPixelColor(i, pixels1.Color(r, g, b));
    pixels1.setPixelColor(23-i, pixels1.Color(r, g, b));
    pixels1.show();   
    delay(DELAYVAL); 
    }

  }

if(muster==2){


   for(int i=0; i<14; i++) {
    pixels1.setPixelColor(i, pixels1.Color(r, g, b));
    pixels1.setPixelColor(i-1, pixels1.Color(0, 0, 0));
    pixels1.setPixelColor(13+i, pixels1.Color(r, g, b));
    pixels1.setPixelColor(12+i, pixels1.Color(0, 0, 0));
    pixels1.show();   
    delay(DELAYVAL); 
    }

  }

if(muster==3){


   for(int i=12; i<25; i++) {
    pixels1.setPixelColor(i, pixels1.Color(r, g, b));
    pixels1.setPixelColor(24-i, pixels1.Color(r, g, b));
    pixels1.show();   
    delay(DELAYVAL); 
    }

  }

}  

}
