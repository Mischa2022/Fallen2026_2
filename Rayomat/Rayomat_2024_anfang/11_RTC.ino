/*Auflistung Unterfunktionen, die für RTC benötigt werden
 * 
 * rtc_stellen     //Helferfunktion um RTC zu stellen. Hier gibt man die aktuelle Deutsche Zeit ein und gibt UTC=1 für Winter und UTC=2 für Sommer mit ein
 * unix_converter  //Hilfsfunktion um Unixwerte wieder in Zeit umzurechnen und auszugeben 
 * tagabgleich     //Helferfunktion um zu prüfen ob ein Wert dem aktuellen Tag entspricht: "Wurde das Medikament heute genommen?"
 * con_tag_bestimmen // wird benötigt um tagabgleich überhaupt durchzuführen
 * uhr_stellen()    //Funktion die per serielle eingabe, die uhr stellt
 */

int rtc_stellen(int Stunden,int Minuten,int Sekunden,int Tag, int Monat,long Jahr,int UTC){

//rtc.writeSqwPinMode(PCF8563_SquareWave1HZ);              
rtc.adjust(DateTime(Jahr, Monat, Tag, Stunden-UTC,Minuten,Sekunden));
}

//**************************************************************************************************************************************
int unix_converter(unsigned long t_unix_date_start,int Zeitzone){
  
  unsigned long t_unix_date;
  
  t_unix_date=t_unix_date_start+(Zeitzone*3600);

  Serial.printf("Date: %4d-%02d-%02d %02d:%02d:%02d", year(t_unix_date), month(t_unix_date), day(t_unix_date), hour(t_unix_date), minute(t_unix_date), second(t_unix_date));
  Serial.print(" ");
  
  if(Zeitzone==1){
    Serial.println("Winterzeit"); //UTC=1
  }
  if(Zeitzone==2){
    Serial.println("Sommerzeit");//UTC=2
  } 
  if(Zeitzone==0){
    Serial.println("Grundzeit");//UTC=0
  }

}
//**************************************************************************************************************************************
bool tagabgleich(int vergleich,unsigned long variable){

int tag;

if(variable<con_start_time){
  if(variable==0){tag=-1;}else{tag=0;}
  }//"0" würde bedeuten, dass am Anreisetag leere Werte gegen das Limit laufen, was nicht richtig ist

if(variable>con_start_time&&variable<=con_start_time+rest_time){
  tag=1;
  }// 1 ist richtig, damit medibuchungen theoretisch bei anreise möglich wären aber dann gegen das limit am 1 spieltag laufen

if(variable>=con_start_time+rest_time+1&&variable<con_start_time+rest_time+(1*86400)){
  tag=1;
  }
  
if(variable>=con_start_time+rest_time+1+(1*86400)&&variable<con_start_time+rest_time+(2*86400)){
  tag=2;
  }
  
if(variable>=con_start_time+rest_time+1+(2*86400)&&variable<con_start_time+rest_time+(3*86400)){
  tag=3;
  }
  
if(variable>=con_start_time+rest_time+1+(3*86400)&&variable<con_start_time+rest_time+(4*86400)){
  tag=4;
  }
  
if(variable>=con_start_time+rest_time+1+(4*86400)&&variable<con_start_time+rest_time+(5*86400)){
  tag=5;
  }

if(variable>=con_start_time+rest_time+1+(5*86400)&&variable<con_start_time+rest_time+(6*86400)){
  tag=6;
  }
if(variable>=con_start_time+rest_time+1+(anzahl_tage*86400)+1){
  tag=99;
  }
  
if(tag==vergleich){
  return true;
  }
if(tag!=vergleich){
  return false;
  }
}

//*****************************************************************************************//

int con_tag_bestimmen(unsigned long jetzt,unsigned long startzeit,unsigned long rest_anreise){

if(jetzt>=startzeit&&jetzt<=startzeit+rest_anreise){
  con_tag=0;
  }
  
if(jetzt>=startzeit+rest_anreise+1&&jetzt<startzeit+rest_anreise+(1*86400)){
  con_tag=1;
  }
  
if(jetzt>=startzeit+rest_anreise+1+(1*86400)&&jetzt<startzeit+rest_anreise+(2*86400)){
  con_tag=2;
  }
  
if(jetzt>=startzeit+rest_anreise+1+(2*86400)&&jetzt<startzeit+rest_anreise+(3*86400)){
  con_tag=3;
  }
  
if(jetzt>=startzeit+rest_anreise+1+(3*86400)&&jetzt<startzeit+rest_anreise+(4*86400)){
  con_tag=4;
  }
  
if(jetzt>=startzeit+rest_anreise+1+(4*86400)&&jetzt<startzeit+rest_anreise+(5*86400)){
  con_tag=5;
  }
  
if(jetzt>startzeit+rest_anreise+(5*86400)){
  con_tag=6;
  }

if(jetzt>startzeit+rest_anreise+(anzahl_tage*86400)+1){
  con_tag=99;
  }
                                      
//Serial.print("Contag:");
//Serial.println(con_tag);
}

