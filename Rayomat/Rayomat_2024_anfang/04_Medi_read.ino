 /*Auflistung Unterfunktionen, die für Medikamentenerkennung benötigt werden
 * 
 * Mediread_PN532     //Helferfunktion interpretiert Werte von Medikamenten-TAGs per PN532 um das richtige Medikament zu buchen
 * id_reading         // Helfer für Mediread_MFRC522  
 * Mediread_MFRC522   //Helferfunktion interpretiert Werte von Medikamenten-TAGs per MFRC522 um das richtige Medikament zu buchen
 */


int Mediread_PN532(){                 
  
  unsigned long medi_id=0;
  uint8_t success=0;
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 }; 
  uint8_t uidLength=4;     
  uint8_t KEYA[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }; // Basis Key A
  int art=0;
  int counter2 =0; // um leseschleifen zu vermeiden       
 
   success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
   reader=false;

  if (success) {

    for (uint8_t i=0; i < uidLength; i++) 
    {

      medi_id=((medi_id+uid[i])*10); 

    if(i==3){

    reader=true;
    }}
  } 
  
if(reader==true&&counter2==0){    
 
  counter2=counter2+reading_PN532(KEYA,10);

  if (counter2==0){

art= ergebnisB2- medi_id; 
              
switch (art) {
     case 177:
     Serial.println("Dekon gefunden"); 
     sorte=3;
     ziel_char='b';
     ziel_long=sorte;
     break;   
                                   
     case 255:// original
     Serial.println("NanoClean gefunden");
     sorte=2;
     ziel_char='b';
     ziel_long=sorte;
     break;
                               
     case 367:
     Serial.println("Blutwäsche gefunden"); 
     sorte=5;
     ziel_char='b';
     ziel_long=sorte;
     break;   
                            
     case 583:
     Serial.println("Cleanray gefunden"); 
     sorte=6;
     ziel_char='b';
     ziel_long=sorte;
     break;
                            
     case 722:
     Serial.println("LifeCleaner gefunden"); 
     sorte=4;
     ziel_char='b';
     ziel_long=sorte;
     break;
                            
     default:
     Serial.println("nichts gefunden"); 
     sorte=0;
     break;
     }

    }
  success=!success;
  }
}

//*****************************************************************************************//


int Mediread_MFRC522(){

unsigned long A=0;
long medi;
int art=0;

if(mfrc522.PICC_IsNewCardPresent()&&mfrc522.PICC_ReadCardSerial()){
medi=id_reading();

A= reading_MFRC522(knownKeys[0],10);


     art= ergebnisB- medi; 
         switch (art) {
     case 177:
     Serial.println("Dekon gefunden"); 
     sorte=3;
     ziel_char='b';
     ziel_long=sorte;
     break;   
                                   
     case 255:// original
     Serial.println("NanoClean gefunden");
     sorte=2;
     ziel_char='b';
     ziel_long=sorte;
     break;
                               
     case 367:
     Serial.println("Blutwäsche gefunden"); 
     sorte=5;
     ziel_char='b';
     ziel_long=sorte;
     break;   
                            
     case 583:
     Serial.println("Cleanray gefunden"); 
     sorte=6;
     ziel_char='b';
     ziel_long=sorte;
     break;
                            
     case 722:
     Serial.println("LifeCleaner gefunden"); 
     sorte=4;
     ziel_char='b';
     ziel_long=sorte;
     break;
                            
     default:
     Serial.println("nichts gefunden"); 
     sorte=0;
     break;
     }
mfrc522.PICC_HaltA();
mfrc522.PCD_StopCrypto1();
}return sorte;

}

//*****************************************************************************************//
long id_reading(){
    long medi_id_value=0;


for (byte i = 0; i < 4; i++)
    {
     medi_id_value=((medi_id_value+mfrc522.uid.uidByte[i])*10); 
     if(i>=3){
      return medi_id_value;
     }
    }
}

//*****************************************************************************************//
