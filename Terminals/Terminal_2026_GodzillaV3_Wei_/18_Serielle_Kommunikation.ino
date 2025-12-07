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
/*
  while (Serial2.available()){
   
     read_Char = (char)Serial2.read();
    if (read_Char != enter) {
      read_String += read_Char;
      counter=counter+1;
      port=2;
      
    }
  }*/

  while (Serial3.available()){
   
     read_Char = (char)Serial3.read();
    if (read_Char != enter) {
      read_String += read_Char;
      counter=counter+1;
      port=3;
     
    }
   
  }

    if (read_Char == enter){
      
      read_String=read_String+"\0";
      read_String.toCharArray(char_read,anzahl_werte-1);
      //Mitschnitt
     // Serial.print(F("Nachricht:"));Serial.print(read_String);Serial.print(F(" von Port:"));Serial.println(port);

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
    ubergabe_char=char_read[0];
    ubergabe=wert; 
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

//*****************************************************************************************//
int print_menu(){
//Serial.println(F("c+Konfig = Konfigueberarbeiten"));
Serial.println(F("Optionen"));
Serial.println(F(""));
Serial.println(F("TERMINAL--------------------------"));
Serial.println(F("j Uhr stellen Seriell "));
Serial.println(F("f Checkinlog lesen"));
Serial.println(F("g Buchungslog lesen"));
Serial.println(F("k Medilog lesen"));
Serial.println(F(""));
Serial.println(F("DONGEL--------------------------"));
Serial.println(F("Checkin: 1=random gruen,2=random gelb,3=random rot"));
Serial.println(F("h+ Checkin Mensch ab Constart"));
Serial.println(F("H+ Checkin Mensch ab jetzt"));
Serial.println(F("v reset"));
Serial.println(F(""));
Serial.println(F("ANALYSE-------------------------"));
Serial.println(F("% Analyse ausfuehrlich"));
Serial.println(F("a+ wert Analyse "));
Serial.println(F(" 1 nur spieler infos ohne medi"));
Serial.println(F(" 2 Nur Nanoclean infos"));
Serial.println(F(" 3 Nur Dekon infos"));
Serial.println(F(" 4 Nur Lifecleaner infos"));
Serial.println(F(" 5 Nur Blutwaesche infos"));
Serial.println(F(" 6 Nur Cleanray infos"));
Serial.println(F(" 10 alle infos"));
Serial.println(F(""));
Serial.println(F("MEDIKATION----------------------"));
Serial.println(F("b+Wert Einnahme Medikament mit kontrolle tages/-Conmaximum wie ray-o-mat"));
Serial.println(F("1 update buchen")); 
Serial.println(F("2 Nanoclean    "));
Serial.println(F("3 Dekon        "));
Serial.println(F("4 Lifecleaner  "));
Serial.println(F("5 Blutwaesche   "));
Serial.println(F("6 Cleanray     "));
Serial.println(F("7 drawback     "));
Serial.println(F(""));
Serial.println(F("MANIPULATION--------------------"));
Serial.println(F("m+Wert Typus aendern "));
Serial.println(F("100   = Mensch"));
Serial.println(F("360   = Mutant"));
Serial.println(F("r+ Wert  Raywert aendern  "));
Serial.println(F("1 random Gruen")); 
Serial.println(F("2 random Gelb"));
Serial.println(F("3 random Rot "));
Serial.println(F(">3 Raywert  "));
Serial.println(F("zbs r400000= raywert 400"));
Serial.println(F("l+ Stunden  Lifecleaner schreiben  "));
Serial.println(F("zbs l4= Lifecleaner fuer 4 Stunden"));
Serial.println(F(""));
Serial.println(F("RECHTE--------------------------"));
Serial.println(F("o+Wert Rechte fuer Medibuchungen"));
Serial.println(F("10000  = Nanoclean"));//
Serial.println(F("1000   = Blutwaesche"));//
Serial.println(F("100    = Cleanray"));//
Serial.println(F("10     = Lifecleaner"));//
Serial.println(F("1      = Dekon"));//
Serial.println(F("zbs 10001= Nanoclean+Dekon"));//
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
        Serial2.println("");delay(10);
      }
      else{
        Serial2.print("");delay(10);
      }    
    }
//************************************************************
    if(ausgabe==3){
      
        if(titel!=""){
        Serial3.write(titel);delay(write_pause);
          } 
        if(inhalt!=""){
         Serial3.print(inhalt);delay(write_pause);
          }
        if(wert!=""){
          if(unix==false){
          Serial3.print(wert);delay(write_pause);
            }
          if(unix==true){
          unix_converter(wert,UTC);  
            }
          }
          
      if(ln==true){
        Serial3.write('\n');delay(write_pause);
      }
      else{
        Serial3.write("");delay(write_pause);
      }    
    }


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
