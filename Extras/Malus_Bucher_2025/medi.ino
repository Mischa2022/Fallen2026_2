

int Mediread_MFRC522(){

unsigned long A=0;
long medi;
int art=0;


medi=id_reading();

A= rfid_reading(knownKeys[0],10);


     art= ergebnisB- medi; 
         switch (art) {
     case 177:
     Serial.println("Medi: Dekon gefunden"); 
     sorte=3;

     break;   
                                   
     case 255:// original
     Serial.println("Medi: NanoClean gefunden");
     sorte=2;

     break;
                               
     case 367:
     Serial.println("Medi: Blutwäsche gefunden"); 
     sorte=5;

     break;   
                            
     case 583:
     Serial.println("Medi: Cleanray gefunden"); 
     sorte=6;

     break;
                            
     case 722:
     Serial.println("Medi: LifeCleaner gefunden"); 
     sorte=4;
 
     break;
                            
     default:
    // Serial.println("kein Medi"); 
     sorte=0;
     break;
     }

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
