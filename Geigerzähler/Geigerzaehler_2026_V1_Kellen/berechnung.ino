/*Auflistung Unterfunktionen, die von anderen Funktionen benötigt werden
 * 
 * new_ray() //wertberechnung
 */

int new_ray(){

unsigned long rest_time;  
int tagesdosis=48;
int UTC=1;
int anzahl_tage_vergangen=0;
unsigned int anzahl_tage_maximal=4; // Geigerzähler arbeiten maximal diese Anzahl an Tagen weiter mit Spielerdongel
unsigned long max_play=0;
unsigned long delta=0;
long puffer=0;
Serial.println(F("BERECHNUNG"));
Serial.print(F("Raywert start:"));Serial.println(raywert);

//if(Last_Booking_read>aktuell_time){Last_Booking_read=aktuell_time;}
 
if(LifeCleaner_effekt_read==0){
  LC_aktiv=0;
}
else if(LifeCleaner_effekt_read<aktuell_time){
  LC_aktiv=0;
}
else if(LifeCleaner_effekt_read>aktuell_time){
  LC_aktiv=1;
}
  
if(Con_Start_read!=0&&raywert!=0){
  Serial.println(F("Kartentyp: Spieler"));

rest_time=86400- ((Con_Start_read+(UTC*3600))%86400); 
    Serial.print(F("Rest:"));Serial.println(rest_time);

max_play=Con_Start_read+rest_time+1+(86400*anzahl_tage_maximal);
  Serial.print(F("max_play:"));Serial.println(max_play);   

  
  //Spiel seid 4 tagen vorbei 
    if(max_play<aktuell_time){
      delta=((Con_Start_read+rest_time+(anzahl_tage_maximal*86400))-Last_Booking_read)*tagesdosis/86400;
     // delta=delta/1000;
      
          Serial.print(F("delta1:"));Serial.println(delta);
          
        if(raywert+delta<=450){
          raywert2=raywert+delta;
          
          Serial.print(F("Ray zu spät:"));Serial.println(raywert2);
          }
          else{
            raywert2=450;
            Serial.print(F("Ray zu spät und über skala:"));Serial.println(raywert2);
            }
          }
    //Spiel noch nicht begonnen
      if(aktuell_time < (Con_Start_read+rest_time+1)){
        raywert2=raywert;
        Serial.print(F("Ray zufrüh:"));Serial.println(raywert2);
      }
    // im Spiel ohne LC
     if(max_play>=aktuell_time&&LC_aktiv==0&&aktuell_time > (Con_Start_read+rest_time+1)){
      delta=(aktuell_time-Last_Booking_read)*tagesdosis/86400;
     // delta=delta/1000;
     
          Serial.print(F("delta2:"));Serial.println(delta);
          raywert=raywert+delta;
          
        if(raywert<=450){
      raywert2=raywert;
      Serial.print(F("Ray im Spiel:"));Serial.println(raywert2);
      }
      else{
        raywert2=450;
        Serial.print(F("Ray im Spiel zu groß:"));Serial.println(raywert2);
        }
    }
   
         // im Spiel mit LC
     if(max_play>=aktuell_time&&LC_aktiv==1&&aktuell_time > (Con_Start_read+rest_time+1)){
      delta=0;
          Serial.print(F("delta:"));Serial.println(delta);
            raywert=raywert+delta;
            
        if(raywert<=450){
      raywert2=raywert;
      Serial.print(F("Ray im Spiel mit LC:"));Serial.println(raywert2);
      }
      else{
        raywert2=450;
        Serial.print(F("Ray im Spiel zu groß mit LC:"));Serial.println(raywert2);
        }
    }
}
if(Con_Start_read==0&&raywert==0){

  
Serial.println(F("Kartentyp: Leer"));
  
  raywert2=0;
}

if(Con_Start_read==0&&raywert!=0){

  Serial.println(F("Kartentyp: Plot"));
 
          if(raywert<=450){
      raywert2=raywert;
      }
   else{
        raywert2=450;
   }
}
Serial.println(F("BERECHNUNG END"));
Serial.println(F("--------------------------------"));
}
