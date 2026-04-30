
void initialisierung2() {
  char read_Char4;  //konfig import sd
  Serial2.println("y");
    Serial.println( F("Initialisierung"));
   Serial.println(  Terminalname);
//SD-Check 
  
  if (!SD.begin(chipSelect)) {
    Serial.println(F("SD-Karte nicht ok"));

    
    while (1);
  }

 Serial.println(F("SD-Karte ok"));

     
   if (SD.exists("konfig.txt")) {
  
       File dataFile = SD.open("konfig.txt", FILE_READ);

        if (dataFile) {
        while (dataFile.available()) {
              read_Char4 = (char)dataFile.read();
        
          if (read_Char4 != '\n') {
             neu_konfig += read_Char4;
             
            }
            
          else{
      
            dataFile.close();
            cut(neu_konfig, neu, '*');
            delay(100);
            read_konfig_out_of_string(neu);
            }
        }
    
        } 
      }
      else{
       

          cut(basis_konfig, basis2, '*');
          /* for (int y = 0; y < 25; y++) {
              Serial.print(y);Serial.print(F(" ");
              Serial.print(bereich_name[y]);
              Serial.println( basis[y]); 
              delay(10);
          }*/
          read_konfig_out_of_string(basis2);
      }
//Reader-Check
mfrc522.PCD_DumpVersionToSerial();

t = rtc.now();      
aktuell_time=t.unixtime();
rest_time=86400- ((con_start_time+(UTC*UNIX_korrektur))%86400); 
  Serial.println(aktuell_time);
  
//Uhrcheck
  if( aktuell_time<(con_start_time-432000)||aktuell_time > 1893452460){
  Serial.print(F("Con_start_time:"));Serial.println(con_start_time);
  myprint("Uhr ist verstellt","","",true,true,false,1,0);
  while (1);
 }
 Serial.println(F("Uhr ok"));  

//______________________________________________________

   



//uhr_pruefen(aktuell_time);
unsigned long a_t_korrektur=0;
      

      a_t_korrektur=aktuell_time+(UTC*3600);
                                                                  
      Serial.printf("Momentane Zeit: %4d-%02d-%02d %02d:%02d:%02d", year(a_t_korrektur), month(a_t_korrektur), day(a_t_korrektur), hour(a_t_korrektur), minute(a_t_korrektur), second(a_t_korrektur));
      Serial.write('\n');delay(50);
      Serial.write("Momentane Zeit Unix: ");
      Serial.print(aktuell_time); // Ohne UTC da allgemein gültige Zeitangabe
      Serial.write('\n');delay(50);
      Serial.write("Con_Start:");
      Serial.print(con_start_time);
      Serial.write('\n');delay(50);
      
   if(aktuell_time>con_start_time+rest_time){
      Serial.write("vergangene Sekunden ab Anreise:");
      Serial.print(aktuell_time-(con_start_time+rest_time));
      Serial.write(" | vergangene Stunden ab Anreise:");
      Serial.println((aktuell_time-(con_start_time+rest_time))/3600);
      
       }
       else{
        Serial.println("Vor Constart");
      }
      
      delay(50);
      con_tag=con_tag_bestimmen(aktuell_time,con_start_time,rest_time);
      Serial.write("Contag:");
      Serial.println(con_tag);
myprint("----------------------------------------------------------------------------------------","","",true,true,false,1,port);
myprint("----------------------------------------------------------------------------------------","","",true,true,false,1,port);  
        

      Serial.println();  
      Serial.println(F("Initialisierung fertig"));
      Serial.println();

}

//*****************************************************************************************//

void lichtertest(){

digitalWrite(relaisPin[0],!geschaltet);
delay(500);
digitalWrite(relaisPin[1],!geschaltet);
delay(500);
digitalWrite(relaisPin[2],!geschaltet);
delay(500);
digitalWrite(relaisPin[3],!geschaltet);
delay(500);
pixels2.clear();
pixels2.show();  
pixels1.clear();
pixels1.show();  

digitalWrite(relaisPin[0],geschaltet);
delay(500);
digitalWrite(relaisPin[1],geschaltet);
delay(500);
digitalWrite(relaisPin[2],geschaltet);
delay(500);
digitalWrite(relaisPin[3],geschaltet);


buzzer_play( 5,300);
Serial2.println("y");

for (int x=180;x>0;x--){
myservo_wippe.write(x);
delay(5);
}

for (int x=160;x>15;x--){
myservo_anzeige.write(x);
delay(10);
}

      Serial.println();  
      Serial.println(F("Lichttest fertig"));
      Serial.println();

  }



//*****************************************************************************************//