//*****************************************************************************************//
bool uhr_pruefen(unsigned long abgleichwert){
unsigned long a_t_korrektur=0;
char Zeit[22];
int Stunden;
int Minuten;
int Sekunden;
int Tag;
int Monat;
int UTC2;
long Jahr;
bool fertig=false;

delay(50);
 if( abgleichwert<1640991601||abgleichwert > 1893452460){
    Serial.print("Uhr steht auf:");
    Serial.println(abgleichwert);
    Serial.println();
    Serial.println("Uhr ist nicht gestellt");
    Serial.println();
    Serial.println("Bitte gib eine Zeit in folgenden Format ein:");
    Serial.println();
    Serial.println("Stunden:Minuten:Sekunden-Tag.Monat.Jahr:UTC");
    Serial.println("SS:MM:SS-TT.MM.JJJJ:U"); 
    
while(!fertig){
  if (Serial.available() > 0) {
    
    String eingabeString = Serial.readStringUntil('\n');

    //Serial.print("Eingegeben: ");
    //Serial.println(eingabeString);
    eingabeString.toCharArray(Zeit,22);

    if(Zeit[2]!=':'||Zeit[5]!=':'||Zeit[8]!='-'||Zeit[11]!='.'||Zeit[14]!='.'||Zeit[19]!=':'){
        Serial.println("Falsche Eingabe");
        fertig= false;
        
      }
        else{  
            Stunden=((Zeit[0]-'0')*10)+(Zeit[1]-'0');
            Minuten=((Zeit[3]-'0')*10)+(Zeit[4]-'0');
            Sekunden=((Zeit[6]-'0')*10)+(Zeit[7]-'0');
            Tag=((Zeit[9]-'0')*10)+(Zeit[10]-'0');
            Monat=((Zeit[12]-'0')*10)+(Zeit[13]-'0');
            Jahr=((Zeit[15]-'0')*1000)+((Zeit[16]-'0')*100)+((Zeit[17]-'0')*10)+(Zeit[18]-'0');
            UTC2=Zeit[20]-'0';
    
         // 13:53:00-07.10.2022:2 // Proxy um Uhr neu zu stellen
         // 15:32:00-06.11.2022:1
         //
         //   Serial.printf("Date: %2d:%02d:%02d-%02d.%02d.%04d",Stunden, Minuten, Sekunden,Tag,Monat,Jahr);
         //   Serial.println(" ");
    
         rtc_stellen(Stunden,Minuten,Sekunden,Tag,Monat,Jahr,UTC2);
         delay(50);
         Serial.println("Uhr ist gestellt");
             fertig= true;
          }
        }
        else {
           fertig= false;      
        }
      }
      //zum Aktualisieren der Zeitwerte hier nochmal
      t = rtc.now();
      aktuell_time=t.unixtime();
      rest_time=86400- ((con_start_time+(UTC*UNIX_korrektur))%86400); 
      a_t_korrektur=aktuell_time+(UTC*3600);
                                                                  
      Serial.printf("Momentane Zeit: %4d-%02d-%02d %02d:%02d:%02d", year(a_t_korrektur), month(a_t_korrektur), day(a_t_korrektur), hour(a_t_korrektur), minute(a_t_korrektur), second(a_t_korrektur));
      Serial.println();
      Serial.print("Momentane Zeit Unix: ");
      Serial.println(aktuell_time); // Ohne UTC da allgemein gültige Zeitangabe
      Serial.print("Con_Start:");Serial.println(con_start_time);
      delay(50);
      con_tag_bestimmen(aktuell_time,con_start_time,rest_time);
      Serial.print("Contag:");
      Serial.println(con_tag);
 }
 else{
      //zum Aktualisieren der Zeitwerte hier nochmal
      t = rtc.now();
      aktuell_time=t.unixtime();
      rest_time=86400- ((con_start_time+(UTC*UNIX_korrektur))%86400); 
      a_t_korrektur=aktuell_time+(UTC*3600);
                                                                  
      Serial.printf("Momentane Zeit: %4d-%02d-%02d %02d:%02d:%02d", year(a_t_korrektur), month(a_t_korrektur), day(a_t_korrektur), hour(a_t_korrektur), minute(a_t_korrektur), second(a_t_korrektur));
      Serial.println();
      Serial.print("Momentane Zeit Unix: ");
      Serial.println(aktuell_time); // Ohne UTC da allgemein gültige Zeitangabe
      Serial.print("Con_Start:");Serial.println(con_start_time);
      delay(50);
      con_tag_bestimmen(aktuell_time,con_start_time,rest_time);
      Serial.print("Contag:");
      Serial.println(con_tag);
    }
}
