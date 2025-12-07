/*Auflistung Unterfunktionen, die fuer Medikamentenbuchungen benoetigt werden
 * 
 * medibuchung     // 2025
 */
 
int medibuchung_pipboy(unsigned long medikament){
//char* Medi[] {"Update","Nanoclean","Dekon","Lifecleaner","Bloodclean","Cleanray","Drawback"};
//char* grund[] {"nein","zu frueh","zu spaet"};
unsigned long Bonus;
unsigned long delta;
unsigned long deltaray;
unsigned long time_writing;

int ziel_block1,ziel_block2,ziel_block3,ziel_block4,ziel_block5,ziel_block6,ziel_block7;
unsigned long block_writing[14];
int limit_tag=0;
int limit_con=0;
int used_tag=0;
int used_con=0;

Con_End=(con_start_time+rest_time+((anzahl_tage-1)*86400));
//Serial.print("Grund: ");Serial.println(medikament);
//welches Medikament soll gebucht werden und welche Spezifikationen hat es
            
            // update
            if (medikament==1){
              Bonus=0;
              Check_rfid_tag(medikament,0);
              limit_tag= 100; 
              limit_con= 100;
              used_tag = 0;
              used_con = 0;
              buchungsgrund="Update     ";
            }

            //Nanoclean
            if (medikament==2){
              Check_rfid_tag(1,0);
              NanoClean=random(Nanoclean_min_effekt,Nanoclean_max_effekt)*1000UL;
              Bonus=NanoClean;
              Check_rfid_tag(medikament,0);
              limit_tag= Nano_per_day;   
              limit_con= Nano_per_con; 
              used_tag = Nanocounter_thisday;
              used_con = Nanocounter_allday;
              buchungsgrund="Nanoclean  ";
              
              ziel_block1=54;
              ziel_block2=53;
              ziel_block3=52;
              ziel_block4=50;
              
              for(int x=0;x<8;x++){
                block_writing[x]=NanoClean_read[x];
              }
            }

            //Dekon
            if (medikament==3){
              Check_rfid_tag(1,0);
              Dekon = random(Dekon_min_effekt,Dekon_max_effekt)*1000UL;    
              Bonus=Dekon;
              Check_rfid_tag(medikament,0);
              limit_tag= Dekon_per_day; 
              limit_con= Dekon_per_con; 
              used_tag = Dekoncounter_thisday;
              used_con = Dekoncounter_allday;
              buchungsgrund="Dekon      ";
              
              ziel_block1=49;
              ziel_block2=48;
              ziel_block3=46;
              ziel_block4=45;
              ziel_block5=44;
              ziel_block6=42;
              ziel_block7=41;
              
              for(int x=0;x<14;x++){
                block_writing[x]=Dekon_read[x];
              }
              
            }

            //Lifecleaner
            if (medikament==4){
              Check_rfid_tag(1,0);
              LifeCleaner=random(Lifecleaner_min_effekt,Lifecleaner_max_effekt)*1000UL;   //weil keinen Effekt auf Ray-Wert ist aber als Variable moeglich
              Bonus=LifeCleaner;
            
              Check_rfid_tag(medikament,0);
              limit_tag= LifeCleaner_per_day;    
              limit_con= Life_per_con;  
              used_tag = Lifecounter_thisday;
              used_con = Lifecounter_allday;
              buchungsgrund="Lifecleaner";

              ziel_block1=37;
              ziel_block2=36;
              ziel_block3=34;
              ziel_block4=33;
              ziel_block5=32;
              
              for(int x=0;x<10;x++){
                block_writing[x]=LifeCleaner_read[x];
              }
            }

            //Bloodclean
            if (medikament==5){
              Check_rfid_tag(1,0);
              BloodClean=random(Bloodclean_min_effekt,Bloodclean_max_effekt)*1000UL; 
              Bonus=BloodClean;
              Check_rfid_tag(medikament,0);
              limit_tag= Blood_per_day; 
              limit_con= Blood_per_con;   
              used_tag = Bloodcounter_thisday;
              used_con = Bloodcounter_allday;
              buchungsgrund="Blutwaesche ";

              ziel_block1=30;
              ziel_block2=29;
              ziel_block3=28;
              ziel_block4=26;
              ziel_block5=25;
              
              for(int x=0;x<10;x++){
                block_writing[x]=BloodClean_read[x];
              }
            }

            //Cleanray
            if (medikament==6){
              Check_rfid_tag(1,0);
              Cleanray=random(Cleanray_min_effekt,Cleanray_max_effekt)*1000UL;  
              Bonus=Cleanray;
              Check_rfid_tag(medikament,0);
              limit_tag= Clean_per_day; 
              limit_con= Clean_per_con;
              used_tag = Cleancounter_thisday;
              used_con = Cleancounter_allday;
              buchungsgrund="Cleanray   ";

              ziel_block1=18;
              ziel_block2=17;
              ziel_block3=16;
              ziel_block4=14;
              
              for(int x=0;x<8;x++){
                block_writing[x]=Cleanray_read[x];
              }
            }

            //Drawback
            if(medikament==7){
              Check_rfid_tag(1,0);
              Drawback=random(Drawback_min_effekt,Drawback_max_effekt)*1000UL;
              Bonus=Drawback;
              limit_tag= 100; 
              limit_con= 100;
              used_tag = 0;
              used_con = 0;
              buchungsgrund="Drawback   ";
              }


//Rechnen und Freigaben

      t = rtc.now();
      aktuell_time=t.unixtime();
      
      //myprint("------------------------------------------------","","",true,true,false,1,0); 
      
if(Last_Booking_read> aktuell_time){Last_Booking_read=aktuell_time;}
//Falls ein Geraet durchgaengig laeuft
con_tag=con_tag_bestimmen(aktuell_time,con_start_time,rest_time);
     
      
//1. Richtiges Con und nach Anreise

//Serial.write("Richtiges Con:");
myprint("Richtiges Con:","","",true,false,false,1,0);    
       
//if(Con_Start_read==con_start_time&&con_tag>=erster_buchungstag&&con_tag<=anzahl_tage){
 if(Con_Start_read==con_start_time&&con_tag>=erster_buchungstag&&con_tag<anzahl_tage){

 myprint("ja","","",true,true,false,1,0);           
//2. Einnahme Medis erlaubt          
      
     if(used_tag<limit_tag&&used_con<limit_con){ // muss kleiner sein, damit eine weitere buchung erlaubt ist
      
        //ja   
            
               //myprint("------------------------------------------------","","",true,true,false,1,0);   
            
               myprint("Aktuelle Zeit:","",aktuell_time,true,true,false,1,0);   

              
               myprint("Letzte Buchung:","",Last_Booking_read,true,true,false,1,0);   
        
              
//3.Lifecleanereffekt aktiv?            
///////////////////////////////////////////////////////////////////////////////////////
                  // myprint("------------------------------------------------","","",true,true,false,1,0);   

                  if(LifeCleaner_effekt_read>=aktuell_time){

                      myprint("Lifecleanereffekt aktiv: ja","","",true,true,false,1,0); 
                      delta=0;
                     
                      time_writing=aktuell_time; //damit laeuft bei jedem versuch auch last_booking hoch, halte ich fuer sinnvoll
                      if(medikament==7){
                        Bonus=0;
                      }
                  }else {

                      myprint("Lifecleanereffekt aktiv: nein","","",true,true,false,1,0); 
                      if(aktuell_time-Last_Booking_read<0){
                        delta=0;
                      }
                        else{
                          if(Last_Booking_read<LifeCleaner_effekt_read){
                            delta=aktuell_time-LifeCleaner_effekt_read;

                            myprint("Aufschlag nach Lifecleaner","","",true,true,false,1,0); 
                          }
                          else{
                          delta=aktuell_time-Last_Booking_read;

                          myprint("Aufschlag nach letzter Buchung","","",true,true,false,1,0); 
                          }
                         }
                      
                      time_writing=aktuell_time;
                     
                   }
 ///////////////////////////////////////////////////////////////////////////////////////
               //myprint("------------------------------------------------","","",true,true,false,1,0);   

              myprint("Raywert alt:","",Ray_value_extern_read,true,true,false,1,0); 
              

              myprint(Medi[medikament-1],"","",true,true,false,1,0); 
        
              if(medikament!=7){
        
              myprint("Bonus:-","",Bonus,true,true,false,1,0); 
              
              //deltaray=(tagesdosis*delta/86400)*1000;
              deltaray=(tagesdosis*delta*10)/864;
              myprint("Delta in RAY:+","",deltaray,true,true,false,1,0); 

                if(Bonus>Ray_value_extern_read+deltaray){
                  ray_writing=minimum_ray_writing;
                }
                else{
              ray_writing=(Ray_value_extern_read+deltaray)-Bonus;
                }
           
                if(ray_writing>=maximum_ray_writing){
                  ray_writing=maximum_ray_writing;
                }
                
              }
              if(medikament==7){
         
              myprint("Malus:+","",Bonus,true,true,false,1,0); 
         
              //deltaray=(tagesdosis*delta/86400)*1000;
                deltaray=(tagesdosis*delta*10)/864;
              myprint("Delta in RAY:+","",deltaray,true,true,false,1,0);
        
               if(Bonus>Ray_value_extern_read+deltaray){
                  ray_writing=minimum_ray_writing;
                }
                else{
              ray_writing=(Ray_value_extern_read+deltaray)+Bonus;
                }
           
                if(ray_writing>=maximum_ray_writing){
                  ray_writing=maximum_ray_writing;
                }
              
              }
              
       
            myprint("Raywert neu:","",ray_writing,true,true,false,1,0);
             //update oder drawback
             if(medikament==1||medikament==7){

              if(medikament==7){Menge_Draw=Menge_Draw+1;}
              
                writing(knownKeys[last_key],58,Con_Start_read,time_writing);
                writing(knownKeys[last_key],56,Con_End,ray_writing);
             }

////////////////////////////////////////bis hier ueberarbeitet
              
              //Bloodclean oder Cleanray
              if(medikament==5||medikament==6){

                
                if(medikament==5){Menge_Blood=Menge_Blood+1;}
                if(medikament==6){Menge_Clean=Menge_Clean+1;}
                
                writing(knownKeys[last_key],58,Con_Start_read,time_writing);
                writing(knownKeys[last_key],56,Con_End,ray_writing);
                
                block_writing[used_con]=aktuell_time;
                
                writing(knownKeys[last_key],ziel_block1, block_writing[0], block_writing[1]);
                writing(knownKeys[last_key],ziel_block2, block_writing[2], block_writing[3]);
                writing(knownKeys[last_key],ziel_block3, block_writing[4], block_writing[5]);
                writing(knownKeys[last_key],ziel_block4, block_writing[6], block_writing[7]);
              }
              
              //Dekon
              if(medikament==3){

                Menge_Dekon=Menge_Dekon+1;
               
                writing(knownKeys[last_key],58,Con_Start_read,time_writing);
                writing(knownKeys[last_key],56,Con_End,ray_writing);
                
                block_writing[used_con]=aktuell_time;
                
                writing(knownKeys[last_key],ziel_block1, block_writing[0], block_writing[1]);
                writing(knownKeys[last_key],ziel_block2, block_writing[2], block_writing[3]);
                writing(knownKeys[last_key],ziel_block3, block_writing[4], block_writing[5]);
                writing(knownKeys[last_key],ziel_block4, block_writing[6], block_writing[7]);
                writing(knownKeys[last_key],ziel_block5, block_writing[8], block_writing[9]);
                writing(knownKeys[last_key],ziel_block6, block_writing[10], block_writing[11]);
                writing(knownKeys[last_key],ziel_block7, block_writing[12], block_writing[13]);
              }
              
                // Lifecleaner 
                if (medikament==4){

                 Menge_Life=Menge_Life+1;
                  
                 writing(knownKeys[last_key],58,Con_Start_read,aktuell_time);
                 writing(knownKeys[last_key],57,aktuell_time+LifeCleaner_buffer,archtype_read); 
                 writing(knownKeys[last_key],56,Con_End,ray_writing);
                 
                block_writing[used_con]=aktuell_time;
                
                writing(knownKeys[last_key],ziel_block1, block_writing[0], block_writing[1]);
                writing(knownKeys[last_key],ziel_block2, block_writing[2], block_writing[3]);
                writing(knownKeys[last_key],ziel_block3, block_writing[4], block_writing[5]);
                writing(knownKeys[last_key],ziel_block4, block_writing[6], block_writing[7]);
                writing(knownKeys[last_key],ziel_block5, block_writing[8], block_writing[9]);
                }
              
              //Nanoclean
              if(medikament==2){

                Menge_Nanoclean=Menge_Nanoclean+1;
                
                writing(knownKeys[last_key],58,Con_Start_read,time_writing);
                writing(knownKeys[last_key],56,Con_End,ray_writing);
                
                block_writing[used_con]=aktuell_time;
                
                writing(knownKeys[last_key],ziel_block1, block_writing[0], block_writing[1]);
                writing(knownKeys[last_key],ziel_block2, block_writing[2], block_writing[3]);
                writing(knownKeys[last_key],ziel_block3, block_writing[4], block_writing[5]);
                writing(knownKeys[last_key],ziel_block4, block_writing[6], block_writing[7]);
              }
              
            }
//2. Einnahme Medis erlaubt 
//nein 
            else{ 
              if(used_tag>=limit_tag){
      
                myprint("Tageslimit erreicht","","",true,true,false,1,0);
                buchungsgrund2=" Limit erreicht";
                
              }
              
              if(used_con>=limit_con){
         
                myprint("Conlimit erreicht","","",true,true,false,1,0);
                buchungsgrund2=" Limit erreicht";
              }
 //keine Medibuchung nur Update             
        
          //myprint("------------------------------------------------","","",true,true,false,1,0);    
         
               myprint("Aktuelle Zeit:","",aktuell_time,true,true,false,1,0);   
              
               myprint("Letzte Buchung:","",Last_Booking_read,true,true,false,1,0);   
        
        
               //myprint("------------------------------------------------","","",true,true,false,1,0);   
            
              if(LifeCleaner_effekt_read>=aktuell_time){
          
                myprint("Lifecleanereffekt aktiv: ja","",aktuell_time,true,true,false,1,0);   
                delta=0;
                time_writing=LifeCleaner_effekt_read;
              }else {
            
                myprint("Lifecleanereffekt aktiv: nein","",aktuell_time,true,true,false,1,0);   
                 if(aktuell_time-Last_Booking_read<0){
                        delta=0;
                      }
                        else{
                          delta=aktuell_time-Last_Booking_read;
                          }
                time_writing=aktuell_time;
                }
        
      
              // myprint("------------------------------------------------","","",true,true,false,1,0);   
        
              myprint("Raywert alt:","",Ray_value_extern_read,true,true,false,1,0);  
         
              myprint(Medi[0],"","",true,true,false,1,0);   
          
              myprint("Bonus:","",0,true,true,false,1,0); 
                
         
              //deltaray=(tagesdosis*delta/86400)*1000;
              deltaray=(tagesdosis*delta*10)/864;
              myprint("Delta in RAY:+","",deltaray,true,true,false,1,0); 
                
              ray_writing=(Ray_value_extern_read+deltaray);

              if(ray_writing<minimum_ray_writing){
                  ray_writing=minimum_ray_writing;
                }
                if(ray_writing>maximum_ray_writing){
                  ray_writing=maximum_ray_writing;
                }
              
              myprint("Raywert neu:","",ray_writing,true,true,false,1,0);  
              
              writing(knownKeys[last_key],58,Con_Start_read,time_writing);
              writing(knownKeys[last_key],56,Con_End,ray_writing);
          }
                    ray_writing=ray_writing/1000;
      /*  if(ray_writing==0){                   msg3="kein Ray    ";}
        if(ray_writing>0&&ray_writing<=50){   msg3="light Green ";}  
        if(ray_writing>50&&ray_writing<=100){ msg3="Green       ";}  
        if(ray_writing>100&&ray_writing<=150){msg3="dark Green  ";}  
        if(ray_writing>150&&ray_writing<=200){msg3="light Yellow";}
        if(ray_writing>200&&ray_writing<=250){msg3="Yellow      ";}
        if(ray_writing>250&&ray_writing<=300){msg3="dark Yellow ";}
        if(ray_writing>300&&ray_writing<=350){msg3="light Red   ";}
        if(ray_writing>350&&ray_writing<=400){msg3="Red         ";}
        if(ray_writing>400){                  msg3="dark Red    ";}*/
   }

   else {
//1. nicht richtiges Con, Anreisetag oder nach Conende
//, mach nichts

        if(Con_Start_read!=con_start_time){ 
   
        buchungsgrund=" nicht richtiges con";
        }
        else if(con_tag<erster_buchungstag){
    
        buchungsgrund=" zu frueh";
        }
        else if(con_tag>anzahl_tage-1){ //an Anreisetag denken
 
        buchungsgrund=" zu spaet";
        }
        myprint(buchungsgrund,"","",true,true,false,1,0);  
         //buzzer_play( 3,100);
   }

      // myprint("------------------------------------------------","","",true,true,false,1,0);   

memset( block_writing, 0, sizeof( block_writing));
}
