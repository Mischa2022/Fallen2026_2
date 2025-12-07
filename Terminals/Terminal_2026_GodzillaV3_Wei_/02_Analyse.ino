/*Auflistung Unterfunktionen, die fuer Analyse einens Dongels benoetigt werden
 * 
 * Tag_analyse()     // 2025
 */



int Tag_analyse(int target,bool ausfuehrlich){
unsigned long delta2;
unsigned long deltaray2;
unsigned long ray_writing2;
  unsigned long raywert=0;
  unsigned int key_state=0;

          
  int key=0;
//2x Prozess

  if(ausfuehrlich==0){  

     myprint("--------------------------------------------","","",true,true,false,1,port);
    myprint("Analyse gestartet","","",true,true,ausfuehrlich,1,port);
  }
  
  if(ausfuehrlich==1){  

    myprint("--------------------------------------------","","",true,true,false,1,port);
    myprint("Ausfuehrliche Analyse gestartet","","",true,true,ausfuehrlich,1,port);
  }

  //Tag_analyse steps 1 *********************************************************************//
  if(error==0){
    newkey();
    prozess();

//Tag_analyse steps 2 *********************************************************************//       
    if(key==0){ 

      for(int x=0;x<=15;x++){
    
        key__searchA(x);
        key=key+ergebnis;
        feedback=0;
        ergebnis=0;
        delay(20);
    
        key__searchB(x);
        key=key+ergebnis;
        feedback=0;
        ergebnis=0;
        delay(20); 
      }
 
      if(key==32){ 
        
        key_state=0;
        error=0;
      } 
      else {
        Serial.print(F("Key soll 32:"));Serial.println(key);
        key_state=1;
        error=1;
      }
    }

//Tag_analyse steps 3 *********************************************************************//

    if(key_state==0){

      Check_rfid_tag(target,ausfuehrlich); //Tagwerte lesen und zwischenspeichern

   
      if(error==0&&target==1||error==0&&target==10){   //werte interpretieren und Dongelalter bestimmen  ausgabe aber nur, wenn die Spielerdaten oder der gesamte dongel abgefragt werden

        if(Con_Start_read==0){ 
      //  if(Con_Start_read==0&&Con_Start_read2019==0){ 
          msg1="RFID ist leer      ";
 
          raywert=0;  
        }
        
        if(Con_Start_read==0&&Ray_value_extern_read!=0){ 
          msg1="vielleicht fuer Plot";
  
          raywert=Ray_value_extern_read/1000;  
        }

        if(Con_Start_read!=con_start_time&&Ray_value_extern_read!=0){ 

          msg1="kein Checkin     " ;
 
          raywert=Ray_value_extern_read/1000;
        }
        if(Con_Start_read==con_start_time&&Ray_value_extern_read!=0){ 

            msg1=conname;
          
 
          raywert=Ray_value_extern_read/1000;
        }


        
// fuer aktuell berechnete werte des raywerts
if(raywert!=0){
  prozess();
  msg4="Ray:";
   
        
        if(aktuell_time<=con_start_time){
   
          myprint("zu frueh fuer berechnung","","",true,true,false,1,port);
          ray_writing2=(Ray_value_extern_read+0)-0;
        }
        else if(aktuell_time>con_start_time+rest_time+1+((anzahl_tage-1)*86400)){
     
          myprint("viel zu spaet","","",true,true,false,1,port);
          ray_writing2=500000;
          delta2=0;
        }
        else if(Con_Start_read!=con_start_time){
            myprint("keine Berechnung moeglich","","",true,true,false,1,port);
          ray_writing2=(Ray_value_extern_read+(0))-0;
          delta2=0;
        }
        else{ //im Spiel
          //Serial.println("Im Spiel2");
        if(LifeCleaner_effekt_read>=aktuell_time){
        
                      delta2=0;
               
                  }else {
                        if(Last_Booking_read>=aktuell_time){
                      //if(aktuell_time-Last_Booking_read<0){
                        delta2=0;
                      }
                        else{
                          if(Last_Booking_read<LifeCleaner_effekt_read){
                            delta2=aktuell_time-LifeCleaner_effekt_read;
             
                          }
                          else{
                          delta2=aktuell_time-Last_Booking_read;
             
                          }
                         }

                     
                   }
                    //Serial.print("Delta2A:");Serial.println(delta2);
              deltaray2=(tagesdosis*delta2/86400)*1000;
              myprint("Rayaufschlag:","",deltaray2,true,true,false,1,port);
              

                if(Ray_value_extern_read+deltaray2<minimum_ray_writing){
                  ray_writing2=minimum_ray_writing;
                }  
                else if(ray_writing2>maximum_ray_writing){
                  ray_writing2=maximum_ray_writing;
                }
                else{
              ray_writing2=(Ray_value_extern_read+deltaray2)-0;
                }
        }

             
         if(Con_Start_read==0&&Ray_value_extern_read!=0){ 
          ray_writing2=Ray_value_extern_read;  
        }     
        //myprint("Ray berechnet:","",ray_writing2,true,true,false,1,port);  
        Serial.print(F("Ray berechnet:"));Serial.println((float)ray_writing2/1000);         
        ray_writing2=ray_writing2/1000;
        if(ray_writing2==0){                    msg5="kein Ray    ";}
        if(ray_writing2>0&&ray_writing2<=50){   msg5="light Green ";}  
        if(ray_writing2>50&&ray_writing2<=100){ msg5="Green       ";}  
        if(ray_writing2>100&&ray_writing2<=150){msg5="dark Green  ";}  
        if(ray_writing2>150&&ray_writing2<=200){msg5="light Yellow";}
        if(ray_writing2>200&&ray_writing2<=250){msg5="Yellow      ";}
        if(ray_writing2>250&&ray_writing2<=300){msg5="dark Yellow ";}
        if(ray_writing2>300&&ray_writing2<=350){msg5="light Red   ";}
        if(ray_writing2>350&&ray_writing2<=400){msg5="Red         ";}
        if(ray_writing2>400&&ray_writing2<=450){msg5="dark Red    ";}
        if(ray_writing2>450)                   {msg5="kein Spiel  ";}
      }  

      }
    }
      msg2="";
      msg3="";
  }

//Tag_analyse steps 4 *********************************************************************//
  if(error!=0||key_state==1){ // wenn Check_rfid_tag einen Fehler auweist direkt weiter zum Ende

   
    msg2="";
    msg3="";
    msg1="RFID abgebrochen";
 if(checkin_reason!=2){
    buzzer_play( 8,100);
    }
  }

  return;
}
//*****************************************************************************************//
