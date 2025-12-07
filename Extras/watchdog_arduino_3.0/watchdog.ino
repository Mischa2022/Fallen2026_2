unsigned long watchdog_read(char &ubergabe_char,unsigned long &ubergabe,char enter){
char read_Char2;
/*
#define anzahl_werte 11
bool stringComplete = false;  
char char_read[anzahl_werte];
int counter=0;
unsigned long wert=0;
int port= 0;
int werte[anzahl_werte];
String read_String = "";*/

  while (Serial.available()){
   
     read_Char2 = (char)Serial.read();
    if (read_Char2 != enter) {
      read_String2 += read_Char2;
      counter2=counter2+1;
      port2=3;
      
    }
  }

    if (read_Char2 == enter){
      
      read_String2=read_String2+"\0";
      read_String2.toCharArray(char_read2,anzahl_werte2-1);
      //Serial.println(read_String);
     char_read2[0]=char_read2[0];
      for(int i=1;i<=counter2-1;i++){
        if((int)char_read2[i]-48>=0){
          werte2[i]=(int)char_read2[i]-48;
        } else { 
          werte2[i]=0;
        }
      }
      if(counter2>1){
        wert2=(wert2+werte2[1]);
        for( int y=2;y<=counter2-1;y++){
         if(werte2[y]>=0){ wert2=(wert2*10)+werte2[y]; }
         if(werte2[y]==-1){ wert2=wert2; }
        }
        stringComplete2 = true;
      }
      if(counter2==1){
        wert2=0;
        stringComplete2 = true;
      }
    }
    
  
    
  if (stringComplete2) {
    ubergabe_char=char_read2[0];
    ubergabe=wert2; 
    counter2=0;
    read_String2="";
    
    stringComplete2 = false; 
  }
    
  if (!stringComplete2) {
    memset(char_read2, ' ', sizeof(char_read2));
    memset(werte2, -1, sizeof(werte2));  
    wert2=0;
  }
}

void watchdog(const long timer){
  //laufende Zeit bis zum nächsten Reset
  u8g2.clearBuffer();       
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(0,10,"Naechster Reset in:"); 
  u8g2.setCursor(110,10);
  u8g2.print((timer-(aktuelleMillis-vergangeneMillis))/1000); 
  
  
  u8g2.setCursor(0,20);
  u8g2.print(anzahl_reset);
  u8g2.drawStr(60,20,"Reset bisher"); 
  u8g2.sendBuffer(); 
 Serial.print("Naechster Reset in:");Serial.print((timer-(aktuelleMillis-vergangeneMillis))/1000);Serial.print(" | Reset bisher:");Serial.println( anzahl_reset);
  


  if (meldung==true){
    sendCommand(CMD_PLAY_W_INDEX,0X01);
    delay(8000);
  }

  
  else if (aktuelleMillis - vergangeneMillis >= timer) {
  u8g2.clearBuffer();       
  u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.drawStr(0,20,"Zu spaet!"); 
  u8g2.sendBuffer(); 
   
  
    digitalWrite(reset_Pin, LOW);
    delay(1000);
    digitalWrite(reset_Pin, HIGH);
    anzahl_reset=anzahl_reset+1;
    if(anzahl_reset==warnung){meldung=true;}
    else{
    vergangeneMillis = aktuelleMillis;
    }
   
   
  }
  /*
  if(button==0){ //manueller Reset/ Entstörung
   
    digitalWrite(reset_Pin, LOW);
    delay(1000);
    digitalWrite(reset_Pin, HIGH);
    meldung=false;
    anzahl_reset=0;
    //vergangeneMillis =0;
    
  }
*/

  
watchdog_read(ziel_charwtd,ziel_longwtd,'\n');
if(ziel_charwtd=='y'){
  //Serial.print(ziel_charwtd);Serial.println(ziel_longwtd);
  vergangeneMillis = aktuelleMillis;
}

ziel_charwtd=' '; 
ziel_longwtd=0;

  
}

void sendCommand(int8_t command, int16_t dat)
{
 // delay(20);
 Send_buf[0] = 0x7e; //starting byte
 Send_buf[1] = 0xff; //version
 Send_buf[2] = 0x06; //the number of bytes of the command without starting byte and ending byte
 Send_buf[3] = command; //
 Send_buf[4] = 0x00;//0x00 = no feedback, 0x01 = feedback
 Send_buf[5] = (int8_t)(dat >> 8);//datah
 Send_buf[6] = (int8_t)(dat); //datal
 Send_buf[7] = 0xef; //ending byte

  for (uint8_t i = 0; i < 8; i++)
  {
    mp3.write(Send_buf[i]) ;

  }

}


//*****************************************************************************************//
