/*Auflistung Unterfunktionen, die fuer Checkin einens Dongels benoetigt werden
 * 
 * checkin     //2025 Helferfunktion um einen Spieler_Dongel ein zu checken
 */

int checkin(unsigned long sorte,bool bonus,int Bereich,bool Grund){ // sorte steht fuer Mutant,Mensch usw, bonus==1 bucht direkt zwei Nanoclean

Con_End=(con_start_time+rest_time+((anzahl_tage-1)*86400));


if(Bereich==0){
start_raywert=random(startwert_min,startwert_max)*1000UL;       //Startwert fuer Checkin eines neuen Menschen Dongels
start_raywert_m=random(startwert_min_m,startwert_max_m)*1000UL; //Startwert fuer Checkin eines neuen Mutanten Dongels
}
if(Bereich==1){
start_raywert=random(startwert_min,150)*1000UL;       //Startwert fuer Checkin eines neuen Menschen Dongels
start_raywert_m=random(startwert_min_m,150)*1000UL; //Startwert fuer Checkin eines neuen Mutanten Dongels
}
if(Bereich==2){
start_raywert=random(150,300)*1000UL;       //Startwert fuer Checkin eines neuen Menschen Dongels
start_raywert_m=random(150,300)*1000UL; //Startwert fuer Checkin eines neuen Mutanten Dongels
}
if(Bereich==3){
start_raywert=random(300,450)*1000UL;       //Startwert fuer Checkin eines neuen Menschen Dongels
start_raywert_m=random(300,450)*1000UL;  //Startwert fuer Checkin eines neuen Mutanten Dongels
}



//2xprozess              
t = rtc.now();      
aktuell_time=t.unixtime();

  
  unsigned long booking_time=0;
  unsigned long id_value=0;
  unsigned long delta,delta2=0;
  unsigned long old_rest_time;
  unsigned int key_state=1;
  int key=0;
  int steps=0;
  int keyset[32];
  int old_block[47]{
    1,2,4,5,6,8,9,10,12,13,
    14,16,17,18,20,21,22,24,25,26,
    28,29,30,32,33,34,36,37,38,40,
    41,42,44,45,46,48,49,50,52,53,
    54,56,57,58,60,61,62
  };
  char* typ[]{"Checkin Mensch gestartet"};
  //char* typ[]{"Checkin Mensch gestartet","Checkin Mensch mt sold gestartet","Checkin Mutant gestartet"};
  int auswahl=0;

if(Grund==0){
  
booking_time=con_start_time+rest_time;

}

if(Grund==1){
//variablen um einen spaeteren checkin nicht auf start_time festzulegen sondern aktuell zu halten
  if(aktuell_time>con_start_time){
    booking_time=aktuell_time;
  }
}

if(aktuell_time<con_start_time){
  booking_time=con_start_time+rest_time;
}


 
//Ausgabe Terminal was gestartet wird********************************************************
    if(sorte==100&&bonus==0){        
      auswahl=0; 
      }
    if(sorte==100&&bonus==1){        
      auswahl=1; 
      }
    if(sorte==360){       
      auswahl=2; 
      }
      myprint(typ[auswahl],"","",true,true,false,1,port);        
      
      newkey();

//Key´s werden bestimmt*********************************************************************
  
  if(key==0){ 
  
    for(int x=0;x<=15;x++){
      
      key__searchA(x);
      keyset[x]=key_used;
      key=key+ergebnis;
      feedback=0;
      ergebnis=0;
      delay(10);
      
      key__searchB(x);
      keyset[x+16]=key_used;
      key=key+ergebnis;
      feedback=0;
      ergebnis=0;
      delay(50); 
    }
    
    if(key==32){ 
      key_state=0;
      error=0;
    } else {
      key_state=1;
      error=1;
    }
  }

//Auswerten und interpretieren der Dongeldaten**********************************************
prozess();
 if(steps==0&&key_state==0){

 myprint("Bisherige Werte","","",true,true,false,1,port);  
      Check_rfid_tag(1,0);
      raywert_gelesen2=Ray_value_extern_read/1000;

     old_rest_time=86400-(Con_Start_read%86400);
      
   if(error==0){   //werte interpretieren und Dongelalter bestimmen
    if(Con_Start_read==0){

        msg6="neuer Checkin";
        raywert_gelesen=0;  
        checkin_reason=1;
      }
    if(Con_Start_read==con_start_time&&Ray_value_extern_read!=0){
      
        raywert_gelesen=Ray_value_extern_read;
       msg6="erneuter Checkin";
       checkin_reason=2;
       error=1;
        }
      else if(Con_Start_read!=0&&Ray_value_extern_read!=0){ 
        
        if(Con_Start_read!=0&&Ray_value_extern_read>maximum_ray_writing){ //Zum Abfangen von falsch gesetzten Raywerten aus dem Jahr 2022
        raywert_gelesen=start_raywert+50000;
        msg6=" Alter TAG HIGH";
        }
        if(Con_Start_read!=0&&Ray_value_extern_read<minimum_ray_writing){ //Zum Abfangen von falsch gesetzten Raywerten aus dem Jahr 2022
        raywert_gelesen=minimum_ray_writing;
        msg6=" Alter TAG LOW";
        }
        
        if(Con_Start_read!=con_start_time&&Con_Start_read!=0&&Ray_value_extern_read!=0){
         
          myprint("--------------------------------------------","","",true,true,false,1,port);

          //einbauen Lifecleanereffekt
          if(Last_Booking_read<LifeCleaner_effekt_read){
            Last_Booking_read=LifeCleaner_effekt_read;
            myprint("Hat Lifecleaner genommen!","","",true,true,false,1,port);
           
          }
 
          if(Last_Booking_read>(Con_Start_read+old_rest_time+(172800))){  //wer spaetestens am zwei Tag mitgemacht hat
            msg6="Am Strahlenspiel teilgenommen";
            }
          
          else if(Last_Booking_read<(Con_Start_read+old_rest_time+(259200))){
          msg6="Schwarzes Schaf"; //wer sich drei tage nicht geruehrt hat
          
          }

 /////////////////////////////////////////////////////   Aufschlag muss ueberarbeitet werden, con 2024 war 3 aktive tage    
if(Con_End_read==0){
          delta=((Con_Start_read+old_rest_time+(3*86400))-Last_Booking_read); 
          Serial.println(F("Hochgerechnet"));
          delay(50);
      }
       else{    delta=(Con_End_read-Last_Booking_read);
                Serial.println(F("Berechnet durch Con_End"));
                delay(50);
       }     
                  
          delta2=delta*tagesdosis*10/864;
          
 /////////////////////////////////////////////// 
   

          myprint("statischer Raywert:","",Ray_value_extern_read,true,true,false,1,port);
          myprint("Aufschlag Ray:","",delta2,true,true,false,1,port);
          myprint("--------------------------------------------","","",true,true,false,1,port);
          if(Ray_value_extern_read+delta2>maximum_ray_writing){
          raywert_gelesen=maximum_ray_writing;
          }
          else if(Ray_value_extern_read+delta2<minimum_ray_writing){
            raywert_gelesen=minimum_ray_writing;
          }
          else{
        raywert_gelesen=Ray_value_extern_read+delta2;
          }
        }
        
         if(Con_Start_read==con_start_time&&Ray_value_extern_read!=0){
      
        raywert_gelesen=Ray_value_extern_read;
       
       
        }
        checkin_reason=4;
      }

  }    
   if(error!=0){
   checkin_reason=0; //gibt es bei Check_rfid_tag einen Fehler, unterbrech hier und geh zum ende
   }   
 }
//Setzen neuer Keys ***********************************************************************

  if(error==0){ 
      if(steps==0){
     //   Serial.write("Start");
        for(int z=0;z<=15;z++){
       /*   Serial.write("Sector");
          Serial.print(z);
          Serial.write(" | ");
          Serial.write("KeyA:");
          Serial.print(keyset[z]);
          Serial.write(" | ");
          Serial.write("KeyB:");
          Serial.println(keyset[z+16]);*/
          RFID_Set_Keys_int(keyset[z],keyset[z+16], knownKeys[0], knownKeys[last_key], z);
          delay(10);
        }
        steps=1;
      }
    
//Reseten alter Werte *********************************************************************
// das verursacht bei abbruch einen leeren Dongel von den Werten her.                              
      if(steps==1&&error==0&&key_state==0){  
      
        for(int r=0;r<=46;r++){
          writing(knownKeys[last_key],old_block[r],0,0);
          delay(10); 
        }
      } 
    }

//Schreiben neuer Werte********************************************************************
prozess();

    switch(checkin_reason){  
      
      case 0:
      
        msg2="nicht geschrieben";
        msg3="";
        bonus=false;
      break;        

          case 2://kein schreiben neuer Daten*************************************************
     Serial.println(F("bereits eingecheckt"));
      
        msg2="war eingecheckt";
        msg3="";
        bonus=false;
      break;  
      
      case 1: //Schreiben ganz neuer Daten*************************************************
     Serial.println(F("Neuer Dongel"));
      //Con_Daten
        
        writing(knownKeys[last_key],Admin1_block,con_start_time,booking_time);
        writing(knownKeys[last_key],Admin2_block,0,sorte);       //archtype    

            writing(knownKeys[last_key],Admin3_block ,Con_End,start_raywert);      //raywert fuer Menschen neu schreiben  
            raywert_gelesen=start_raywert;
            
        
        

      break;

     case 4: //Umschreiben von aera Sascha/Frank *************************************************
     Serial.println(F("Umschreiben Dongel"));
      //Con_Daten
        
        writing(knownKeys[last_key],Admin1_block,con_start_time,booking_time);
        writing(knownKeys[last_key],Admin2_block,0,sorte);       //archtype  

        
        
        if(raywert_gelesen==0){  //kein Startwert hinterlegt, dann hier neuschreiben
          
           writing(knownKeys[last_key],Admin3_block ,Con_End,start_raywert);      //raywert fuer Menschen neu schreiben  
          }
          
         else{                
          writing(knownKeys[last_key],Admin3_block ,Con_End,raywert_gelesen);  //gelesenen raywert_gelesen beibehalten 
             }
        
      break;
    }

    Bereich=0;
    
}

 

//*****************************************************************************************//
