 /*Auflistung Unterfunktionen, die für Check einens Dongels benötigt werden
 * 
 * Check_rfid_tag     //Helferfunktion um einen Spieler_Dongel auf gespeicherte Werte zu prüfen
 */

int Check_rfid_tag(int variante,bool ausfuehrlich){



/*varianten
 * 1 nur spieler infos ohne medi
 * 2 Nur Nanoclean infos
 * 3 Nur Dekon infos
 * 4 Nur Lifecleaner infos
 * 5 Nur Blutwäsche infos
 * 6 Nur Cleanray infos
 * 10 alle infos
 */
 
// Lesen der zufüllenden Werte

//Con und Spielerrelevante Daten
//*************************************************************************************//


error=error+rfid_reading(knownKeys[0],Admin1_block); //58
//Serial.print(F("Error Admin1:"));Serial.println(error);
  Con_Start_read=ergebnisA;
  Last_Booking_read=ergebnisB; 

  ergebnisA=0;ergebnisB=0;    
    
error=error+rfid_reading(knownKeys[0],Admin2_block); //57
//Serial.print(F("Error Admin2:"));Serial.println(error);
  archtype_read=ergebnisB;
  //archtype_read=360;
  LifeCleaner_effekt_read=ergebnisA; 

  ergebnisA=0;ergebnisB=0;
    
error=error+rfid_reading(knownKeys[0],Admin3_block); //56
//Serial.print(F("Error Admin3:"));Serial.println(error);
  Con_End_read=ergebnisA;
  Ray_value_extern_read=ergebnisB; 
  
  ergebnisA=0;ergebnisB=0;  


//Nanocleaninformationen
//*************************************************************************************//


//Dekoninformationen
//*************************************************************************************//


//Lifecleanerinformationen
//*************************************************************************************//
 

//Blutwäscheinformationen
//*************************************************************************************//
 

//Cleanrayinformationen
//*************************************************************************************//


//Medirechte
//*************************************************************************************//


//Ausgabe der gelesenen Werte als UNIX-werte aber nur wenn error==0
//*************************************************************************************//

    Serial.println(F("READ"));
    Serial.print(F("Con_Start_read:"));//wird im folgenden Konvertiert
    Serial.print(Con_Start_read); //wird im folgenden Konvertiert
  
    Serial.println();
    Serial.print(F("Con_End_read:"));//wird im folgenden Konvertiert
    Serial.print(Con_End_read); //wird im folgenden Konvertiert

    Serial.println();
  
   Serial.print(F("Letzte Buchung:")); //für Godzilla eigentlich "Last_Booking_read:"
   Serial.print(Last_Booking_read);
   
   Serial.println();
   
   // Serial.print(F("archtype_read:"));//wird im folgenden Konvertiert
    //Serial.println(archtype_read); //wird im folgenden Konvertiert
    Serial.print(F("Archetyp:"));
    if(archtype_read==100){
      Serial.println(F("Mensch"));
      }//für Godzilla
      
    if(archtype_read==360){
      Serial.println(F("Mutant"));
      }//für Godzilla
      
    if(archtype_read==250){
     Serial.println(F("Bunkerbewohner"));
      }//für Godzilla 
      
    if(archtype_read==0){
      Serial.println(F("Kein Typus"));
    }//für Godzilla für Plots
    
   Serial.print(F("LifeCleanereffekt:"));//für Godzilla eigentlich "LifeCleaner effekt_read:"
   Serial.println(LifeCleaner_effekt_read);
   // Serial.print(F("Ray_value_intern_read:"); //wird momentan nicht gebraucht
   // Serial.println(Ray_value_intern_read);  //wird momentan nicht gebraucht
   
    Serial.print(F("Raywert:"));//für Godzilla eigentlich "Ray_value_extern_read:"
    Serial.println(Ray_value_extern_read);
raywert=Ray_value_extern_read/1000; 

if(raywert>450){
  Serial.println(F("Wert ist verkehrt!"));
  

  }
delay(200);
Serial.println(F("READ END"));
Serial.println(F("--------------------------------"));
    
   
  
}
//*************************************************************************************//
