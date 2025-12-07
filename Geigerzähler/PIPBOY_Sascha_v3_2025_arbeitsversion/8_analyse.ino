 /*Auflistung Unterfunktionen, die für Check einens Dongels benötigt werden
 * 
 * Check_rfid_tag     //Helferfunktion um einen Spieler_Dongel auf gespeicherte Werte zu prüfen
 */

int Check_rfid_tag_pipboy(int variante,bool ausfuehrlich){

//Serial.println("Daten Grabber");
 
// Lesen der zufüllenden Werte

//Con und Spielerrelevante Daten
//*************************************************************************************//


error=error+rfid_reading(knownKeys[0],Admin1_block); //58
//Serial.print("Error Admin1:");Serial.println(error);
  Con_Start_read=ergebnisA;
  Last_Booking_read=ergebnisB; 

  ergebnisA=0;ergebnisB=0;    
    
error=error+rfid_reading(knownKeys[0],Admin2_block); //57
//Serial.print("Error Admin2:");Serial.println(error);
  archtype_read=ergebnisB;
  LifeCleaner_effekt_read=ergebnisA; 

  ergebnisA=0;ergebnisB=0;
    
error=error+rfid_reading(knownKeys[0],Admin3_block); //56
//Serial.print("Error Admin3:");Serial.println(error);
  Con_End_read=ergebnisA;
  Ray_value_extern_read=ergebnisB; 
  
  ergebnisA=0;ergebnisB=0;  

//Medirechte
//*************************************************************************************//
if(variante==1||variante==10){
  error=error+rfid_reading(knownKeys[0],1);

  rights=ergebnisB;

  ergebnisA=0;ergebnisB=0;
}

//Ausgabe der gelesenen Werte als UNIX-werte aber nur wenn error==0
//*************************************************************************************//

   
    Serial.print("Con_Start_read:");//wird im folgenden Konvertiert
    Serial.print(Con_Start_read); //wird im folgenden Konvertiert
    Serial.print(" ");
    unix_converter(Con_Start_read,0);
    Serial.println();
    Serial.print("Con_End_read:");//wird im folgenden Konvertiert
    Serial.print(Con_End_read); //wird im folgenden Konvertiert
    Serial.print(" ");
    unix_converter(Con_End_read,0);
    Serial.println();
  
   Serial.print("Letzte Buchung:"); //für Godzilla eigentlich "Last_Booking_read:"
   Serial.print(Last_Booking_read);
   Serial.print(" ");
   unix_converter(Last_Booking_read,0);
   Serial.println();
   
    Serial.print("archtype_read:");//wird im folgenden Konvertiert
    //Serial.println(archtype_read); //wird im folgenden Konvertiert
    Serial.print("Archetyp:");
    if(archtype_read==100){
      Serial.println("Mensch");
      }//für Godzilla
      
    if(archtype_read==360){
      Serial.println("Mutant");
      }//für Godzilla
      
    if(archtype_read==250){
     Serial.println("Bunkerbewohner");
      }//für Godzilla 
      
    if(archtype_read==0){
      Serial.println("Kein Typus");
    }//für Godzilla für Plots
    
   Serial.print("LifeCleanereffekt:");//für Godzilla eigentlich "LifeCleaner effekt_read:"
   Serial.println(LifeCleaner_effekt_read);
   // Serial.print("Ray_value_intern_read:"); //wird momentan nicht gebraucht
   // Serial.println(Ray_value_intern_read);  //wird momentan nicht gebraucht
   
    Serial.print("Raywert:");//für Godzilla eigentlich "Ray_value_extern_read:"
    Serial.println(Ray_value_extern_read);
raywert=Ray_value_extern_read/1000; 
//Serial.print("Roywert:");Serial.println(raywert);

if(raywert>450){
  Serial.println("Wert ist verkehrt!");
  
  Display.clearDisplay();   
  Display.setTextSize(1);
  Display.setTextColor(WHITE);
  Display.setCursor( 10, 10);
  Display.print("Wert ist verkehrt!");
  Display.display();
  delay(1800);
  
  }
delay(200);
Serial.println("--------------------------------");
    
   
  
}
//*************************************************************************************//
