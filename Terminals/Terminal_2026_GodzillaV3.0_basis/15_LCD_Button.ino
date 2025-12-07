/*Auflistung Unterfunktionen, die fuer LCD und Buttons benoetigt werden
 * 
 * menue_print_lcd            //  2025 LCD Menuefuehrung
 * poti_read                  //  2025 eingabe ueber Poti
 * rotary_read                //  2025 eingabe ueber rotationsgeber
 * lcd_print_medi_log         //  2025 ausgabe medilog ueber lcd durch spezialdongel
 */

void menue_print_lcd(int modus,int positio){
  char* marker=">";
  int pos=0;
  int pos2=0;
   
char* buchungen[] {"Checkin            ","Analyse            ","Reset              ","                    ",
                   "     Blockiert      ","  Mit PC verbunden  ","  Checkinterminal   ","  Buchungsterminal  ","  Warten auf Dongel "
                   };


   if (modus==0){ //Godzilla
    lcd.setCursor(0,0);
    lcd.print(buchungen[5]);
    lcd.setCursor(0, 1);
    lcd.print(buchungen[3]);
    lcd.setCursor(0, 2);
    lcd.print(buchungen[3]);
    lcd.setCursor(0, 3);
    lcd.print(buchungen[3]);
    //locked=false;
    }    
    
   else if (modus==1){ //Checkin
     pos=positio;
      if(pos<=0){        pos=0;        }
      if(pos>=2 ){        pos=2;        }
      
      lcd.setCursor(0,1);
      lcd.print(" ");
      lcd.setCursor(0,2);
      lcd.print(" ");
      lcd.setCursor(0,3);
      lcd.print(" ");
      lcd.setCursor(0,pos+1);
      lcd.print(marker);
    
    lcd.setCursor(0,0);
    lcd.print(buchungen[6]);
    lcd.setCursor(1, 1);
    lcd.print(buchungen[0]);
    lcd.setCursor(1, 2);
    lcd.print(buchungen[1]);
    lcd.setCursor(1, 3);
    lcd.print(buchungen[2]);
   // locked=false;

      if(ebene==true){
      lcd.setCursor(0, 0); 
      lcd.print(buchungen[8]);
      if(pos==0){ ziel_char='h';}
      if(pos==1){ ziel_char='a';ziel_long=1;}
      if(pos==2){ ziel_char='v';}
      }
       else{
      lcd.setCursor(0,0);
      lcd.print(buchungen[6]);
      ziel_char=' ';  
      ziel_long=0;
      }
   
    }  
    
   else if (modus==2){  //Buchung
    lcd.setCursor(0,0);
    lcd.print(buchungen[7]);
    
      if(locked==true){
        lcd.setCursor(0, 1);
        lcd.print(buchungen[4]);  
        lcd.setCursor(0, 2);
        lcd.print(buchungen[3]);
        lcd.setCursor(0, 3);
        lcd.print(buchungen[3]);
        
          Anzeige_update =false;
          Anzeige_Nanoclean =false;
          Anzeige_Dekon =false;
          Anzeige_Lifecleaner =false;
          Anzeige_Blutwaesche =false;
          Anzeige_Cleanray =false;
          Anzeige_drawback =false;
          ebene=false;
      } 

      if(locked==false){
        pos2=positio;
  
      if(pos2<0)      {        pos2=0;               }
      if(pos2>maxebene ){        pos2=maxebene;        }
      
      lcd.setCursor(0, 1);
      lcd.print(buchungen[3]);
      lcd.setCursor(0,2);
      lcd.print(marker);
      lcd.setCursor(1, 2);
      
      if(pos2==0&&Anzeige_update == true){
        lcd.print(Medi[pos2]);
           if(ebene==true){
              lcd.setCursor(0, 3); 
              lcd.print(buchungen[8]);
              ziel_char='b';
              ziel_long=pos2+1;
            }
            else{
                lcd.setCursor(0, 3); 
                lcd.print(buchungen[3]);
                ziel_char=' ';  
                ziel_long=0;
            }
        }
        
      if(pos2==1&&Anzeige_Nanoclean == true){
        lcd.print(Medi[pos2]);
           if(ebene==true){
              lcd.setCursor(0, 3); 
              lcd.print(buchungen[8]);
              ziel_char='b';
              ziel_long=pos2+1;
            }
             else{
                lcd.setCursor(0, 3); 
                lcd.print(buchungen[3]);
                ziel_char=' ';  
                ziel_long=0;
            }
        }
        
      if(pos2==2&&Anzeige_Dekon == true){
        lcd.print(Medi[pos2]);
           if(ebene==true){
              lcd.setCursor(0, 3); 
              lcd.print(buchungen[8]);
              ziel_char='b';
              ziel_long=pos2+1;
            }
              else{
                lcd.setCursor(0, 3); 
                lcd.print(buchungen[3]);
                ziel_char=' ';  
                ziel_long=0;
            }
        }
        
      if(pos2==3&&Anzeige_Lifecleaner == true){
        lcd.print(Medi[pos2]);
           if(ebene==true){
              lcd.setCursor(0, 3); 
              lcd.print(buchungen[8]);
              ziel_char='b';
              ziel_long=pos2+1;
            }
              else{
                lcd.setCursor(0, 3); 
                lcd.print(buchungen[3]);
                ziel_char=' ';  
                ziel_long=0;
            }
        }
        
      if(pos2==4&&Anzeige_Blutwaesche == true){
        lcd.print(Medi[pos2]);
           if(ebene==true){
              lcd.setCursor(0, 3); 
              lcd.print(buchungen[8]);
              ziel_char='b';
              ziel_long=pos2+1;
            }
              else{
                lcd.setCursor(0, 3); 
                lcd.print(buchungen[3]);
                ziel_char=' ';  
                ziel_long=0;
            }
        }
        
      if(pos2==5&&Anzeige_Cleanray == true){
        lcd.print(Medi[pos2]);
           if(ebene==true){
              lcd.setCursor(0, 3); 
              lcd.print(buchungen[8]);
              ziel_char='b';
              ziel_long=pos2+1;
            }
              else{
                lcd.setCursor(0, 3); 
                lcd.print(buchungen[3]);
                ziel_char=' ';  
                ziel_long=0;
            }
        }
        
      if(pos2==6&&Anzeige_drawback == true){
        lcd.print(Medi[pos2]);
           if(ebene==true){
              lcd.setCursor(0, 3); 
              lcd.print(buchungen[8]);
              ziel_char='b';
              ziel_long=pos2+1;
            }
              else{
                lcd.setCursor(0, 3); 
                lcd.print(buchungen[3]);
                ziel_char=' ';  
                ziel_long=0;
            }
        }
     /* lcd.print(Medi[pos2]);

      if(ebene==true){
      lcd.setCursor(0, 3); 
      lcd.print(buchungen[8]);
      ziel_char='b';
      ziel_long=pos2+1;
    */
      }
      else{
       lcd.setCursor(0, 3); 
      lcd.print(buchungen[3]);
      ziel_char=' ';  
      ziel_long=0;
      }
     }
   }

