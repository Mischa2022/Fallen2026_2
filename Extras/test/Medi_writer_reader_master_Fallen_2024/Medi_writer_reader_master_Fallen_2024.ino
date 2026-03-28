#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//*****************************************************************************************//
//RFID

    #define SS_PIN 10
    #define RST_PIN 9
    MFRC522 mfrc522(SS_PIN, RST_PIN);



    byte A[]={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
    //byte B[]={0xFF,0xE6,0xFF,0xFF,0xD1,0xFF};   
    byte B[]={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

//*****************************************************************************************//
 //Ein-/ Ausgabe  
   
  // LiquidCrystal_I2C lcd(0x3f,16,2);int LCD_State= 1; //Gelb 2 Reihen
    LiquidCrystal_I2C lcd(0x3f,20,4);int LCD_State= 2; //Gelb 4 Reihen
//   LiquidCrystal_I2C lcd(0x27,16,2);int LCD_State= 1; //Blau 2 Reihen
  // LiquidCrystal_I2C lcd(0x27,20,4);// int LCD_State= 2;//Blau 4 Reihen

    int Poti_read = 0;
    int potPin = A3; 
    int buzzer =A2;
    int buzzertime =0;
    int redPin=7;
    int greenPin=5;
    int bluePin=4;
//**********************************Einstellungen******************************************//

//read

//read unterfunktionen
unsigned long ergebnisA,ergebnisB;
unsigned long reading=0;

//allgemeine Prozessvariablen
unsigned int steps=0;
unsigned int error=0;
unsigned int error2=0;
unsigned int error3=0;
unsigned long medi;
unsigned long secure;
unsigned long art;
unsigned long id;
int kontroll_block=10;
int medi_effekt=0;
char* typ[]{"Nur lesen      ","Nanoclean      ",
            "Dekon          ","Blutwaesche    ",
            "Cleanray       ","Lifecleaner    ",
            "               ","zum schreiben  ",
            "TAG auflegen   ","Wert gelesen:  ",
            "geschrieben    ","schreiben      "};

 int code[]{255,177,367,583,722};
                        
                                                                                                                                                                              
//*****************************************************************************************//
void setup()
{ 
  Serial.begin(9600);
  SPI.begin(); 
  mfrc522.PCD_Init();
  lcd.init();
  lcd.backlight();
  lcd.clear();
  pinMode(buzzer, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(4, OUTPUT);
  digitalWrite(4,LOW);
  digitalWrite(redPin,LOW);
  digitalWrite(greenPin,LOW);
  digitalWrite(bluePin,HIGH);
  randomSeed(analogRead(0));
}

//*****************************************************************************************//
void loop(){
 
  Poti_read = analogRead(potPin);  
  Poti_read = map(Poti_read,0,1010,0,5);
    //Poti_read =5;    

if(steps==0){
ergebnisA,ergebnisB=0;
reading=0;
error=0;
error2=0;
medi_effekt=0;
medi=0;
secure=0;
art=0;
id=0;
digitalWrite(redPin,LOW);
digitalWrite(greenPin,LOW);
digitalWrite(bluePin,HIGH);

      switch(Poti_read){
      case 0: Serial.println(typ[0]);lcd.setCursor(0, 0); lcd.print(typ[0]);lcd.setCursor(0, 2); lcd.print(typ[6]);lcd.setCursor(0, 3); lcd.print(typ[8]);break;
      case 1: Serial.println(typ[1]);lcd.setCursor(0, 0); lcd.print(typ[1]);lcd.setCursor(0, 2); lcd.print(typ[7]);lcd.setCursor(0, 3); lcd.print(typ[8]);break;
      case 2: Serial.println(typ[2]);lcd.setCursor(0, 0); lcd.print(typ[2]);lcd.setCursor(0, 2); lcd.print(typ[7]);lcd.setCursor(0, 3); lcd.print(typ[8]);break;
      case 3: Serial.println(typ[3]);lcd.setCursor(0, 0); lcd.print(typ[3]);lcd.setCursor(0, 2); lcd.print(typ[7]);lcd.setCursor(0, 3); lcd.print(typ[8]);break;
      case 4: Serial.println(typ[4]);lcd.setCursor(0, 0); lcd.print(typ[4]);lcd.setCursor(0, 2); lcd.print(typ[7]);lcd.setCursor(0, 3); lcd.print(typ[8]);break;
      case 5: Serial.println(typ[5]);lcd.setCursor(0, 0); lcd.print(typ[5]);lcd.setCursor(0, 2); lcd.print(typ[7]);lcd.setCursor(0, 3); lcd.print(typ[8]);break;
     }
}
               
    if (  mfrc522.PICC_IsNewCardPresent()) {
     
  }else steps=0;    
 
  if (  mfrc522.PICC_ReadCardSerial()) {  
    digitalWrite(buzzer,HIGH);
    delay(100);
    digitalWrite(buzzer,LOW);
  steps=1;
  }
  else {
    steps=0;  return;
    }



if(steps==1){
lcd.clear();

 switch(Poti_read){                                    
     case 0:   medi_effekt=Medi_Sorte(A,kontroll_block); lcd.setCursor(0, 0); lcd.print(typ[9]);digitalWrite(bluePin,LOW);delay(1000);
     
     
               switch(medi_effekt){                  
                case 1:         lcd.setCursor(0, 2); lcd.print(typ[1]);Serial.println(typ[1]);digitalWrite(greenPin,HIGH);digitalWrite(redPin,LOW);delay(1500);break;  
                case 2:         lcd.setCursor(0, 2); lcd.print(typ[2]);Serial.println(typ[2]);digitalWrite(greenPin,HIGH);digitalWrite(redPin,LOW);delay(1500);break;    
                case 3:         lcd.setCursor(0, 2); lcd.print(typ[3]);Serial.println(typ[3]);digitalWrite(greenPin,HIGH);digitalWrite(redPin,LOW);delay(1500);break;  
                case 4:         lcd.setCursor(0, 2); lcd.print(typ[4]);Serial.println(typ[4]);digitalWrite(greenPin,HIGH);digitalWrite(redPin,LOW);delay(1500);break; 
                case 5:         lcd.setCursor(0, 2); lcd.print(typ[5]);Serial.println(typ[5]);digitalWrite(greenPin,HIGH);digitalWrite(redPin,LOW);delay(1500);break;   
                default:        lcd.setCursor(0, 2); lcd.print("Unbekannt      ");Serial.println("Unbekannt      ");digitalWrite(greenPin,LOW);digitalWrite(redPin,HIGH);delay(2000);break;   
               }
     
            //   id=id_reading(); lcd.setCursor(0, 3);   lcd.print(id);break; //mit Anzeige ID
                 lcd.setCursor(0, 3);   lcd.print(typ[6]);break;//ohne Anzeige ID
     
     case 1:   id=id_reading(); 
               error3=error3+writing(A,kontroll_block,random(100,99999999),id+code[0]);
               lcd.setCursor(0, 0);
               lcd.print(typ[1]);
               Serial.print(typ[1]);
               Serial.println(typ[11]);
               digitalWrite(greenPin,HIGH);
          break;
          
     case 2:   id=id_reading(); 
               error3=error3+writing(A,kontroll_block,random(100,99999999),id+code[1]);
               lcd.setCursor(0, 0);
               lcd.print(typ[2]);
               Serial.print(typ[2]);
               Serial.println(typ[11]);
               digitalWrite(greenPin,HIGH);
           break;
           
     case 3:   id=id_reading(); 
               error3=error3+writing(A,kontroll_block,random(100,99999999),id+code[2]);
               lcd.setCursor(0, 0);lcd.print(typ[3]);
               Serial.print(typ[3]);
               Serial.println(typ[11]);
               digitalWrite(greenPin,HIGH);
           break;
           
     case 4:   id=id_reading(); 
               error3=error3+writing(A,kontroll_block,random(100,99999999),id+code[3]);
               lcd.setCursor(0, 0);lcd.print(typ[4]);Serial.print(typ[4]);
               Serial.println(typ[11]);
               digitalWrite(greenPin,HIGH);
           break;
           
     case 5:   id=id_reading(); 
               error3=error3+writing(A,kontroll_block,random(100,99999999),id+code[4]);
               lcd.setCursor(0, 0);
               lcd.print(typ[5]);
               Serial.print(typ[5]);
               Serial.println(typ[11]);
               digitalWrite(greenPin,HIGH);
           break;
        }
      steps=2;
         
  }

if(steps==2){ 
    if(Poti_read!=0){
      digitalWrite(bluePin,LOW);
digitalWrite(greenPin,HIGH);
lcd.setCursor(0, 1);   lcd.print("|.             |");   
error3=error3+writing(A,1,random(100,99999999),random(100,99999999));
error3=error3+writing(A,2,random(100,99999999),random(100,99999999));
error3=error3+writing(A,4,random(100,99999999),random(100,99999999));
lcd.setCursor(0, 1);   lcd.print("|..            |");

error3=error3+writing(A,5,random(100,99999999),random(100,99999999));
error3=error3+writing(A,6,random(100,99999999),random(100,99999999));
error3=error3+writing(A,8,random(100,99999999),random(100,99999999));
lcd.setCursor(0, 1);   lcd.print("|...           |");

error3=error3+writing(A,9,random(100,99999999),random(100,99999999));
error3=error3+writing(A,12,random(100,99999999),random(100,99999999));
error3=error3+writing(A,13,random(100,99999999),random(100,99999999));
lcd.setCursor(0, 1);   lcd.print("|....          |");

error3=error3+writing(A,14,random(100,99999999),random(100,99999999));
error3=error3+writing(A,16,random(100,99999999),random(100,99999999));
error3=error3+writing(A,17,random(100,99999999),random(100,99999999));
lcd.setCursor(0, 1);   lcd.print("|.....         |");

error3=error3+writing(A,18,random(100,99999999),random(100,99999999));
error3=error3+writing(A,20,random(100,99999999),random(100,99999999));
error3=error3+writing(A,21,random(100,99999999),random(100,99999999));                   
lcd.setCursor(0, 1);   lcd.print("|......        |");

error3=error3+writing(A,22,random(100,99999999),random(100,99999999));
error3=error3+writing(A,24,random(100,99999999),random(100,99999999));
error3=error3+writing(A,25,random(100,99999999),random(100,99999999));
lcd.setCursor(0, 1);   lcd.print("|.......       |");

error3=error3+writing(A,26,random(100,99999999),random(100,99999999));
error3=error3+writing(A,28,random(100,99999999),random(100,99999999));
error3=error3+writing(A,29,random(100,99999999),random(100,99999999));
lcd.setCursor(0, 1);   lcd.print("|........      |");

error3=error3+writing(A,30,random(100,99999999),random(100,99999999));
error3=error3+writing(A,32,random(100,99999999),random(100,99999999));
error3=error3+writing(A,33,random(100,99999999),random(100,99999999));
lcd.setCursor(0, 1);   lcd.print("|.........     |");

error3=error3+writing(A,34,random(100,99999999),random(100,99999999));
error3=error3+writing(A,36,random(100,99999999),random(100,99999999));
error3=error3+writing(A,37,random(100,99999999),random(100,99999999));
error3=error3+writing(A,38,random(100,99999999),random(100,99999999));
error3=error3+writing(A,40,random(100,99999999),random(100,99999999));
error3=error3+writing(A,41,random(100,99999999),random(100,99999999));
lcd.setCursor(0, 1);   lcd.print("|..........    |");
digitalWrite(greenPin,LOW);
error3=error3+writing(A,42,random(100,99999999),random(100,99999999));
error3=error3+writing(A,44,random(100,99999999),random(100,99999999));
error3=error3+writing(A,45,random(100,99999999),random(100,99999999));
lcd.setCursor(0, 1);   lcd.print("|...........   |");

error3=error3+writing(A,46,random(100,99999999),random(100,99999999));
error3=error3+writing(A,48,random(100,99999999),random(100,99999999));
error3=error3+writing(A,49,random(100,99999999),random(100,99999999));
error3=error3+writing(A,50,random(100,99999999),random(100,99999999));
error3=error3+writing(A,52,random(100,99999999),random(100,99999999));
lcd.setCursor(0, 1);   lcd.print("|............  |");

error3=error3+writing(A,53,random(100,99999999),random(100,99999999));
error3=error3+writing(A,54,random(100,99999999),random(100,99999999));
error3=error3+writing(A,56,random(100,99999999),random(100,99999999));
error3=error3+writing(A,57,random(100,99999999),random(100,99999999));
lcd.setCursor(0, 1);   lcd.print("|............. |");

error3=error3+writing(A,58,random(100,99999999),random(100,99999999));
error3=error3+writing(A,60,random(100,99999999),random(100,99999999));
error3=error3+writing(A,61,random(100,99999999),random(100,99999999));
error3=error3+writing(A,62,random(100,99999999),random(100,99999999));
    
if(error3==0){
lcd.setCursor(0, 1);   lcd.print("|..............|");
lcd.setCursor(0, 2);   lcd.print("geschrieben    ");
lcd.setCursor(0, 3);   lcd.print("camoflage done ");

Serial.println("Fertig");
      digitalWrite(buzzer,HIGH);
    delay(100);
    digitalWrite(buzzer,LOW);
delay(2000); 
steps=3;}
           
         if(error3!=0){
            digitalWrite(buzzer,HIGH);
    delay(100);
    digitalWrite(buzzer,LOW);
    delay(100);
      digitalWrite(buzzer,HIGH);
    delay(100);
    digitalWrite(buzzer,LOW);
    delay(100);
      digitalWrite(buzzer,HIGH);
    delay(100);
    digitalWrite(buzzer,LOW);
    
  digitalWrite(redPin,HIGH);
  Serial.println("Fehler");
      delay(500); 
    
      steps=3;
  }}if (Poti_read==0){steps=3;}
    }
 if(steps==3){
  lcd.clear();
  digitalWrite(redPin,LOW); 
  digitalWrite(bluePin,LOW); 
  digitalWrite(greenPin,LOW); 
  error3=0;
      mfrc522.PICC_HaltA();
      mfrc522.PCD_StopCrypto1(); 
      steps=0;
  }



}

//*****************************************************************************************//
   
long rfid_reading(byte keys[],byte block)
{

  MFRC522::MIFARE_Key key; 
  for (byte i = 0; i < 6; i++) key.keyByte[i] = keys[i];// 0xFF;

  byte trailerBlock = block * 4 + 3;
  byte len=18;
  byte buffer1[18];
  int WERTA0,WERTA1,WERTA2,WERTA3,WERTA4;
  int WERTB0,WERTB1,WERTB2,WERTB3,WERTB4;
  long varA,varA2,varA3,varA4,varA5;
  long varB,varB2,varB3,varB4,varB5;
 
  MFRC522::StatusCode status;
  
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid)); 
  if (status != MFRC522::STATUS_OK) {// Serial.println("Error1");Serial.println(block);
    return 'y';
  }

  status = mfrc522.MIFARE_Read(block, buffer1, &len);
  if (status != MFRC522::STATUS_OK) {//Serial.print("Error2");Serial.println(block);
    return 'y';
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

}


//*****************************************************************************************//
     int writing(byte keys[],byte block,unsigned long variableA, unsigned long variableB) {
    byte buffer[16];
    byte status;
   // int paint=1;
    long varAA,varAB,varAC,varAD,varAX,varAY,varAZ,varAA1,varAB1,varAC1,varAD1,varAX1,varAY1,varAZ1;
    long varBA,varBB,varBC,varBD,varBX,varBY,varBZ,varBA1,varBB1,varBC1,varBD1,varBX1,varBY1,varBZ1;
    byte trailerBlock = block * 4 + 3;
     MFRC522::MIFARE_Key key;
     for (byte i = 0; i < 6; i++) key.keyByte[i] = keys[i];
 
    
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
                  
                      
                      
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_B, block, &key, &(mfrc522.uid)); 
  if (status != MFRC522::STATUS_OK) {Serial.println("Error1");
      return 1;
  }
               
          status = mfrc522.MIFARE_Write(block, buffer, 16);
  if (status != MFRC522::STATUS_OK) {     Serial.println("Error2");    
    return 1;
  }
     else Serial.println("Write finished");delay(10);

   return 0;
     }
    
//*****************************************************************************************//
int Medi_Sorte(byte keys[],int block){
int kind=0;
unsigned long A=0;

medi=id_reading();

A= rfid_reading(keys,block);
secure=ergebnisB;

     art= secure- medi; 
  //   Serial.print("Secure:");Serial.print(secure);Serial.print(" : ");Serial.print("medi:");Serial.print(medi);Serial.print(" : ");Serial.println(art);
     //Serial.println(art);
              switch (art) {

                            case 255: //Nanoclean
                            kind=1;
                            break;
                            
                            case 177://Dekon
                            kind=2;
                            break;   
                                                                  
                            case 367: //Blutwäsche
                            kind=3;
                            break;   
                            
                            case 583://Cleanray
                            kind=4;
                            break;
                         
                            case 722://Lifecleaner
                            kind=5;
                            break;
                    
                            }
return kind;
}
//*****************************************************************************************//
long id_reading(){
    long medi_id=0;

for (byte i = 0; i < 4; i++)
    {
     medi_id=((medi_id+mfrc522.uid.uidByte[i])*10); 
     if(i>=3){
      return medi_id;
     }
    }
}
//*****************************************************************************************//
//*****************************************ENDE********************************************//
  
    
