/*Auflistung Unterfunktionen, die von anderen Funktionen benötigt werden
 * 
 * reset_variablen //löschen aller zwischengepeicherten Werte aus den Variablen
 * buzzer_play // für töne
 * relais_switch // für relais und anzeigeservo
 */
 
//*****************************************************************************************//

void myprint(char*titel,String inhalt,unsigned long wert,bool wp,bool ln,bool unix,int debuglevel,int ausgabe){

ausgabe=0;//aushebeln der esp_schnittstelle. Aktuell nicht nötig
 
//  myprint(Text:"",Text2:"",Wert:"",writeorprint:false,ln_on:true,unix_on:false,debug:1,port:0);
  
  
 // myprint(Text:"Nun Dongel auflegen",Text2:""          ,""                 ,false    ,true     ,false      ,1              ,0);
  //myprint(char*titel           ,char*inhalt ,unsigned long wert ,bool wp  ,bool ln  ,bool unix  ,int debuglevel ,int ausgabe){
  /*titel= bezeichnung der Ausgabe
   * inhalt = falls text und keine werte
   * wert = ausgabewerte
   * wp = write ==0 print ==1
   * ln = neue line oder nicht
   * unix= long konvertieren oder nur als wert ausgeben
   * debuglevel = falls ausgabe nur in bestimmten situationen erwünscht
   * ausgabe= auswahl des seriellen ports
   */
  
  if(debuglevel>=debug){

    if(ausgabe==0){
      
        if(titel!=""){
        Serial.print(titel);
          } 
        if(inhalt!=""){
        Serial.print(inhalt);
          }
        if(wert!=""){
          if(unix==false){
          Serial.print(wert);
            }
          if(unix==true){
          unix_converter(wert,UTC);  
            }
          }
          
      if(ln==true){
        Serial.println("");
      }
      else{
        Serial.print("");
      }    
    }
//************************************************************
    if(ausgabe==1){
      
      if(titel!=""){
      Serial1.print(titel);
      } 
        if(inhalt!=""){
        Serial1.print(inhalt);
        }
        if(wert!=""){
          if(unix==false){
          Serial1.print(wert);
          }
          if(unix==true){
          unix_converter(wert,UTC);  
          }
        }
      if(ln==true){
        Serial1.println("");
      }
      else{
        Serial1.print("");
      }    
    }
//************************************************************
    if(ausgabe==2){
      
      if(titel!=""){
      Serial2.print(titel);delay(10);
      } 
        if(inhalt!=""){
        Serial2.print(inhalt);delay(10);
        }
        if(wert!=""){
          if(unix==false){
          Serial2.print(wert);delay(10);
          }
          if(unix==true){
          unix_converter(wert,UTC);  
          }
        }
      if(ln==true){
        Serial2.println("");delay(10);
      }
      else{
        Serial2.print("");delay(10);
      }    
    }
//************************************************************
    if(ausgabe==3){
      
        if(titel!=""){
        Serial3.write(titel);//delay(50);
          } 
        if(inhalt!=""){
         Serial3.print(inhalt);//delay(50);
          }
        if(wert!=""){
          if(unix==false){
          Serial3.print(wert);//delay(50);
            }
          if(unix==true){
          unix_converter(wert,UTC);  
            }
          }
          
      if(ln==true){
        Serial3.write('\n');delay(50);
      }
      else{
        Serial3.write("");delay(50);
      }    
    }
  }
}
//************************************************************   

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
void blinken(){
  
    
    digitalWrite(ledPin1,HIGH);
    delay(1000);
    
    digitalWrite(ledPin1,LOW);
    delay(1000);
  
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
//  pixels2.clear(); // Set all pixel colors to 'off'

    
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
   //   pixels2.clear();
   //   pixels2.show();  
  }

if(muster==1){
//  pixels2.clear(); // Set all pixel colors to 'off'
  
   for(int i=0; i<13; i++) {
    pixels2.setPixelColor(i, pixels2.Color(r, g, b));
    pixels2.setPixelColor(23-i, pixels2.Color(r, g, b));
    pixels2.show();   
    delay(DELAYVAL); 
    }
 //   pixels2.clear();
 //   pixels2.show();  
  }

if(muster==2){
 // pixels2.clear(); // Set all pixel colors to 'off'

   for(int i=0; i<14; i++) {
    pixels2.setPixelColor(i, pixels2.Color(r, g, b));
    pixels2.setPixelColor(i-1, pixels2.Color(0, 0, 0));
    pixels2.setPixelColor(13+i, pixels2.Color(r, g, b));
    pixels2.setPixelColor(12+i, pixels2.Color(0, 0, 0));
    pixels2.show();   
    delay(DELAYVAL); 
    }
//    pixels2.clear();
  }

if(muster==3){
//  pixels2.clear(); // Set all pixel colors to 'off'

   for(int i=12; i<25; i++) {
    pixels2.setPixelColor(i, pixels2.Color(r, g, b));
    pixels2.setPixelColor(24-i, pixels2.Color(r, g, b));
    pixels2.show();   
    delay(DELAYVAL); 
    }
//    pixels2.clear();
  }
 
}
else{
pixels2.clear(); 

if(muster==0){
//  pixels1.clear(); // Set all pixel colors to 'off'

    
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
  //    pixels1.clear();
  }

if(muster==1){
 // pixels1.clear(); // Set all pixel colors to 'off'
  
   for(int i=0; i<13; i++) {
    pixels1.setPixelColor(i, pixels1.Color(r, g, b));
    pixels1.setPixelColor(23-i, pixels1.Color(r, g, b));
    pixels1.show();   
    delay(DELAYVAL); 
    }
//    pixels1.clear();
  }

if(muster==2){
//  pixels1.clear(); // Set all pixel colors to 'off'

   for(int i=0; i<14; i++) {
    pixels1.setPixelColor(i, pixels1.Color(r, g, b));
    pixels1.setPixelColor(i-1, pixels1.Color(0, 0, 0));
    pixels1.setPixelColor(13+i, pixels1.Color(r, g, b));
    pixels1.setPixelColor(12+i, pixels1.Color(0, 0, 0));
    pixels1.show();   
    delay(DELAYVAL); 
    }
//    pixels1.clear();
  }

if(muster==3){
//  pixels1.clear(); // Set all pixel colors to 'off'

   for(int i=12; i<25; i++) {
    pixels1.setPixelColor(i, pixels1.Color(r, g, b));
    pixels1.setPixelColor(24-i, pixels1.Color(r, g, b));
    pixels1.show();   
    delay(DELAYVAL); 
    }
 //   pixels1.clear();
  }
 // pixels1.clear();
}  

}
