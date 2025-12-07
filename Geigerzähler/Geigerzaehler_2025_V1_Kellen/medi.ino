

int Mediread_MFRC522(){

unsigned long A=0;
long medi;
int art=0;

//if(mfrc522.PICC_IsNewCardPresent()&&mfrc522.PICC_ReadCardSerial()){
medi=id_reading();

A= rfid_reading(knownKeys[0],10);


     art= ergebnisB- medi; 
         switch (art) {
     case 177:
     Serial.println("Dekon gefunden"); 
     sorte=3;
   //  ziel_char='b';
   //  ziel_long=sorte;
     break;   
                                   
     case 255:// original
     Serial.println("NanoClean gefunden");
     sorte=2;
  //   ziel_char='b';
  //   ziel_long=sorte;
     break;
                               
     case 367:
     Serial.println("Blutwäsche gefunden"); 
     sorte=5;
   //  ziel_char='b';
   //  ziel_long=sorte;
     break;   
                            
     case 583:
     Serial.println("Cleanray gefunden"); 
     sorte=6;
   //  ziel_char='b';
   //  ziel_long=sorte;
     break;
                            
     case 722:
     Serial.println("LifeCleaner gefunden"); 
     sorte=4;
   //  ziel_char='b';
   //  ziel_long=sorte;
     break;
                            
     default:
     Serial.println("nichts gefunden"); 
     sorte=0;
     break;
     }
//mfrc522.PICC_HaltA();
//mfrc522.PCD_StopCrypto1();
//}
return sorte;

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
