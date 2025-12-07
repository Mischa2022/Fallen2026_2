/*Auflistung Unterfunktionen, die von anderen Funktionen benötigt werden
 * 
 * anzeige //steuert led, buzzer und strom für analoge anzeige
 * buzzer_play // für töne
 */

void anzeige(unsigned long basis){

int wiederholung=0;
int pause;
int farbe=1;
int r,g,b;
int intens=50; //farbstärke


if (basis>=450){basis=449;}
if(basis==0){}
//if(basis!=0){ buzzer_play(1,100); }

wiederholung=(basis/50)+1;

if(wiederholung==2||wiederholung==5||wiederholung==8){intens=100;}
if(wiederholung==3||wiederholung==6||wiederholung==9){intens=255;}


farbe=(basis/150)+1;
if( farbe==0){farbe=1;}
if(farbe==1){r=0;g=intens;b=0;pause=500;}
if(farbe==2){r=intens;g=intens;b=0;pause=350;}
if(farbe==3){r=intens;g=0;b=0;pause=200;}

for(int x=0;x<wiederholung;x++){

           pixels.setPixelColor(0,pixels.Color(r,g,b));
         pixels.show();
         delay(pause);
         pixels.setPixelColor(0,pixels.Color(0, 0, 0));
         pixels.show();
         delay(pause);
}
      
       /*
        if(basis>0&&basis<=50){
         Serial.println("hellgrün");
         pixels.setPixelColor(0,pixels.Color(0, 50, 0));
         pixels.show();
         delay(500);
          }  
          
        if(basis>50&&basis<=100){
         Serial.println("grün");
         pixels.setPixelColor(0,pixels.Color(0, 100, 0));
         pixels.show();
         delay(500);
         pixels.setPixelColor(0,pixels.Color(0, 0, 0));
         pixels.show();
         delay(500);
         pixels.setPixelColor(0,pixels.Color(0, 100, 0));
         pixels.show();
          } 
          
        if(basis>100&&basis<=150){
         Serial.println("dunkelgrün");
         pixels.setPixelColor(0,pixels.Color(0, 255,0));
         pixels.show();
         delay(500);
         pixels.setPixelColor(0,pixels.Color(0, 0, 0));
         pixels.show();
         delay(500);
         pixels.setPixelColor(0,pixels.Color(0, 255, 0));
         pixels.show();
         delay(500);
         pixels.setPixelColor(0,pixels.Color(0, 0, 0));
         pixels.show();
         delay(500);
         pixels.setPixelColor(0,pixels.Color(0, 255, 0));
         pixels.show();
          }  
          
        if(basis>150&&basis<=200){
          Serial.println("hellgelb");
          pixels.setPixelColor(0,pixels.Color(50, 50, 0));
          pixels.show();
          delay(1000);
          } 
          
        if(basis>200&&basis<=250){
         Serial.println("gelb");
         pixels.setPixelColor(0,pixels.Color(100,100, 0));
         pixels.show();
         delay(500);
         pixels.setPixelColor(0,pixels.Color(0, 0, 0));
         pixels.show();
         delay(500);
         pixels.setPixelColor(0,pixels.Color(100,100, 0));
         pixels.show();
          } 
          
        if(basis>250&&basis<=300){
         Serial.println("dunkelgelb");
         pixels.setPixelColor(0,pixels.Color(150,150, 0));
         pixels.show();
         delay(500);
         pixels.setPixelColor(0,pixels.Color(0, 0, 0));
         pixels.show();
         delay(500);
         pixels.setPixelColor(0,pixels.Color(150,150, 0));
         pixels.show();
         delay(500);
         pixels.setPixelColor(0,pixels.Color(0, 0, 0));
         pixels.show();
         delay(500);
         pixels.setPixelColor(0,pixels.Color(150,150, 0));
         pixels.show();
          } 
          
        if(basis>300&&basis<=350){
         Serial.println("hellrot");
         pixels.setPixelColor(0,pixels.Color(50, 0, 0));
         pixels.show();
         delay(1000);
          } 
          
        if(basis>350&&basis<=400){
         Serial.println("rot");
         pixels.setPixelColor(0,pixels.Color(100, 0, 0));
         pixels.show();
         delay(500);
         pixels.setPixelColor(0,pixels.Color(0, 0, 0));
         pixels.show();
         delay(500);
         pixels.setPixelColor(0,pixels.Color(100, 0, 0));
         pixels.show();            
          } 
          
        if(basis>400){
         Serial.println("dunkelrot");
         pixels.setPixelColor(0,pixels.Color(255, 0, 0));
         pixels.show();
         delay(500);
         pixels.setPixelColor(0,pixels.Color(0, 0, 0));
         pixels.show();
         delay(500);
         pixels.setPixelColor(0,pixels.Color(255, 0, 0));
         pixels.show();
         delay(500);
         pixels.setPixelColor(0,pixels.Color(0, 0, 0));
         pixels.show();
         delay(500);
         pixels.setPixelColor(0,pixels.Color(255, 0, 0));
         pixels.show();
         
          } 
          
*/


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
