/*Auflistung Unterfunktionen, die fuer manuelle Manipulation einens Dongels benoetigt werden
 * 
 * Typus_aendern      // Hilfsfunktion um aus Mensch einen Mutanten zu machen und umgekehrt
 * ray_manipulation   // Hilfsfunktion um Raywert frei zu aendern
 * lifecleaner_write  // Hilfsfunktion um Lifecleaner zu schreiben, ohne Dokumentation
 * medi_rechte        // Hilfsfunktion um Medirechte auf leere oder Spielerdongel zu schreiben
 */
 

int Typus_aendern(unsigned long art){
prozess();
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

   prozess();
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
