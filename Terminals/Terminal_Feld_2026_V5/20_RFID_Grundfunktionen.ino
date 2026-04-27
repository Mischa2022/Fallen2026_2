/*Auflistung Grundsaetzlicher RFID Funktionen
 * 
 * rfid_reading      //allgemeine Lesefunktion
 * writing           //allgemeine Schreibfunktion
 * key__searchA      //Suchfunktion Key A
 * key__searchB      //Suchfunktion Key B
 * try_keyB          //Unterfunktion zum Testen Key B
 * try_keyA          //Unterfunktion zum Testen Key A
 * RFID_Set_Keys_int //aendern der Keys A&B
 * newkey          //Hilfsfunktion zum Bestimmen des aktuellen KeyB nach Checkin
 */


long rfid_reading(byte keys[],byte block) {

/* zum lesen wird in meinen Programmen nur der Key A benoetigt.
 *  Diese Funktion zerlegt den buffer in variableA und B und 
 *  kann ueber ergebnisA & B abgegriffen werden. 
 *  Fehlerhafte Authentizierung oder andere Fehler, werden als 1 zurueckgegeben
 *  und dienen als Fehlercounter.
 */

  MFRC522::MIFARE_Key key; 
  for (byte i = 0; i < 6; i++) key.keyByte[i] = keys[i];// 0xFF;

  byte trailorBlock =0;
  byte len=18;
  byte buffer1[18];
  int WERTA0,WERTA1,WERTA2,WERTA3,WERTA4;
  int WERTB0,WERTB1,WERTB2,WERTB3,WERTB4;
  long varA,varA2,varA3,varA4,varA5;
  long varB,varB2,varB3,varB4,varB5;

  ergebnisA,ergebnisB=0;

  if (block==1||block==2){trailorBlock=3;}
  if (block==4||block==5||block==6){trailorBlock=7;}
  if (block==8||block==9||block==10){trailorBlock=11;}
  if (block==12||block==13||block==14){trailorBlock=15;}
  if (block==16||block==17||block==18){trailorBlock=19;}
  if (block==20||block==21||block==22){trailorBlock=23;}
  if (block==24||block==25||block==26){trailorBlock=27;}
  if (block==28||block==29||block==30){trailorBlock=31;}
  if (block==32||block==33||block==34){trailorBlock=35;}
  if (block==36||block==37||block==38){trailorBlock=39;}
  if (block==40||block==41||block==42){trailorBlock=43;}
  if (block==44||block==45||block==46){trailorBlock=47;}
  if (block==48||block==49||block==50){trailorBlock=51;}
  if (block==52||block==53||block==54){trailorBlock=55;}
  if (block==56||block==57||block==58){trailorBlock=59;}
  if (block==60||block==61||block==62){trailorBlock=63;}
 
  MFRC522::StatusCode status;
 
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailorBlock, &key, &(mfrc522.uid)); 
  if (status != MFRC522::STATUS_OK) {
  //  Serial.write("Key A trailorblock "); // Ausgabe ist fuer Test nicht mehr noetig
  //  Serial.print(trailorBlock);
  //  Serial.write(" nicht ok");
    return 1;
  }

  status = mfrc522.MIFARE_Read(block, buffer1, &len);
  if (status != MFRC522::STATUS_OK) {
  //  Serial.write("Lesen Block "); // Ausgabe ist fuer Test nicht mehr noetig
  //  Serial.print(block);
  //  Serial.write(" nicht ok");
    return 1;
  }
   
  WERTA0=buffer1[3],DEC;
  WERTA1=buffer1[4],DEC;
  WERTA2=buffer1[5],DEC;
  WERTA3=buffer1[6],DEC;
  WERTA4=buffer1[7],DEC;

  varA= ((WERTA0 *256));
  varA2=((varA*256)+WERTA1);
  varA3=((varA2*256)+WERTA2);
  varA4=((varA3*256)+WERTA3);
  varA5=((varA4*256)+WERTA4);
  ergebnisA=varA5;

