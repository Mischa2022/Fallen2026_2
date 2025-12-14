/*Auflistung Unterfunktionen, die von anderen Funktionen benötigt werden
 * 
 * anzeige //steuert led, buzzer und strom für analoge anzeige
 * buzzer_play // für töne
 */

void anzeige(unsigned long basis){
int pause;
int wiederholung;

if (basis>=501){basis=449;}

if(anzeige_groesse==0){
display_2(basis);
}
if(anzeige_groesse==1){
display_1(basis);
}

  if(anzeige_groesse==0){
    lcd.setCursor(17, 0);
          if(archtype_read==100){
          Serial.println(F("Mensch"));
          lcd.print("HMN");
          } 
          
          if(archtype_read==360){
          Serial.println(F("Mutant"));
          lcd.print("MUT");
          }
          
          if(archtype_read==250){
          lcd.print("BKR");
          }
      }
    
   if(anzeige_groesse==1){
      lcd.setCursor(13, 0);
          if(archtype_read==100){
          lcd.print("HMN");
          } 
          if(archtype_read==360){
          lcd.print("MUT");
          }
          if(archtype_read==250){
          lcd.print("BKR");
          }
      }


        if(basis==0){}
        if(basis>0&&basis<=50){
          digitalWrite(LED_G_Pin,led_on);
          analoge_anzeige(basis); //funktion um analoge anzeige anzusteuern
          pause= 500-basis;
          wiederholung=2000/(2*pause);
          buzzer_play(wiederholung,pause);
          }  
          
        if(basis>50&&basis<=100){
          digitalWrite(LED_G_Pin,led_on);
          analoge_anzeige(basis); //funktion um analoge anzeige anzusteuern
          pause= 500-basis;
          wiederholung=2000/(2*pause);
          buzzer_play(wiederholung,pause);
          } 
          
        if(basis>100&&basis<=150){
          digitalWrite(LED_G_Pin,led_on);
          analoge_anzeige(basis); //funktion um analoge anzeige anzusteuern
          pause= 500-basis;
          wiederholung=2000/(2*pause);
          buzzer_play(wiederholung,pause);
          }  
          
        if(basis>150&&basis<=200){
          digitalWrite(LED_R_Pin,led_on);
          digitalWrite(LED_G_Pin,led_on);
          analoge_anzeige(basis); //funktion um analoge anzeige anzusteuern
          pause= 500-basis;
          wiederholung=2000/(2*pause);
          buzzer_play(wiederholung,pause);
          } 
          
        if(basis>200&&basis<=250){
          digitalWrite(LED_R_Pin,led_on);
          digitalWrite(LED_G_Pin,led_on);
          analoge_anzeige(basis); //funktion um analoge anzeige anzusteuern
          pause= 500-basis;
          wiederholung=2000/(2*pause);
          buzzer_play(wiederholung,pause);
          }
          
        if(basis>250&&basis<=300){
          digitalWrite(LED_R_Pin,led_on);
          digitalWrite(LED_G_Pin,led_on);
          analoge_anzeige(basis); //funktion um analoge anzeige anzusteuern
          pause= 500-basis;
          wiederholung=2000/(2*pause);
          buzzer_play(wiederholung,pause);
          } 
          
        if(basis>300&&basis<=350){
          digitalWrite(LED_R_Pin,led_on);
          analoge_anzeige(basis); //funktion um analoge anzeige anzusteuern
          pause= 500-basis;
          wiederholung=2000/(2*pause);
          buzzer_play(wiederholung,pause);
          } 
          
        if(basis>350&&basis<=400){
          digitalWrite(LED_R_Pin,led_on);
          analoge_anzeige(basis); //funktion um analoge anzeige anzusteuern
          pause= 500-basis;
          wiederholung=2000/(2*pause);
          buzzer_play(wiederholung,pause);  
          } 
          
        if(basis>400&&basis<=450){
          digitalWrite(LED_R_Pin,led_on);
          analoge_anzeige(basis); //funktion um analoge anzeige anzusteuern
          pause= 500-basis;
          wiederholung=2000/(2*pause);
          buzzer_play(wiederholung,pause);  
          } 

        if(basis>=500){
          for( int x=0;x<5;x++){
          digitalWrite(LED_R_Pin,led_on);
          analogWrite(analogeAnzeige_Pin,255);
          delay(120);
          digitalWrite(LED_R_Pin,!led_on);
          analogWrite(analogeAnzeige_Pin,0);
          delay(120);
          }

          pause= 550-basis;
          wiederholung=2000/(2*pause);
          buzzer_play(wiederholung,pause);  
          analogWrite(analogeAnzeige_Pin,0);
          } 

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
 delay(3);
  if(t==oldt){
      oldt=y;
    }
   }
  }
    if(t>y){
    for( t=oldt;t>=y;t--){  
 analogWrite(analogeAnzeige_Pin,t);
 delay(3);
    if(t==oldt){
      oldt=y;
    }
   }
  }
 }  
}

