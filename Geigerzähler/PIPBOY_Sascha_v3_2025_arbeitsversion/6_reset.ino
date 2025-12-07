/*Auflistung Unterfunktionen, die für Reset einens Dongels benötigt werden
 * 
 * rfid_reset     //Helferfunktion um einen Spieler_Dongel auf Werkseinstellung zurückzusetzen
 */

int rfid_reset(){
//2x prozess
  unsigned long raywert=0;
  unsigned long id_value=0;
  unsigned int key_state=1;
  int key=0;
  int steps=0;
  int keyset[32];
  int old_block[47]{
    1,2,4,5,6,8,9,10,12,13,
    14,16,17,18,20,21,22,24,25,26,
    28,29,30,32,33,34,36,37,38,40,
    41,42,44,45,46,48,49,50,52,53,
    54,56,57,58,60,61,62
  };


   //  myprint("Reset gestartet","","",true,true,false,1,0);
    newkey();
////prozess(1); 
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
  ////prozess(1);      
//reset steps 6 ***************************************************************************//
        
      if(steps==1){  
        for(int r=0;r<=46;r++){
          Display.clearDisplay();
          writing(knownKeys[0],old_block[r],0,0);
         // Serial.print(r);Serial.println("/46");
          Display.setCursor( 0, 30);
          Display.print(r);Display.print("/46");
          Display.display();
          delay(100);
        }
      } 
    
  for(int x=0;x<=31;x++){
      keyset[x]=0;
    }
    if(error!=0){
    Serial.print("RFID enthaelt");
    Serial.print("unbekannte KEYs ");
    //msg3="";
    Serial.println("Reset abgebrochen");
  }
  else{
    Serial.print("Reset ");
    //msg2="";
    Serial.println("abgeschlossen ");
    //msg4="";

  }
}

  //*****************************************************************************************//
  int key__searchA(byte block1){
  int test;
  
    MFRC522::MIFARE_Key key;
    for (byte k = 0; k < NR_KNOWN_KEYS; k++) {

        for (byte i = 0; i < MFRC522::MF_KEY_SIZE; i++) {
            key.keyByte[i] = knownKeys[k][i];
            test=k;
        }
 
        if (try_keyA(&key,block1,test)) {
          ergebnis=feedback;
            break;  
        }
           
        if ( ! mfrc522.PICC_IsNewCardPresent()){
            break;
            }
        if ( ! mfrc522.PICC_ReadCardSerial()){
            break;
            }
    }
}
//*****************************************************************************************//

boolean try_keyA(MFRC522::MIFARE_Key *key,byte block,int counter2){ 
  int trailor2 = block*4+3;
    boolean result = false;
    feedback=0;
    byte buffer[18];
    
    MFRC522::StatusCode status;
    
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailor2, key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
        
        return false;
    }
    else {
       
   /*  
        Serial.write("Block:");
        Serial.print(block);
        Serial.write(" | KeyA:");
        Serial.print(counter2);
        
        Serial.write(" = ");
        dump_byte_array((*key).keyByte, MFRC522::MF_KEY_SIZE);
        Serial.write(" | ");*/
        key_used=counter2;
        feedback=1; result = true;
    }
    return result;
}

//*****************************************************************************************//

int RFID_Set_Keys_int(int key_selectA,int key_selectB, byte* newA, byte* newB,int sector) {
/*KeyA,KeyB von Sector X werden nach erfolgreichen Authentizieren, 
 * gegen newA &newB ersetzt
 * 
 */
     
  MFRC522::StatusCode status;
  byte trailerBlock = sector * 4 + 3;
  byte buffer[18];
  byte size = sizeof(buffer);
  byte* oldA;
  byte* oldB;
    MFRC522::MIFARE_Key keyA2;
    MFRC522::MIFARE_Key keyB2;
    MFRC522::MIFARE_Key newKeyA2;
    MFRC522::MIFARE_Key newKeyB2;
   oldA= knownKeys[key_selectA];
   oldB= knownKeys[key_selectB];
  

 for (byte i = 0; i < MFRC522::MF_KEY_SIZE; i++) {
    keyA2.keyByte[i] = oldA[i];
    keyB2.keyByte[i] = oldB[i];     //KeyB = A default KeyB = B Livesystem
    newKeyA2.keyByte[i] = newA[i];
    newKeyB2.keyByte[i] = newB[i];  //KeyB = A default KeyB = B Livesystem
  }
    
  status = (MFRC522::StatusCode)mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &keyA2, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    return;
  }

  status = (MFRC522::StatusCode) mfrc522.MIFARE_Read(trailerBlock, buffer, &size);
  if (status != MFRC522::STATUS_OK) {
    return;
  }

  status = (MFRC522::StatusCode)mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_B, trailerBlock, &keyB2, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    return;
  }

  if (newA != nullptr || newB != nullptr) {
    for (byte i = 0; i < MFRC522::MF_KEY_SIZE; i++) {
      if (newA != nullptr) {
        buffer[i] = newA[i];
      }
      if (newB != nullptr) {
        buffer[i+10] = newB[i];
      }
    }
  }

  status = (MFRC522::StatusCode) mfrc522.MIFARE_Write(trailerBlock, buffer, 16);
  if (status != MFRC522::STATUS_OK) {
    return;
    }

  status = (MFRC522::StatusCode)mfrc522.MIFARE_Read(trailerBlock, buffer, &size);
  if (status != MFRC522::STATUS_OK) {
    return;
    }
 //Serial.write("Fertig mit Sector:");
 //Serial.println(sector);
  return true;
}

//*****************************************************************************************//