/* //Ausgabe wird durch Check_RFID uebernommen
Serial.write("ErgebnisA: ");
Serial.println(ergebnisA);
*/
  WERTB0=buffer1[11],DEC;
  WERTB1=buffer1[12],DEC;
  WERTB2=buffer1[13],DEC;
  WERTB3=buffer1[14],DEC;
  WERTB4=buffer1[15],DEC;
  
  varB= ((WERTB0 *256));
  varB2=((varB*256)+WERTB1);
  varB3=((varB2*256)+WERTB2);
  varB4=((varB3*256)+WERTB3);
  varB5=((varB4*256)+WERTB4);
  ergebnisB=varB5;



  delay(50);
  return 0;

}

//*****************************************************************************************//

int writing(byte keys[],byte block,unsigned long variableA, unsigned long variableB) {
      
/* zum schreiben wird in meinen Programmen nur der Key B benoetigt.
 *  Diese Funktion zerlegt variableA und B so, 
 *  dass die Werte als HEX in die buffer geschrieben werden. Zu beachten ist die fuehrende "0" als Trenner
 */
   
  byte buffer[16];
  byte status;
  
  long varAA,varAB,varAC,varAD,varAX,varAY,varAZ,varAA1,varAB1,varAC1,varAD1,varAX1,varAY1,varAZ1;
  long varBA,varBB,varBC,varBD,varBX,varBY,varBZ,varBA1,varBB1,varBC1,varBD1,varBX1,varBY1,varBZ1;
  byte trailorBlock =0;
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = keys[i];

  if (block==1||block==2){trailorBlock=3;}
  if (block==4||block==5||block==6){trailorBlock=7;}
  if (block==8||block==9||block==10){trailorBlock=11;}
  if (block==12||block==13||block==14){trailorBlock=15;}
  if (block==16||block==17||block==18){trailorBlock=19;}
  if (block==20||block==21||block==22){trailorBlock=23;}
  if (block==24||block==25||block==26){trailorBlock=27;}
  if (block==28||block==29||block==30){trailorBlock=31;}
  if (block==32||block==33||block==34){trailorBlock=35;}
  if (block==36||block==37||block==38){trailorBlock=39;}
  if (block==40||block==41||block==42){trailorBlock=43;}
  if (block==44||block==45||block==46){trailorBlock=47;}
  if (block==48||block==49||block==50){trailorBlock=51;}
  if (block==52||block==53||block==54){trailorBlock=55;}
  if (block==56||block==57||block==58){trailorBlock=59;}
  if (block==60||block==61||block==62){trailorBlock=63;}
    
  varAD1= variableA%256;
  varAD= varAD1;   
  varAC1=(variableA-varAD1)/256;
  varAC= varAC1%256;
  varAB1= (variableA-varAC)/256/256;
  varAB= varAB1%256; 
  varAA1= (variableA-varAB)/256/256/256;
  varAA= varAA1%256;
  varAZ1= (variableA-varAA)/256/256/256/256;
  varAZ= varAZ1%256;
  varAY1=(variableA-varAZ)/256/256/256/256/256;
  varAY= varAY1%256;
  varAX1=(variableA-varAY)/256/256/256/256/256/256;
  varAX=varAY1%256;
  
  varBD1= variableB%256;
  varBD= varBD1;   
  varBC1=(variableB-varBD1)/256;
  varBC= varBC1%256;
  varBB1= (variableB-varBC)/256/256;
  varBB= varBB1%256; 
  varBA1= (variableB-varBB)/256/256/256;
  varBA= varBA1%256;
  varBZ1= (variableB-varBA)/256/256/256/256;
  varBZ= varBZ1%256;
  varBY1=(variableB-varBZ)/256/256/256/256/256;
  varBY= varBY1%256;
  varBX1=(variableB-varBY)/256/256/256/256/256/256;
  varBX=varBY1%256;
                    
  buffer[0]= 0;
  buffer[1]= (varAX);
  buffer[2]= (varAY);
  buffer[3]= (varAZ);
  buffer[4]= (varAA);
  buffer[5]= (varAB);
  buffer[6]= (varAC);
  buffer[7]= (varAD);
  
  buffer[8]= 0;
  buffer[9]= (varBX);
  buffer[10]= (varBY);
  buffer[11]= (varBZ);
  buffer[12]= (varBA);
  buffer[13]= (varBB);
  buffer[14]= (varBC);
  buffer[15]= (varBD);
                      
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_B, trailorBlock, &key, &(mfrc522.uid)); 
  if (status != MFRC522::STATUS_OK) {

    // Serial.write("Key B trailorblock ");
    // Serial.print(trailorBlock);
    // Serial.write(" nicht ok");
      return 1;
  
  }
               
  status = mfrc522.MIFARE_Write(block, buffer, 16);
  if (status != MFRC522::STATUS_OK) {   

    // Serial.write("Schreiben Block ");
    // Serial.print(block);
    // Serial.write(" nicht ok");
    return 1;
  
  } 
  else {
 //   Serial.write("Schreiben Block ");
 //   Serial.print(block);
 //   Serial.write(" ok");
 //   delay(50);
    return 0;
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

int key__searchB(byte block1){
  int test2;

    MFRC522::MIFARE_Key key;
    for (byte k = 0; k < NR_KNOWN_KEYS; k++) {

        for (byte i = 0; i < MFRC522::MF_KEY_SIZE; i++) {
            key.keyByte[i] = knownKeys[k][i];
            test2=k;
        }

        if (try_keyB(&key,block1,test2)) {
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

boolean try_keyB(MFRC522::MIFARE_Key *key,byte block,int counter1)
{   int trailor = block*4+3;
    boolean result = false;
    feedback=0;
    byte buffer[18];
    
    MFRC522::StatusCode status;
    
    status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_B, trailor, key, &(mfrc522.uid));
    if (status != MFRC522::STATUS_OK) {
        feedback=0;
        return false;
    }

    byte byteCount = sizeof(buffer);
    status = mfrc522.MIFARE_Read(trailor, buffer, &byteCount);
    if (status != MFRC522::STATUS_OK) {
      feedback=0;
    }
    else {
       
       
     /*   Serial.write("Block:");
        Serial.print(block);
        Serial.write(" | KeyB:");
        Serial.print(counter1);
        
        Serial.write(" = ");
        dump_byte_array((*key).keyByte, MFRC522::MF_KEY_SIZE);
        Serial.println("");*/
        key_used=counter1;
        feedback=1; result = true;
    }
    return result;
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

void newkey(){

  unsigned long id_value=0;
  long id_check=99000000;
  long new_key_value=0;
  long varAA1,varAB1,varAC1,varAD1,varAX1,varAY1,varAZ1,varAA11,varAB11,varAC11,varAD11,varAX11,varAY11,varAZ11;
  for (byte j = 0; j < mfrc522.uid.size; j++) {
    id_value=((id_value+mfrc522.uid.uidByte[j])*10); 
  }

  new_key_value=id_check-id_value;
 // Serial.write("KEY:");
 // Serial.println(    new_key_value);    
  varAD11= new_key_value%256;
  varAD1= varAD11;   
  varAC11=(new_key_value-varAD11)/256;
  varAC1= varAC11%256;
  varAB11= (new_key_value-varAC1)/256/256;
  varAB1= varAB11%256; 
  varAA11= (new_key_value-varAB1)/256/256/256;
  varAA1= varAA11%256;
  varAZ11= (new_key_value-varAA1)/256/256/256/256;
  varAZ1= varAZ11%256;
  varAY11=(new_key_value-varAZ1)/256/256/256/256/256;
  varAY1= varAY11%256;
                  
  knownKeys[last_key][0]= (varAY1);
  knownKeys[last_key][1]= (varAZ1);
  knownKeys[last_key][2]= (varAA1);
  knownKeys[last_key][3]= (varAB1);
  knownKeys[last_key][4]= (varAC1);
  knownKeys[last_key][5]= (varAD1);
                  
}


//*****************************************************************************************//
