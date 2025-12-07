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
      Serial.print("Contag:");Serial.println(faktor);                                
}
