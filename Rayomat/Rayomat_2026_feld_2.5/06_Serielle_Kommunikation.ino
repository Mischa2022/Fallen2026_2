/*Auflistung Unterfunktionen, die für Serielle Kommunikation benötigt werden
 * 
 * serial_read     //Helferfunktion um eingehende Werte zu interpretieren. TeilA besteht immer aus einem Char und TeilB kann ein unsigned Long sein 

 */


unsigned long serial_read(char &ubergabe_char,unsigned long &ubergabe,char enter){

  while (Serial.available()) {
    char read_Char = (char)Serial.read();
    if (read_Char != enter) {
      read_String += read_Char;
      counter=counter+1;
    }
    if (read_Char == enter){
      read_String=read_String+"\0";
      read_String.toCharArray(char_read,anzahl_werte-1);
      char_read[0]=char_read[0];
      for(int i=1;i<=counter-1;i++){
        if((int)char_read[i]-48>=0){
          werte[i]=(int)char_read[i]-48;
        } else { 
          werte[i]=0;
        }
      }
      if(counter>1){
        wert=(wert+werte[1]);
        for( int y=2;y<=counter-1;y++){
         if(werte[y]>=0){ wert=(wert*10)+werte[y]; }
         if(werte[y]==-1){ wert=wert; }
        }
        stringComplete = true;
      }
      if(counter==1){
        wert=0;
        stringComplete = true;
      }
    }
  }  
  
    
  if (stringComplete) {
    ubergabe_char=char_read[0];
    ubergabe=wert; 
    counter=0;
    read_String="";
    stringComplete = false; 
  }
    
  if (!stringComplete) {
    memset(char_read, ' ', sizeof(char_read));
    memset(werte, -1, sizeof(werte));  
    wert=0;
  }
}

//*****************************************************************************************//


void myprint(char*titel,String inhalt,unsigned long wert,bool wp,bool ln,bool unix,int debuglevel,int ausgabe){

ausgabe=0;//aushebeln der esp_schnittstelle. Aktuell nicht nötig
 
//  myprint(Text:"",Text2:"",Wert:"",writeorprint:false,ln_on:true,unix_on:false,debug:1,port:0);
  
  
 // myprint(Text:"Nun Dongel auflegen",Text2:""          ,""                 ,false    ,true     ,false      ,1              ,0);
  //myprint(char*titel           ,char*inhalt ,unsigned long wert ,bool wp  ,bool ln  ,bool unix  ,int debuglevel ,int ausgabe){
  /*titel= bezeichnung der Ausgabe
   * inhalt = falls text und keine werte
   * wert = ausgabewerte
   * wp = write ==0 print ==1
   * ln = neue line oder nicht
   * unix= long konvertieren oder nur als wert ausgeben
   * debuglevel = falls ausgabe nur in bestimmten situationen erwünscht
   * ausgabe= auswahl des seriellen ports
   */
  
  if(debuglevel>=debug){

    if(ausgabe==0){
      
        if(titel!=""){
        Serial.print(titel);
          } 
        if(inhalt!=""){
        Serial.print(inhalt);
          }
        if(wert!=""){
          if(unix==false){
          Serial.print(wert);
            }
          if(unix==true){
          unix_converter(wert,UTC);  
            }
          }
          
      if(ln==true){
        Serial.println(F(""));
      }
      else{
        Serial.print(F(""));
      }    
    }
//************************************************************
    if(ausgabe==1){
      
      if(titel!=""){
      Serial1.print(titel);
      } 
        if(inhalt!=""){
        Serial1.print(inhalt);
        }
        if(wert!=""){
          if(unix==false){
          Serial1.print(wert);
          }
          if(unix==true){
          unix_converter(wert,UTC);  
          }
        }
      if(ln==true){
        Serial1.println(F(""));
      }
      else{
        Serial1.print(F(""));
      }    
    }
//************************************************************
    if(ausgabe==2){
      
      if(titel!=""){
      Serial2.print(titel);delay(10);
      } 
        if(inhalt!=""){
        Serial2.print(inhalt);delay(10);
        }
        if(wert!=""){
          if(unix==false){
          Serial2.print(wert);delay(10);
          }
          if(unix==true){
          unix_converter(wert,UTC);  
          }
        }
      if(ln==true){
        Serial2.println(F(""));delay(10);
      }
      else{
        Serial2.print(F(""));delay(10);
      }    
    }
//************************************************************
    if(ausgabe==3){
      
        if(titel!=""){
        Serial3.write(titel);//delay(50);
          } 
        if(inhalt!=""){
         Serial3.print(inhalt);//delay(50);
          }
        if(wert!=""){
          if(unix==false){
          Serial3.print(wert);//delay(50);
            }
          if(unix==true){
          unix_converter(wert,UTC);  
            }
          }
          
      if(ln==true){
        Serial3.write('\n');delay(50);
      }
      else{
        Serial3.write("");delay(50);
      }    
    }
  }
}
//************************************************************  
