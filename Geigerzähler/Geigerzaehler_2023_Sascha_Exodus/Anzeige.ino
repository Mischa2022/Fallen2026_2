/*Auflistung Unterfunktionen, die von anderen Funktionen benötigt werden
 * 
 * anzeige //steuert led, buzzer und strom für analoge anzeige
 * buzzer_play // für töne
 */
//*****************************************************************************************//
void random_SEG(int timer, int recall){

 byte SEG_random[][6] = {
  {SEG_B| SEG_C|SEG_D|SEG_E|SEG_F|SEG_G },    
  {SEG_A|  SEG_C|SEG_D|SEG_E|SEG_F|SEG_G },  
  {SEG_A| SEG_B| SEG_D|SEG_E|SEG_F|SEG_G },  
  {SEG_A| SEG_B| SEG_C|SEG_E|SEG_F|SEG_G },  
  {SEG_A| SEG_B| SEG_C|SEG_D|SEG_F|SEG_G },  
  {SEG_A| SEG_B| SEG_C|SEG_D|SEG_E|SEG_G },  
  {SEG_A| SEG_B| SEG_C|SEG_D|SEG_E|SEG_F}    
   
  };

  
  for (int x=0;x<=recall;x++){
  randomSeed(analogRead(0));
  display.setSegments(SEG_random[random(0,6)],1,0);
  randomSeed(analogRead(0));
  display.setSegments(SEG_random[random(0,6)],1,1);
  randomSeed(analogRead(0));
  display.setSegments(SEG_random[random(0,6)],1,2);
  randomSeed(analogRead(0));
  display.setSegments(SEG_random[random(0,6)],1,3);
  
  delay(timer);
  display.clear();
}
}

//*****************************************************************************************//
void anzeige(unsigned long basis){
int pause;
int wiederholung;

if (basis>=450){basis=449;}


          
analoge_anzeige(basis); //funktion um analoge anzeige anzusteuern

//buzzerplay
pause= 500-basis;
//Serial.print("pause:");Serial.println(pause);
wiederholung=2000/(2*pause);


buzzer_play(wiederholung,pause); 
//delay(500);
//analoge_anzeige(0);

}
 
//**************************************************************************************************************************************


void buzzer_play( int replay,int run_time){
 
  
  for (int x=0; x<replay;x++){
    
    digitalWrite(buzzer_pin,HIGH);
    delay(run_time);
    
    digitalWrite(buzzer_pin,LOW);
    delay(run_time);
  }
}

//*****************************************************************************************//
int analoge_anzeige(int basis_wert ){
int messwert_anzeige;
messwert_anzeige=map(basis_wert,0,450,0,1024);
 
 y=basis_wert;
 y=map(messwert_anzeige,0,1024,0,255);
 if(y >254){y=254;}

  if(y >254){y=254;}
  if(y <1){y=0;}
   
if(y!=oldt){

if(y<=85){digitalWrite(LED1_Pin,LOW);digitalWrite(LED2_Pin,HIGH);digitalWrite(LED3_Pin,LOW);}
if(y>85&&y<=170){digitalWrite(LED1_Pin,LOW);digitalWrite(LED2_Pin,LOW);digitalWrite(LED3_Pin,HIGH);}
if(y>170){digitalWrite(LED1_Pin,HIGH);digitalWrite(LED2_Pin,LOW);digitalWrite(LED3_Pin,LOW);}

  if(t<y){
    for( t=oldt;t<=y;t++){  
 analogWrite(analogeAnzeige_Pin,t);
 delay(5);
  if(t==oldt){
      oldt=y;
    }
   }
  }
    if(t>y){
    for( t=oldt;t>=y;t--){  
 analogWrite(analogeAnzeige_Pin,t);
 delay(5);
    if(t==oldt){
      oldt=y;
    }
   }
  }
 }  
  delay(200);
 digitalWrite(LED1_Pin,LOW);digitalWrite(LED2_Pin,LOW);digitalWrite(LED3_Pin,LOW);  
}
//*****************************************************************************************//
