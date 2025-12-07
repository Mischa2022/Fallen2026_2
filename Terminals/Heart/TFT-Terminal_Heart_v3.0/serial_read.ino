void incoming_reading(){

    String myString="";
    char char_read[200];
    int posx= 120;
    
    
  myGLCD.setFont(SmallFont);


 if(pos_counter>=max_read){
      
      //überschreiben alte Ausgabe
      posy=58;
      pos_counter=0;

      
    }

if(verbindung==false){

  myGLCD.setBackColor(VGA_LIME);
  myGLCD.setColor(VGA_BLACK);

}
if(verbindung==true){
  
//( 459,33,20,22,VGA_SILVER,wert_verbindung,"");
  myGLCD.setBackColor(VGA_BLACK);
  myGLCD.setColor(VGA_LIME);

}
  //Sperrbildschirm deaktivieren



    //esp-Antworten oder antworten die über ihn reinkommen auf tft anzeigen
    while (Serial3.available() > 0) {
     last_millis= current_millis;
      myString=Serial3.readStringUntil('\n'); // greif neuen string und leg ihn ab


     if( verbindung==false){ 
      myString.toCharArray(char_read,200); // wandle string in char array
      if(char_read[0]=='z'){verbindung=true;
       serial_monitor();
        draw_ebene(funktion);

        }
    }

          myGLCD.print(myString, posx, posy);
          posy=posy+10;
          
          pos_counter=pos_counter+1;
          //Serial.print("Counter:");Serial.println(pos_counter);
    }
    //antworten vom worker-arduino anzeigen auf tft
     while (Serial2.available() > 0) {
     
        last_millis= current_millis;
      myString=Serial2.readStringUntil('\n'); // greif neuen string und leg ihn ab
      //Serial.print("Test Read Worker 1: "); Serial.println(myString);
      
myString.toCharArray(char_read,200); // wandle string in char array




     
      if(char_read[0]=='p'){ //rechtefreigabe manuell
        on=!on;

      if(char_read[1]=='1'){ Nano2 =true;}else{Nano2 =false;}
      if(char_read[2]=='1'){ Blood2 =true;}else{Blood2 =false;}
      if(char_read[3]=='1'){ Clean2 =true;}else{Clean2 =false;}
      if(char_read[4]=='1'){ Life2 =true;}else{Life2 =false;}
      if(char_read[5]=='1'){ Dekon2 =true;}else{Dekon2 =false;}

      if(Nano2==true||Blood2==true||Clean2==true||Life2==true||Dekon2==true){
        Update2=true;Draw2=true;
      }
        
        if(on==true){
        }
        else{start_malen=true;
          }
    }       
        
  if(char_read[0]=='*'){      //konfigimport vom worker
          myString.remove(0,1);
    konfigwerte[stern]=myString;
    if(stern<25){
  //  Serial.print(stern);  Serial.print(" : ");  Serial.println(konfigwerte[stern]);
    }
      memset( char_read, 0, strlen( char_read));
      
      stern=stern+1;
      //if(stern==25){stern=0;}
       myString="";

}


 
if(char_read[0]=='y'){  //modus auswahl
  if(char_read[1]=='0'){  //godzilla
        funktion=0;
        on=true;
        Nano2 =true;
        Blood2=true;
        Clean2=true;
        Life2 =true;
        Dekon2 =true;
        Draw2=true;
        Update2=true;
        memset( char_read, 0, strlen( char_read));
        myString="";
         myGLCD.clrScr();
        draw_ebene(funktion);
       serial_monitor();
        }

  if(char_read[1]=='1'){  //checkin
        funktion=1;
        on=true;
        memset( char_read, 0, strlen( char_read));
        myString="";
         myGLCD.clrScr();
        draw_ebene(funktion);
       serial_monitor();
        }      

  if(char_read[1]=='2'){  //buchung
        funktion=2;       
        memset( char_read, 0, strlen( char_read));
        myString="";
        on=false;
        
        }
      }

                if(on==true){
          myGLCD.print(myString, posx, posy);
          posy=posy+10;
       
          pos_counter=pos_counter+1;
         // Serial.print("Counter:");Serial.println(pos_counter);
          }
    } 

   
      //umleiten von pc-Serial an worker-arduino
        while (Serial.available() > 0) {
        last_millis= current_millis;
      myString=Serial.readStringUntil('\n'); // greif neuen string und leg ihn ab
              
      //wenn esp antwortet, dass er verbunden ist
 
     if( verbindung==false){ 
      myString.toCharArray(char_read,200); // wandle string in char array
      if(char_read[0]=='z'){verbindung=true;
       serial_monitor();
        draw_ebene(funktion);
        }
      if(char_read[0]=='p'){
        on=!on;
        if(on==true){
        draw_ebene(funktion);
       serial_monitor();
        }
        else{start_malen=true;
        }
       }  
    }
    
      else{ // jede weitere textausgabe dann direkt an worker-arduino
    
          Serial2.print(myString);
          Serial2.write('\n');
          

      }

       
    }

      memset( char_read, 0, strlen( char_read));  
      myString="";
  }  
