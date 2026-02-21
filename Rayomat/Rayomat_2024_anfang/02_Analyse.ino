/*Auflistung Unterfunktionen, die für Analyse einens Dongels benötigt werden
 * 
 * Tag_analyse_MFRC522()     // per MFRC522
 * Tag_analyse_PN532()     // per PN532
 */

int Tag_analyse_MFRC522(int target,bool ausfuehrlich){

  unsigned long raywert=0;
  unsigned int key_state=0;
  int key=0;

  if(ausfuehrlich==0){  
    Serial.println("Analyse gestartet");
  }
  
  if(ausfuehrlich==1){  
    Serial.println("Ausführliche Analyse gestartet");
  }

  //Tag_analyse_MFRC522 steps 1 *********************************************************************//
  if(error==0){
    newkey_MFRC522();

//Tag_analyse_MFRC522 steps 2 *********************************************************************//       
    if(key==0){ 

      for(int x=0;x<=15;x++){
    
        key__searchA(x);
        key=key+ergebnis;
        feedback=0;
        ergebnis=0;
        delay(10);
    
        key__searchB(x);
        key=key+ergebnis;
        feedback=0;
        ergebnis=0;
        delay(10); 
      }
  
      if(key==32){ 
        key_state=0;
      } else {
        key_state=1;
        error=1;
      }
    }

//Tag_analyse_MFRC522 steps 3 *********************************************************************//
    if(key_state==0){

      Check_rfid_tag_mfrc522(target,ausfuehrlich); //Tagwerte lesen und zwischenspeichern
  
      if(error==0&&target==1||error==0&&target==10){   //werte interpretieren und Dongelalter bestimmen  ausgabe aber nur, wenn die Spielerdaten oder der gesamte dongel abgefragt werden
        
        if(Con_Start_read==0&&Con_Start_read2019==0){ 
          msg1="RFID ist leer      ";
          msg2="Ray:";
          raywert=0;  
        }
        
        if(Con_Start_read==0&&Ray_value_extern_read!=0){ 
          msg1="RFID ist vielleicht für Plot  ";
          msg2="Ray:";
          raywert=Ray_value_extern_read/1000;  
        }
        
        if(Con_Start_read==0&&Con_Start_read2019!=0){
          msg1="RFID ist von 2019";
          msg2="Ray:";
          raywert=Old_Ray_value_intern_read2019/1000;
        } 
        
        if(Con_Start_read!=0&&Ray_value_extern_read!=0){ 
          msg1="Neues System     " ;
          msg2="Ray:";
          raywert=Ray_value_extern_read/1000;
        }
  
        if(raywert==0){msg3="kein Ray";}
        if(raywert>0&&raywert<=50){msg3="light Green";}  
        if(raywert>50&&raywert<=100){msg3="Green";}  
        if(raywert>100&&raywert<=150){msg3="dark Green";}  
        if(raywert>150&&raywert<=200){msg3="light Yellow";}
        if(raywert>200&&raywert<=250){msg3="Yellow";}
        if(raywert>250&&raywert<=300){msg3="dark Yellow";}
        if(raywert>300&&raywert<=350){msg3="light Red";}
        if(raywert>350&&raywert<=400){msg3="Red";}
        if(raywert>400){msg3="dark Red";}
        msg4="";
      }  
    }
  }

//Tag_analyse_MFRC522 steps 4 *********************************************************************//
  if(error!=0){ // wenn Check_rfid_tag einen Fehler auweist direkt weiter zum Ende
    key_state=1;
  }

  if(key_state==1){ //wenn key_state bis hier hin immer noch nicht klar, dann sind die Keys unklar und wir gehen in Fehler 
// key_state=0;
    msg1="RFID enthaelt";
    msg2="unbekannte KEYs ";
    msg3="";
    msg4="Analyse abgebrochen";
    buzzer_play( 5,100);
  }
  return;
}
//*****************************************************************************************//

int Tag_analyse_PN532(int target,bool ausfuehrlich){

  unsigned long raywert=0;
  unsigned int key_state=0;
  int key=0;

  if(ausfuehrlich==0){  
    Serial.println("Analyse gestartet");
  }
  
  if(ausfuehrlich==1){  
    Serial.println("Ausführliche Analyse gestartet");
  }

  //Tag_analyse_PN532 steps 1 *********************************************************************//
  if(error==0){
    newkey_PN532();

//Tag_analyse_PN532 steps 2 *********************************************************************//       
//Key-search funktioniert mit pn532 noch nicht, wird hier übersprungen
 /*   if(key==0){ 

      for(int x=0;x<=15;x++){
    
        key__searchA(x);
        key=key+ergebnis;
        feedback=0;
        ergebnis=0;
        delay(10);
    
        key__searchB(x);
        key=key+ergebnis;
        feedback=0;
        ergebnis=0;
        delay(10); 
      }
  
      if(key==32){ 
        key_state=0;
      } else {
        key_state=1;
        error=1;
      }
    }*/

//Tag_analyse_PN532 steps 3 *********************************************************************//
    if(key_state==0){

      Check_rfid_tag_PN532(target,ausfuehrlich); //Tagwerte lesen und zwischenspeichern
  
      if(error==0&&target==1||error==0&&target==10){   //werte interpretieren und Dongelalter bestimmen  ausgabe aber nur, wenn die Spielerdaten oder der gesamte dongel abgefragt werden
        
        if(Con_Start_read==0&&Con_Start_read2019==0){ 
          msg1="RFID ist leer      ";
          msg2="Ray:";
          raywert=0;  
        }
        
        if(Con_Start_read==0&&Ray_value_extern_read!=0){ 
          msg1="RFID ist vielleicht für Plot  ";
          msg2="Ray:";
          raywert=Ray_value_extern_read/1000;  
        }
        
        if(Con_Start_read==0&&Con_Start_read2019!=0){
          msg1="RFID ist von 2019";
          msg2="Ray:";
          raywert=Old_Ray_value_intern_read2019/1000;
        } 
        
        if(Con_Start_read!=0&&Ray_value_extern_read!=0){ 
          msg1="Neues System     " ;
          msg2="Ray:";
          raywert=Ray_value_extern_read/1000;
        }
  
        if(raywert==0){msg3="kein Ray";}
        if(raywert>0&&raywert<=50){msg3="light Green";}  
        if(raywert>50&&raywert<=100){msg3="Green";}  
        if(raywert>100&&raywert<=150){msg3="dark Green";}  
        if(raywert>150&&raywert<=200){msg3="light Yellow";}
        if(raywert>200&&raywert<=250){msg3="Yellow";}
        if(raywert>250&&raywert<=300){msg3="dark Yellow";}
        if(raywert>300&&raywert<=350){msg3="light Red";}
        if(raywert>350&&raywert<=400){msg3="Red";}
        if(raywert>400){msg3="dark Red";}
        msg4="";
      }  
    }
  }

//Tag_analyse_PN532 steps 4 *********************************************************************//
  if(error!=0){ // wenn Check_rfid_tag einen Fehler auweist direkt weiter zum Ende
    key_state=1;
  }

  if(key_state==1){ //wenn key_state bis hier hin immer noch nicht klar, dann sind die Keys unklar und wir gehen in Fehler 
// key_state=0;
    msg1="RFID enthaelt";
    msg2="unbekannte KEYs ";
    msg3="";
    msg4="Analyse abgebrochen";
    buzzer_play( 5,100);
  }
  return;
}
//*****************************************************************************************//
