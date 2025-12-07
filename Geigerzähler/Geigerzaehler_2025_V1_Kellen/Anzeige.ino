/*Auflistung Unterfunktionen, die von anderen Funktionen benötigt werden
 * 
 * anzeige //steuert led, buzzer und strom für analoge anzeige
 * buzzer_play // für töne
 */

void anzeige(unsigned long basis){
int pause;
int wiederholung;

if (basis>=450){basis=449;}

        if(basis==0){}
        if(basis>0&&basis<=50){
          digitalWrite(LED_G_Pin,led_on);
          }  
        if(basis>50&&basis<=100){
          digitalWrite(LED_G_Pin,led_on);
          } 
        if(basis>100&&basis<=150){
          digitalWrite(LED_G_Pin,led_on);
          }  
        if(basis>150&&basis<=200){
          digitalWrite(LED_R_Pin,led_on);
          digitalWrite(LED_G_Pin,led_on);
          } 
        if(basis>200&&basis<=250){
          digitalWrite(LED_R_Pin,led_on);
          digitalWrite(LED_G_Pin,led_on);
          } 
        if(basis>250&&basis<=300){
          digitalWrite(LED_R_Pin,led_on);
          digitalWrite(LED_G_Pin,led_on);
          } 
        if(basis>300&&basis<=350){
          digitalWrite(LED_R_Pin,led_on);
          } 
        if(basis>350&&basis<=400){
          digitalWrite(LED_R_Pin,led_on);
          } 
        if(basis>400){
          digitalWrite(LED_R_Pin,led_on);
          } 
          
analoge_anzeige(basis); //funktion um analoge anzeige anzusteuern

//buzzerplay
pause= 500-basis;
//Serial.print("pause:");Serial.println(pause);
wiederholung=2000/(2*pause);


buzzer_play(wiederholung,pause); 

 digitalWrite(LED_R_Pin,!led_on);
 digitalWrite(LED_G_Pin,!led_on);
 digitalWrite(LED_B_Pin,!led_on); 
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
}

//*****************************************************************************************//

//*****************************************************************************************//

//**************************************************************************************************************************************
