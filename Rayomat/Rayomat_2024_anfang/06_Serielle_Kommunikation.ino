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
