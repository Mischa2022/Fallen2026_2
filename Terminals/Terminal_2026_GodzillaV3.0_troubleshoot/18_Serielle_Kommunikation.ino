/*Auflistung Unterfunktionen, die fuer Serielle Kommunikation benoetigt werden
 * 
 * serial_read    // Helferfunktion um eingehende Werte zu interpretieren. TeilA besteht immer aus einem Char und TeilB kann ein unsigned Long sein 
 * print_menu     // Hilfspunkt um im Betrieb alle moeglichen Eingaben ueber Seriell anzuzeigen
 * print_konfig() // ausgabe aktueller konfig
 * myprint        // eigene Schreibfunktion
 */



unsigned long serial_read(char &ubergabe_char,unsigned long &ubergabe,char enter){
char read_Char;

  while (Serial.available()){
   
     read_Char = (char)Serial.read();
    if (read_Char != enter) {
      read_String += read_Char;
      counter=counter+1;
      port=0;
      
    }
  }





    if (read_Char == enter){
      
      read_String=read_String+"\0";
      read_String.toCharArray(char_read,anzahl_werte-1);
      //Mitschnitt
  //    Serial.print("Nachricht:");Serial.print(read_String);Serial.print(" von Port:");Serial.println(port);

//uhrstellen start 
if(char_read[0]=='j'){

read_String.remove(0,1);
ubergabe_char='j';
//Serial.print("Rest:");
//Serial.print(read_String);
wert=read_String.toInt();
//Serial.print(" umgewandelt:");
//Serial.println(wert);
stringComplete = true;
}
//uhrstellen ende

else{
      
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
    wdt_reset();
    ubergabe_char=char_read[0];
    ubergabe=wert; 
    mfrc522.PCD_AntennaOn();
    delay(10);
    counter=0;
    read_String="";
//    Serial.print("Was ich raus gemacht habe: ");Serial.print(ubergabe_char);Serial.print(" ");Serial.println(ubergabe);
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

//ausgabe=0;//aushebeln der esp_schnittstelle. Aktuell nicht noetig
 
//  myprint(Text:"",Text2:"",Wert:"",writeorprint:false,ln_on:true,unix_on:false,debug:1,port:0);
  
  
 // myprint(Text:"Nun Dongel auflegen",Text2:""          ,""                 ,false    ,true     ,false      ,1              ,0);
  //myprint(char*titel           ,char*inhalt ,unsigned long wert ,bool wp  ,bool ln  ,bool unix  ,int debuglevel ,int ausgabe){
  /*titel= bezeichnung der Ausgabe
   * inhalt = falls text und keine werte
   * wert = ausgabewerte
   * wp = write ==0 print ==1
   * ln = neue line oder nicht
   * unix= long konvertieren oder nur als wert ausgeben
   * debuglevel = falls ausgabe nur in bestimmten situationen erwuenscht
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
        Serial.println("");
      }
      else{
        Serial.print("");
      }    
    }
//************************************************************
 

}
}
//************************************************************    
//Helferfunktion um ID´s von TAGs anzuzeigen

void dump_byte_array(byte *buffer, byte bufferSize) {
   
      
    
    for (byte i = 0; i < bufferSize; i++) {
        Serial.print(buffer[i] < 0x10 ? " 0" : " ");
        Serial.print(buffer[i], HEX);
    

       }
  
}

//*****************************************************************************************//

int serial_print_konfig(){

  Serial.print(F(" Con_Name              |" )); Serial.println( Con_Name              ); 
  Serial.print(F(" con_start_time        |" )); Serial.println( con_start_time        );
  Serial.print(F(" UTC                   |" )); Serial.println( UTC                   ); 
  Serial.print(F(" Korrektur             |" )); Serial.println( UNIX_korrektur        );
  Serial.print(F(" anzahl_tage           |" )); Serial.println( anzahl_tage           ); 
  Serial.print(F(" tagesdosis            |" )); Serial.println( tagesdosis            ); 
 
  
  Serial.print(F(" Cleanray_min_effekt   |" )); Serial.println( Cleanray_min_effekt   ); 
  Serial.print(F(" Cleanray_max_effekt   |" )); Serial.println( Cleanray_max_effekt   ); 
  
  Serial.print(F(" Clean_per_con         |" )); Serial.println( Clean_per_con         );
  Serial.print(F(" Clean_per_day         |" )); Serial.println( Clean_per_day         );                
     
  Serial.print(F(" LifeCleaner_buffer    |" )); Serial.println( LifeCleaner_buffer/3600); 
  Serial.print(F(" Life_per_con          |" )); Serial.println( Life_per_con          );
  Serial.print(F(" LifeCleaner_per_day   |" )); Serial.println( LifeCleaner_per_day   );

  Serial.print(F(" Bloodclean_min_effekt |" )); Serial.println( Bloodclean_min_effekt ); 
  Serial.print(F(" Bloodclean_max_effekt |" )); Serial.println( Bloodclean_max_effekt ); 
  Serial.print(F(" Blood_per_con         |" )); Serial.println( Blood_per_con         );
  Serial.print(F(" Blood_per_day         |" )); Serial.println( Blood_per_day         ); 
                  
  Serial.print(F(" Nanoclean_min_effekt  |" )); Serial.println( Nanoclean_min_effekt  ); 
  Serial.print(F(" Nanoclean_max_effekt  |" )); Serial.println( Nanoclean_max_effekt  );
  Serial.print(F(" Nano_per_con          |" )); Serial.println( Nano_per_con          );
  Serial.print(F(" Nano_per_day          |" )); Serial.println( Nano_per_day          );
                              
  Serial.print(F(" Dekon_min_effekt      |" )); Serial.println( Dekon_min_effekt      );
  Serial.print(F(" Dekon_max_effekt      |" )); Serial.println( Dekon_max_effekt      );           
  Serial.print(F(" Dekon_per_con         |" )); Serial.println( Dekon_per_con         );        
  Serial.print(F(" Dekon_per_day         |" )); Serial.println( Dekon_per_day         );
  
  
}                    
