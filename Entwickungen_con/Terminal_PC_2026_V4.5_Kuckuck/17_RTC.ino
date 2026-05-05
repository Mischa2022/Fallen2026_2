/*Auflistung Unterfunktionen, die fuer RTC benoetigt werden
 * 
 * rtc_stellen        //2025 Helferfunktion um RTC zu stellen. Hier gibt man die aktuelle Deutsche Zeit ein und gibt UTC=1 fuer Winter und UTC=2 fuer Sommer mit ein
 * unix_converter     //2025 Hilfsfunktion um Unixwerte wieder in Zeit umzurechnen und auszugeben 
 * tagabgleich        //2025 Helferfunktion um zu pruefen ob ein Wert dem aktuellen Tag entspricht: "Wurde das Medikament heute genommen?"
 * con_tag_bestimmen  //2025 wird benoetigt um tagabgleich ueberhaupt durchzufuehren
 */

int rtc_stellen(int Stunden,int Minuten,int Sekunden,int Tag, int Monat,long Jahr,int UTC){
wdt_reset();
//rtc.writeSqwPinMode(PCF8563_SquareWave1HZ);              
rtc.adjust(DateTime(Jahr, Monat, Tag, Stunden-UTC,Minuten,Sekunden));
}

//**************************************************************************************************************************************
int unix_converter(unsigned long t_unix_date_start,int Zeitzone){
  wdt_reset();
  unsigned long t_unix_date;
  char* typen3[]{""," WZ"," SZ","Leer"};
  
  t_unix_date=t_unix_date_start+(Zeitzone*3600);
  
if (t_unix_date==0){

  myprint(typen3[3],"","",true,false,false,1,port);
  delay(50);
  }
else{

  Serial.printf(" Date: %4d-%02d-%02d %02d:%02d:%02d", year(t_unix_date), month(t_unix_date), day(t_unix_date), hour(t_unix_date), minute(t_unix_date), second(t_unix_date));


  myprint(typen3[Zeitzone],"","",true,false,false,1,port);
}
}
//**************************************************************************************************************************************
bool tagabgleich(int vergleich,unsigned long variable){
  unsigned long vergleichzeit=0;
  vergleichzeit=con_start_time+rest_time;
  int tag=1;

  if(year(vergleichzeit)<=year(variable)){
    
      if(month(vergleichzeit)<=month(variable)){
    
    //Serial.print("laufendes Spiel:");
    tag=tag+day(variable)-day(vergleichzeit);
    }
    else{
      //Serial.print("vergangenheit Spiel:");
      tag=98;
      }
    }
    else{
      //Serial.print("vergangenheit Spiel:");
      tag=98;
      }
   
  //Serial.println(tag);

  if(tag==vergleich){
  return true;

  }
 
if(tag!=vergleich){
 
  return false;
  }
}
//**************************************************************************************************************************************

int con_tag_bestimmen(unsigned long jetzt,unsigned long startzeit,unsigned long rest_anreise){ //neu
wdt_reset();
int faktor= 1;

if(jetzt<=startzeit+rest_anreise){
  return 0;  }
if(jetzt>startzeit+rest_anreise+((anzahl_tage-1)*86400)+1){ // anzahl tage ist inklusive anreise
  return 99;
  }

while(1){  
  if(jetzt>=startzeit+rest_anreise+1+((faktor-1)*86400)&&jetzt<startzeit+rest_anreise+(faktor*86400)){
    return faktor;  
    }
  else{faktor++;}
  }
                                      
}
