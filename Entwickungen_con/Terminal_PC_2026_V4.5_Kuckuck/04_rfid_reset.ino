/*Auflistung Unterfunktionen, die fuer Reset einens Dongels benoetigt werden
 * 
 * rfid_reset     //2025 Helferfunktion um einen Spieler_Dongel auf Werkseinstellung zurueckzusetzen
 */

int rfid_reset(){

  unsigned long raywert=0;
  unsigned long id_value=0;
  unsigned int key_state=1;
  int key=0;
  int steps=0;
  int keyset[32];
  int old_block[]{
    1,2,
    4,5,6,
    8,9,10,
    12,13,14,
    16,17,18,
    20,21,22,
    24,25,26,
    28,29,30,
    32,33,34,
    36,37,38,
    40,41,42,
    44,45,46,
    48,49,50,
    52,53,54,
    56,57,58,
    60,61,62
  };


     myprint("Reset gestartet","","",true,true,false,1,port);
    newkey();

//Reset steps 2 *********************************************************************//       

  if(key==0){ 
  
    for(int x=0;x<=15;x++){
      
      key__searchA(x);
      keyset[x]=key_used;
      key=key+ergebnis;
      feedback=0;
      ergebnis=0;
      delay(10);
      
      key__searchB(x);
      keyset[x+16]=key_used;
      key=key+ergebnis;
      feedback=0;
      ergebnis=0;
      delay(50); 
    }
    
    if(key==32){ 
      key_state=0;
    } else {
      key_state=1;
      error=1;

    }
  }

    
      if(steps==0&&key_state==0){
      //  Serial.write("Start");
        for(int z=0;z<=15;z++){
       /*   Serial.write("Sector");
          Serial.println(z);
          Serial.write("KeyA:");
          Serial.print(keyset[z]);
          Serial.write(" | ");
          Serial.write("KeyB:");
          Serial.println(keyset[z+16]);*/
          RFID_Set_Keys_int(keyset[z],keyset[z+16], knownKeys[0], knownKeys[0], z);
          delay(100);
        }
        steps=1;
      }
     
//reset steps 6 ***************************************************************************//
        
      if(steps==1){  
        for(int r=0;r<=46;r++){
          error=error+writing(knownKeys[0],old_block[r],0,0);

        }
      } 
    
  for(int x=0;x<=31;x++){
      keyset[x]=0;
    }
    if(error!=0){
    msg1="RFID enthaelt";
    msg2="unbekannte KEYs ";
    msg3="";
    msg4="Reset abgebrochen";
  }
  else{
    msg1="Reset ";
    msg2="";
    msg3="abgeschlossen ";
    msg4="";
  }
}

  //*****************************************************************************************//
