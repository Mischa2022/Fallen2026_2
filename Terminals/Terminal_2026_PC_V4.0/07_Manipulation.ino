/*Auflistung Unterfunktionen, die fuer manuelle Manipulation einens Dongels benoetigt werden
 * 
 * Typus_aendern      // Hilfsfunktion um aus Mensch einen Mutanten zu machen und umgekehrt
 * ray_manipulation   // Hilfsfunktion um Raywert frei zu aendern
 * lifecleaner_write  // Hilfsfunktion um Lifecleaner zu schreiben, ohne Dokumentation
 * medi_rechte        // Hilfsfunktion um Medirechte auf leere oder Spielerdongel zu schreiben
 */
 

int Typus_aendern(unsigned long art){

if(art>1000){art=art/10;}

      newkey();// falls Dongel bereits eingecheckt
      delay(50);
      key__searchB(14);// falls Dongel noch nicht eingecheckt/ fuer Dummy-Dongel
      delay(50);
      rfid_reading(knownKeys[0],Admin2_block); //57
      LifeCleaner_effekt_read=ergebnisA;
      archtype_read=ergebnisB; 

if(art==100){
       myprint("Typus auf Mensch aendern gestartet","","",true,true,false,1,port);

      writing(knownKeys[key_used],57,LifeCleaner_effekt_read,100);
      Tag_analyse(1,0);//fuer ausgabe der aenderung
      msg2="Mensch ";
      msg4="Typus";
      msg5=" aendern fertig";
}
else if(art==360){
      myprint("Typus auf Mutant aendern gestartet","","",true,true,false,1,port);

      writing(knownKeys[key_used],57,LifeCleaner_effekt_read,360);
      Tag_analyse(1,0);//fuer ausgabe der aenderung
      msg2="Mutant ";
      msg4="Typus";
      msg5=" aendern fertig";
}
else if(art==250){
      myprint("Typus auf Bunkerbewohner aendern gestartet","","",true,true,false,1,port);

      writing(knownKeys[key_used],57,LifeCleaner_effekt_read,250);
      Tag_analyse(1,0);//fuer ausgabe der aenderung
      msg2="Bunki ";
      msg4="Typus";
      msg5=" aendern fertig";
}

else{
      msg2=" ";
      msg4="Unbekannte ";
      msg5=" Eingabe";

}


}
//*****************************************************************************************//
int ray_manipulation(unsigned long wert){
   myprint("Raywert aendern gestartet","","",true,true,false,1,port);


      newkey();// falls Dongel bereits eingecheckt
      delay(100);
      key__searchB(14);// falls Dongel noch nicht eingecheckt/ fuer Dummy-Dongel
      delay(100);
      rfid_reading(knownKeys[0],Admin3_block ); //56
      Con_End_read=ergebnisA;
      Ray_value_extern_read=ergebnisB; 
      
      if(wert>maximum_ray_writing){
        wert=maximum_ray_writing;
        } // abfangen von zu großen werten

      if(wert<minimum_ray_writing){
        wert=minimum_ray_writing;
        } // abfangen von zu kleinen werten
        
      writing(knownKeys[key_used],56,Con_End_read,wert); 
      Tag_analyse(1,0); //fuer ausgabe der aenderung
      msg4="Raywert";
      msg5=" aendern fertig";
      ergebnisA=0;
      ergebnisB=0;
}
//*****************************************************************************************//
int lifecleaner_write(unsigned long effekt){
  if(effekt>100){effekt=effekt/10;}
  unsigned long effekt_speicher=0;
      t = rtc.now();
      aktuell_time=t.unixtime();
      Tag_analyse(1,0); //fuer ausgabe der aenderung
      myprint("Lifecleaner schreiben","","",true,true,false,1,port);
    
      newkey();// falls Dongel bereits eingecheckt
      delay(100);
      key__searchB(14);
      delay(50);
      rfid_reading(knownKeys[0],Admin2_block); //57
      LifeCleaner_effekt_read=ergebnisA;
      archtype_read=ergebnisB; 

    
      myprint("Werte bisher","","",true,true,false,1,port);
   
      myprint("Archtype:","",archtype_read,true,true,false,1,port);
   
     myprint("LifeCleaner_effekt:","",LifeCleaner_effekt_read,true,true,false,1,port);
   
      delay(100);
      if(effekt>0){
      effekt_speicher=effekt*3600;
      writing(knownKeys[key_used],57,aktuell_time+effekt_speicher,archtype_read); }
      if(effekt==0){
        writing(knownKeys[key_used],57,0,archtype_read); 
      }
      Tag_analyse(1,0); //fuer ausgabe der aenderung
      msg4="Lifecleaner";
      msg5=" geschrieben";
      ergebnisA=0;
      ergebnisB=0;
}      

