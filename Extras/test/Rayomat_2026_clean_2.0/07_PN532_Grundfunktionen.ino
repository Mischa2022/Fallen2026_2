
/*Auflistung Grundsätzlicher RFID Funktionen per PN532
 * 
 * reading_PN532      //allgemeine Lesefunktion
 * writing_PN532      //allgemeine Schreibfunktion
 * newkey_PN532       //Hilfsfunktion zum Bestimmen des aktuellen KeyB nach Checkin
*/



long reading_PN532(uint8_t Key[],int block){
  
  uint8_t success2;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 }; 
  uint8_t uidLength=4;                      

  
  int trailorBlock;
  int WERTA0,WERTA1,WERTA2,WERTA3,WERTA4;
  int WERTB0,WERTB1,WERTB2,WERTB3,WERTB4;
  
  long varA,varA2,varA3,varA4,varA5;
  long varB,varB2,varB3,varB4,varB5;
  
  ergebnisA2,ergebnisB2=0; //Reset der Ablage

//bestimmung des Trailorblocks
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

  
    success2 = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

      success2 = nfc.mifareclassic_AuthenticateBlock(uid, uidLength,trailorBlock, 0, Key);
    
      if (success2)
      {
        uint8_t data[16];

        success2 = nfc.mifareclassic_ReadDataBlock(block, data);
    
        if (success2)
        {
          
              WERTA0=data[3],DEC;
              WERTA1=data[4],DEC;
              WERTA2=data[5],DEC;
              WERTA3=data[6],DEC;
              WERTA4=data[7],DEC;
            
              varA= ((WERTA0 *256));
              varA2=((varA*256)+WERTA1);
              varA3=((varA2*256)+WERTA2);
              varA4=((varA3*256)+WERTA3);
              varA5=((varA4*256)+WERTA4);
              
              ergebnisA2=varA5;
                   
   //          Serial.print(F("ErgebnisA2: "));
   //          Serial.println(ergebnisA2);
            
              WERTB0=data[11],DEC;
              WERTB1=data[12],DEC;
              WERTB2=data[13],DEC;
              WERTB3=data[14],DEC;
              WERTB4=data[15],DEC;
            
              varB= ((WERTB0 *256));
              varB2=((varB*256)+WERTB1);
              varB3=((varB2*256)+WERTB2);
              varB4=((varB3*256)+WERTB3);
              varB5=((varB4*256)+WERTB4);
              ergebnisB2=varB5;
                   
     //         Serial.print(F("ErgebnisB2: "));
     //         Serial.println(ergebnisB2);
     //         Serial.print(F("Block "));Serial.print(block);Serial.println(F(" fertig gelesen")); //debug
              return 0;
        }
        else
        {
          Serial.println(F("Block nicht gelesen")); //debug
          reader=false;
          return 1;
        }
      }
      else
      {
        Serial.println(F("Key vielleicht falsch?")); //debug
        reader=false;
        return 1;
      }
success2 =!success2;
  }
//*****************************************************************************************//
int writing_PN532(uint8_t KeyB[],byte block,unsigned long variableA, unsigned long variableB) {
      
/* zum schreiben wird in meinen Programmen nur der Key B benötigt.
 *  Diese Funktion zerlegt variableA und B so, 
 *  dass die Werte als HEX in die data geschrieben werden. Zu beachten ist die führende "0" als Trenner
 */
   
  uint8_t success3;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 }; 
  uint8_t uidLength=4;    
  
  long varAA,varAB,varAC,varAD,varAX,varAY,varAZ,varAA1,varAB1,varAC1,varAD1,varAX1,varAY1,varAZ1;
  long varBA,varBB,varBC,varBD,varBX,varBY,varBZ,varBA1,varBB1,varBC1,varBD1,varBX1,varBY1,varBZ1;
  byte trailorBlock =0;
  uint8_t data[16];

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
                    
  data[0]= 0;
  data[1]= (varAX);
  data[2]= (varAY);
  data[3]= (varAZ);
  data[4]= (varAA);
  data[5]= (varAB);
  data[6]= (varAC);
  data[7]= (varAD);
  
  data[8]= 0;
  data[9]= (varBX);
  data[10]= (varBY);
  data[11]= (varBZ);
  data[12]= (varBA);
  data[13]= (varBB);
  data[14]= (varBC);
  data[15]= (varBD);

    success3 = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

      success3 = nfc.mifareclassic_AuthenticateBlock(uid, uidLength, trailorBlock, 1, KeyB);
   if (success3){

        success3 = nfc.mifareclassic_WriteDataBlock(block, data);
    
        if (success3){

  //  Serial.print(F("Schreiben Block "));
  //  Serial.print(block);
  //  Serial.println(F(" ok"));
    delay(50);
    return 0;
  }else{  
    Serial.print(F("Schreiben Block "));
    Serial.print(block);
    Serial.println(F("nicht ok"));
  return 1;}
 }else{
  Serial.print(F("Authentizität Block "));
    Serial.print(block);
    Serial.println(F("nicht ok"));
  return 1;
 }
 success3 =!success3;
 }
//*****************************************************************************************//
//*****************************************************************************************//
void newkey_PN532(){

  unsigned long id_value=0;
  long id_check=99000000;
  unsigned long new_key_value=0;
  long varAA1,varAB1,varAC1,varAD1,varAX1,varAY1,varAZ1,varAA11,varAB11,varAC11,varAD11,varAX11,varAY11,varAZ11;
  uint8_t success;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 }; 
  uint8_t uidLength=4;       
  
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

  if (success) {

    for (uint8_t i=0; i < uidLength; i++) 
    {

      id_value=((id_value+uid[i])*10); 

    }

  new_key_value=id_check-id_value;
//  Serial.print(F("KEY:"));
//  Serial.println(new_key_value);    
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
}