//*****************************************************************************************//

int poti_read(int mini,int maxi){
  //int poti_anzeige;
  int value1 = button.read();

  if(ebene!=true){
  int potiwert=analogRead(POTI_PIN);
  //Serial.println(potiwert);
  poti_anzeige=map(potiwert,0,1000,0,maxi);
    menue_print_lcd(modus,poti_anzeige);
  }
  
  if ( button.fallingEdge() ) {
    buzzer_play(1,100);
    ebene=!ebene;
    menue_print_lcd(modus,poti_anzeige);
   // Serial.print("Ebene:");Serial.println(ebene);
   }
   
  //menue_print_lcd(modus,poti_anzeige);
  
}

//*****************************************************************************************//

int rotary_read(int mini,int maxi){
    if (result == DIR_CW&&ebene!=true) {
     
      if(counterx<=mini){counterx=mini;}
      else{    counterx--; }
      
      menue_print_lcd(modus,counterx);
  } 
  if (result == DIR_CCW&&ebene!=true) {

    if(counterx>=maxi){counterx=maxi;}
      else{    counterx++; }
     
      menue_print_lcd(modus,counterx);
  }
    if (rotary.buttonPressedReleased(20)) {
      ebene=!ebene;
   menue_print_lcd(modus,counterx);
  }
}