//*****************************************************************************************//
int medi_rechte(unsigned long wert){
      if(wert>11111){wert=wert/10;}
      myprint("Medirechte schreiben gestartet","","",true,true,false,1,port);
 
      newkey(); // falls Dongel bereits eingecheckt
      delay(100);
      key__searchB(1); // falls Dongel noch nicht eingecheckt/ fuer Dummy-Dongel
      delay(50);
      writing(knownKeys[key_used],Admin4_block,0,wert);      //wird in Block 1 bisher geschreiben...        
      Tag_analyse(1,0); //fuer ausgabe der aenderung
      msg4="Medirechte";
      msg5=" geschrieben";
}
//*****************************************************************************************//
int korrektur(String auswahl){
  
  String ausgabe;
  char* titel[]{"Nanoclean","Dekon","Lifecleaner","Bloodclean","Cleanray"};
  int wo;
  int was;
  int ziel;
  int Bereich;
  char* wer;
  char auswahlpuffer[29];
  int Stunden;
  int Minuten;
  int Sekunden;
  int Tag;
  int Monat;
  long Jahr;
  
  DateTime new_t;  
  unsigned long new_time;
  auswahl.toCharArray(auswahlpuffer,29);


unsigned long  buffer_read1;
unsigned long  buffer_read2;
wer=auswahlpuffer[1];

was=((auswahlpuffer[3]-'0')*10)+(auswahlpuffer[4]-'0');

Jahr=((auswahlpuffer[6]-'0')*1000)+((auswahlpuffer[7]-'0')*100)+((auswahlpuffer[8]-'0')*10)+(auswahlpuffer[9]-'0');
Monat=((auswahlpuffer[11]-'0')*10)+(auswahlpuffer[12]-'0');
Tag=((auswahlpuffer[14]-'0')*10)+(auswahlpuffer[15]-'0');
Stunden=((auswahlpuffer[17]-'0')*10)+(auswahlpuffer[18]-'0');
            Minuten=((auswahlpuffer[20]-'0')*10)+(auswahlpuffer[21]-'0');
            Sekunden=((auswahlpuffer[26]-'0')*10)+(auswahlpuffer[27]-'0');


new_t=(DateTime(Jahr, Monat, Tag, Stunden,Minuten,Sekunden));
new_time=new_t.unixtime();

  if(wer=='N'){wo=1;}
  else if(wer=='D'){wo=2;}
  else if(wer=='L'){wo=3;}
  else if(wer=='B'){wo=4;}
  else if(wer=='C'){wo=5;}
  else{wo=6;}
  
switch(wo){
  
case 1:     
              switch(was){
                case 1: ziel=54;Bereich=1;
                break;
                case 2:ziel=54;Bereich=2;
                break;
                case 3:ziel=53;Bereich=1;
                break;
                case 4:ziel=53;Bereich=2;
                break;
                case 5:ziel=52;Bereich=1;
                break;
                case 6:ziel=52;Bereich=2;
                break;
                case 7:ziel=50;Bereich=1;
                break;
                case 8:ziel=50;Bereich=2;
                break;
                default :Serial.println(F("Falsche Menge"));ziel=0; Bereich=0;
                break;
              }
      break;
case 2:     

              switch(was){
                case 1: ziel=49;Bereich=1;
                break;
                case 2:ziel=49;Bereich=2;
                break;
                case 3:ziel=48;Bereich=1;
                break;
                case 4:ziel=48;Bereich=2;
                break;
                case 5:ziel=46;Bereich=1;
                break;
                case 6:ziel=46;Bereich=2;
                break;
                case 7:ziel=45;Bereich=1;
                break;
                case 8:ziel=45;Bereich=2;
                break;
                case 9:ziel=44;Bereich=1;
                break;
                case 10:ziel=44;Bereich=2;
                break;
                case 11:ziel=42;Bereich=1;
                break;
                case 12:ziel=42;Bereich=2;
                break;
                case 13:ziel=41;Bereich=1;
                break;
                case 14:ziel=41;Bereich=2;
                break;
                default :Serial.println(F("Falsche Menge"));ziel=0; Bereich=0;
                break;
              }
      break;
case 3:     


              switch(was){
                case 1: ziel=37;Bereich=1;
                break;
                case 2:ziel=37;Bereich=2;
                break;
                case 3:ziel=36;Bereich=1;
                break;
                case 4:ziel=36;Bereich=2;
                break;
                case 5:ziel=34;Bereich=1;
                break;
                case 6:ziel=34;Bereich=2;
                break;
                case 7:ziel=33;Bereich=1;
                break;
                case 8:ziel=33;Bereich=2;
                break;
                case 9:ziel=32;Bereich=1;
                break;
                case 10:ziel=32;Bereich=2;
                break;
              
                default :Serial.println(F("Falsche Menge"));ziel=0; Bereich=0;
                break;
              }
    break;

case 4:    

              switch(was){
                case 1: ziel=30;Bereich=1;
                break;
                case 2:ziel=30;Bereich=2;
                break;
                case 3:ziel=29;Bereich=1;
                break;
                case 4:ziel=29;Bereich=2;
                break;
                case 5:ziel=28;Bereich=1;
                break;
                case 6:ziel=28;Bereich=2;
                break;
                case 7:ziel=26;Bereich=1;
                break;
                case 8:ziel=26;Bereich=2;
                break;
                case 9:ziel=25;Bereich=1;
                break;
                case 10:ziel=25;Bereich=2;
                break;
              
                default :Serial.println(F("Falsche Menge"));ziel=0; Bereich=0;
                break;
              }
    break;
    
case 5:     

              switch(was){
                case 1: ziel=18;Bereich=1;
                break;
                case 2:ziel=18;Bereich=2;
                break;
                case 3:ziel=17;Bereich=1;
                break;
                case 4:ziel=17;Bereich=2;
                break;
                case 5:ziel=16;Bereich=1;
                break;
                case 6:ziel=16;Bereich=2;
                break;
                case 7:ziel=14;Bereich=1;
                break;
                case 8:ziel=14;Bereich=2;
                break;
             
                default :Serial.println(F("Falsche Menge"));ziel=0; Bereich=0;
                break;
              }
    break;   
    
default: Serial.println(F("Falsches Medikament"));ziel=0; Bereich=0;
    break;
  }
  if(ziel!=0){
  ausgabe=titel[wo-1];

  newkey();
      rfid_reading(knownKeys[0],ziel);
      buffer_read1=ergebnisA;
      buffer_read2=ergebnisB; 
  
  
  if(Bereich==1){
    writing(knownKeys[last_key],ziel, new_time, buffer_read2);
  }
   if(Bereich==2){
    writing(knownKeys[last_key],ziel, buffer_read1, new_time);
  }
  Serial.print(ausgabe);Serial.print(F(" | Ziel: "));Serial.print(ziel);Serial.print(F(" |A: "));Serial.print(buffer_read1);Serial.print(F(" |B: "));Serial.print(buffer_read2);Serial.print(F(" |Zeit:"));Serial.print(new_time);
  Serial.println();
}

}
