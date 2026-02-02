/*Auflistung Unterfunktionen, die für Check einens Dongels benötigt werden
 * 
 * Check_rfid_tag     //Helferfunktion um einen Spieler_Dongel auf gespeicherte Werte zu prüfen
 */

int Check_rfid_tag(int variante,bool ausfuehrlich){



/*varianten
 * 1 nur spieler infos ohne medi
 */
 
// Lesen der zufüllenden Werte

//Con und Spielerrelevante Daten
//*************************************************************************************//
if(variante==1){

error=error+rfid_reading(knownKeys[0],Admin1_block); //58

  Con_Start_read=ergebnisA;
  Last_Booking_read=ergebnisB; 
  //Last_Booking_read=1661940000;

  ergebnisA=0;ergebnisB=0;    
    
error=error+rfid_reading(knownKeys[0],Admin2_block); //57
 // archtype_read=ergebnisB;
  LifeCleaner_effekt_read=ergebnisA; 
//  LifeCleaner_effekt_read=aktuell_time+(24*3600);
  ergebnisA=0;ergebnisB=0;
    
error=error+rfid_reading(knownKeys[0],Ray_block); //56
  Ray_value_intern_read=ergebnisA;
  Ray_value_extern_read=ergebnisB; 

  ergebnisA=0;ergebnisB=0;  
}


//Ausgabe der gelesenen Werte als UNIX-werte aber nur wenn error==0
//*************************************************************************************//
  if(error==0&&ausfuehrlich==0){
  if(variante==1){
   Serial.print("aktuell_time");Serial.println(aktuell_time);
    Serial.print("Con_Start_read:");//wird im folgenden Konvertiert
    Serial.println(Con_Start_read); //wird im folgenden Konvertiert
  
   Serial.print("Letzte Buchung:"); //für Godzilla eigentlich "Last_Booking_read:"
   Serial.println(Last_Booking_read);

   Serial.print("LifeCleanereffekt:");//für Godzilla eigentlich "LifeCleaner effekt_read:"
   Serial.println(LifeCleaner_effekt_read);
   // Serial.print("Ray_value_intern_read:"); //wird momentan nicht gebraucht
   // Serial.println(Ray_value_intern_read);  //wird momentan nicht gebraucht
   
    Serial.print("Raywert:");//für Godzilla eigentlich "Ray_value_extern_read:"
    Serial.println(Ray_value_extern_read);
    
raywert=Ray_value_extern_read/1000; 

    }
   
  }
}
//*************************************************************************************//