//*****************************************************************************************//
 
void display_1(int basis_wert2) {
  
int x=0;
int pos[]={1,2,3,5,6,7,9,10,11};
float wert;
int wertx;
float werty;

uint8_t char1[8] =  {0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f}; 
uint8_t char2[8] =  {0x0,0x0,0x0,0x0,0x1f,0x1f,0x1f,0x1f};
lcd.createChar(1, char1);
lcd.createChar(2, char2);
lcd.home();

 wert=basis_wert2;
 werty= (basis_wert2/450.00*9.00);
 if(werty>9.50){werty=9.50;}
 wertx = map(wert,0,450,0,9);
 if(wertx>9){wertx=9;}

//analoge_anzeige(messwert);
 
 
for (x=0;x<wertx;x++){
 lcd.setCursor(pos[x],1);
 lcd.print((char)1);
}
for (x=9;x>=wertx;x--){
 lcd.setCursor(pos[x],1);
 lcd.print(" ");
}
 if(werty-wertx>0.00){
  lcd.setCursor(pos[wertx],1);
  lcd.print((char)2);
  }
  lcd.setCursor(12,0); //lcd.print("    ");
}   

//*****************************************************************************************//  
void display_2(int basis_wert3) {
  
int x;
int pos[3]={1,5,9};
float wert[3];
float Zahl1,Zahl2,Zahl3;
uint8_t char1[8] =  {0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f}; 

lcd.createChar(1, char1); // Sends the custom char to lcd
lcd.home();

  Zahl1 = (basis_wert3/100) ;
  Zahl2 = (basis_wert3-((basis_wert3/100)*100))/10 ;
  Zahl3 = (basis_wert3-(Zahl1*100)-(Zahl2*10));
  /*
if(basis_wert3!=0){
lcd.setCursor(12, 0);
lcd.print(basis_wert3);
}*/
//analoge_anzeige(basis_wert3); //testen ob hier ok oder in anzeige

 wert[0]=Zahl1;
 wert[1]=Zahl2;
 wert[2]=Zahl3;

for (x=0;x<=2;x++){
if( wert[x]==9.0){   
 lcd.setCursor(pos[x],3);lcd.print((char)1);      
  lcd.setCursor(pos[x],2);lcd.print((char)1);       
  lcd.setCursor(pos[x],1);lcd.print((char)1);  
  lcd.setCursor((pos[x]-1),3);lcd.print((char)1);  
  lcd.setCursor(pos[x]-1,2);lcd.print((char)1);           
  lcd.setCursor(pos[x]-1,1);lcd.print((char)1);
  lcd.setCursor((pos[x]+1),3);lcd.print((char)1); 
  lcd.setCursor(pos[x]+1,2);lcd.print((char)1);           
  lcd.setCursor(pos[x]+1,1);lcd.print((char)1);  
  }   

if( wert[x]==8.0){   
 lcd.setCursor(pos[x],3);lcd.print((char)1);      
  lcd.setCursor(pos[x],2);lcd.print((char)1);       
  lcd.setCursor(pos[x],1);lcd.print((char)1);  
  lcd.setCursor((pos[x]-1),3);lcd.print((char)1);  
  lcd.setCursor(pos[x]-1,2);lcd.print((char)1);           
  lcd.setCursor(pos[x]-1,1);lcd.print((char)1);
  lcd.setCursor((pos[x]+1),3);lcd.print((char)1); 
  lcd.setCursor(pos[x]+1,2);lcd.print((char)1);           
  lcd.setCursor(pos[x]+1,1);lcd.print(" ");  
  }   

if( wert[x]==7.0){   
  lcd.setCursor(pos[x],3);lcd.print((char)1);      
  lcd.setCursor(pos[x],2);lcd.print((char)1);       
  lcd.setCursor(pos[x],1);lcd.print((char)1);  
  lcd.setCursor((pos[x]-1),3);lcd.print((char)1);  
  lcd.setCursor(pos[x]-1,2);lcd.print((char)1);           
  lcd.setCursor(pos[x]-1,1);lcd.print(" ");
  lcd.setCursor((pos[x]+1),3);lcd.print((char)1); 
  lcd.setCursor(pos[x]+1,2);lcd.print((char)1);           
  lcd.setCursor(pos[x]+1,1);lcd.print(" ");  
  }   

if( wert[x]==6.0){   
 lcd.setCursor(pos[x],3);lcd.print((char)1);      
  lcd.setCursor(pos[x],2);lcd.print((char)1);       
  lcd.setCursor(pos[x],1);lcd.print((char)1);  
  lcd.setCursor((pos[x]-1),3);lcd.print((char)1);  
  lcd.setCursor(pos[x]-1,2);lcd.print((char)1);           
  lcd.setCursor(pos[x]-1,1);lcd.print(" ");
  lcd.setCursor((pos[x]+1),3);lcd.print((char)1); 
  lcd.setCursor(pos[x]+1,2);lcd.print(" ");           
  lcd.setCursor(pos[x]+1,1);lcd.print(" ");  
  }  

if( wert[x]==5.0){   
  lcd.setCursor(pos[x],3);lcd.print((char)1);      
  lcd.setCursor(pos[x],2);lcd.print((char)1);       
  lcd.setCursor(pos[x],1);lcd.print((char)1);  
  lcd.setCursor((pos[x]-1),3);lcd.print((char)1);  
  lcd.setCursor(pos[x]-1,2);lcd.print(" ");           
  lcd.setCursor(pos[x]-1,1);lcd.print(" ");
  lcd.setCursor((pos[x]+1),3);lcd.print((char)1); 
  lcd.setCursor(pos[x]+1,2);lcd.print(" ");           
  lcd.setCursor(pos[x]+1,1);lcd.print(" ");  
  }

if( wert[x]==4.0){   
  lcd.setCursor(pos[x],3);lcd.print((char)1);       
  lcd.setCursor(pos[x],2);lcd.print((char)1);       
  lcd.setCursor(pos[x],1);lcd.print((char)1);
  lcd.setCursor((pos[x]-1),3);lcd.print((char)1);        
  lcd.setCursor(pos[x]-1,2);lcd.print(" ");           
  lcd.setCursor(pos[x]-1,1);lcd.print(" ");
  lcd.setCursor(pos[x]+1,3);lcd.print(" ");          
  lcd.setCursor(pos[x]+1,2);lcd.print(" ");           
  lcd.setCursor(pos[x]+1,1);lcd.print(" "); 
  }

if( wert[x]==3.0){   
  lcd.setCursor(pos[x],3);lcd.print((char)1);      
  lcd.setCursor(pos[x],2);lcd.print((char)1);       
  lcd.setCursor(pos[x],1);lcd.print((char)1);       
  lcd.setCursor(pos[x]-1,3);lcd.print(" ");          
  lcd.setCursor(pos[x]-1,2);lcd.print(" ");           
  lcd.setCursor(pos[x]-1,1);lcd.print(" ");
  lcd.setCursor(pos[x]+1,3);lcd.print(" ");          
  lcd.setCursor(pos[x]+1,2);lcd.print(" ");           
  lcd.setCursor(pos[x]+1,1);lcd.print(" ");
  }

if( wert[x]==2.0){   
  lcd.setCursor(pos[x],3);lcd.print((char)1);      
  lcd.setCursor(pos[x],2);lcd.print((char)1);       
  lcd.setCursor(pos[x],1);lcd.print(" ");           
  lcd.setCursor(pos[x]-1,3);lcd.print(" ");          
  lcd.setCursor(pos[x]-1,2);lcd.print(" ");           
  lcd.setCursor(pos[x]-1,1);lcd.print(" ");
  lcd.setCursor(pos[x]+1,3);lcd.print(" ");          
  lcd.setCursor(pos[x]+1,2);lcd.print(" ");           
  lcd.setCursor(pos[x]+1,1);lcd.print(" ");
  }

if( wert[x]==1.0){   
  lcd.setCursor(pos[x],3);lcd.print((char)1);      
  lcd.setCursor(pos[x],2);lcd.print(" ");           
  lcd.setCursor(pos[x],1);lcd.print(" ");           
  lcd.setCursor(pos[x]-1,3);lcd.print(" ");          
  lcd.setCursor(pos[x]-1,2);lcd.print(" ");           
  lcd.setCursor(pos[x]-1,1);lcd.print(" ");
  lcd.setCursor(pos[x]+1,3);lcd.print(" ");          
  lcd.setCursor(pos[x]+1,2);lcd.print(" ");           
  lcd.setCursor(pos[x]+1,1);lcd.print(" ");
  }
  
if( wert[x]==0.0){   
  lcd.setCursor(pos[x],3);lcd.print(" ");          
  lcd.setCursor(pos[x],2);lcd.print(" ");           
  lcd.setCursor(pos[x],1);lcd.print(" ");           
  lcd.setCursor(pos[x]-1,3);lcd.print(" ");          
  lcd.setCursor(pos[x]-1,2);lcd.print(" ");           
  lcd.setCursor(pos[x]-1,1);lcd.print(" ");
  lcd.setCursor(pos[x]+1,3);lcd.print(" ");          
  lcd.setCursor(pos[x]+1,2);lcd.print(" ");           
  lcd.setCursor(pos[x]+1,1);lcd.print(" ");
  }
 // lcd.setCursor(12,0); lcd.print("    ");
}



}
//*****************************************************************************************//

//**************************************************************************************************************************************