//*****************************************************************************************//

int lcd_print_medi_log(){
  check_medi_log();

Menge_Dekon     = Menge_Dekon-1000;    
Menge_Nanoclean = Menge_Nanoclean-2000;
Menge_Life      = Menge_Life-3000;
Menge_Clean     = Menge_Clean-4000;
Menge_Blood     = Menge_Blood-5000;
Menge_Draw      = Menge_Draw-6000;

lcd.clear();
lcd.setCursor(0,0);
lcd.print("Deko|Nano|Life"); 

lcd.setCursor(0,1);
if(Menge_Dekon<1000){lcd.print(" ");}
if(Menge_Dekon<100){lcd.print(" ");}
if(Menge_Dekon<10){lcd.print(" ");}
//if(Menge_Dekon<1){lcd.print("0");}
lcd.print(Menge_Dekon);
lcd.print("|");
if(Menge_Nanoclean<1000){lcd.print(" ");}
if(Menge_Nanoclean<100){lcd.print(" ");}
if(Menge_Nanoclean<10){lcd.print(" ");}
//if(Menge_Nanoclean<1){lcd.print("0");}
lcd.print(Menge_Nanoclean);
lcd.print("|");
if(Menge_Life<1000){lcd.print(" ");}
if(Menge_Life<100){lcd.print(" ");}
if(Menge_Life<10){lcd.print(" ");}
//if(Menge_Life<1){lcd.print("0");}
lcd.print(Menge_Life);

lcd.setCursor(0,2);
lcd.print("Clea|Bloo|Draw");

lcd.setCursor(0,3);
if(Menge_Clean<1000){lcd.print(" ");}
if(Menge_Clean<100){lcd.print(" ");}
if(Menge_Clean<10){lcd.print(" ");}
//if(Menge_Clean<1){lcd.print("0");}
lcd.print(Menge_Clean );
lcd.print("|");
if(Menge_Blood<1000){lcd.print(" ");}
if(Menge_Blood<100){lcd.print(" ");}
if(Menge_Blood<10){lcd.print(" ");}
//if(Menge_Blood<1){lcd.print("0");}
lcd.print(Menge_Blood);
lcd.print("|");
if(Menge_Draw<1000){lcd.print(" ");}
if(Menge_Draw<100){lcd.print(" ");}
if(Menge_Draw<10){lcd.print(" ");}
//if(Menge_Draw<1){lcd.print("0");}
lcd.print(Menge_Draw );

if(port==3){
  Serial3.println("Deko|Nano|Life"); 
  if(Menge_Dekon<1000){Serial3.print(" ");}
  if(Menge_Dekon<100){Serial3.print(" ");}
  if(Menge_Dekon<10){Serial3.print(" ");}
  Serial3.print(Menge_Dekon);
  Serial3.print("|");
  if(Menge_Nanoclean<1000){Serial3.print(" ");}
  if(Menge_Nanoclean<100){Serial3.print(" ");}
  if(Menge_Nanoclean<10){Serial3.print(" ");}
  Serial3.print(Menge_Nanoclean);
  Serial3.print("|");
  if(Menge_Life<1000){Serial3.print(" ");}
  if(Menge_Life<100){Serial3.print(" ");}
  if(Menge_Life<10){Serial3.print(" ");}
  Serial3.println(Menge_Life);
  Serial3.println("Clea|Bloo|Draw");
  if(Menge_Clean<1000){Serial3.print(" ");}
  if(Menge_Clean<100){Serial3.print(" ");}
  if(Menge_Clean<10){Serial3.print(" ");}
  Serial3.print(Menge_Clean);
  Serial3.print("|");
  if(Menge_Blood<1000){Serial3.print(" ");}
  if(Menge_Blood<100){Serial3.print(" ");}
  if(Menge_Blood<10){Serial3.print(" ");}
  Serial3.print(Menge_Blood);
  Serial3.print("|");
  if(Menge_Draw<1000){Serial3.print(" ");}
  if(Menge_Draw<100){Serial3.print(" ");}
  if(Menge_Draw<10){Serial3.print(" ");}
  Serial3.println(Menge_Draw);
}
delay(5000);
}
