/*Auflistung Unterfunktionen, die für Medikamentenbuchungen benötigt werden
 * 
 * medibuchung_MFRC522     // 
 * medibuchung_PN532     // 
 */
 
int medibuchung_MFRC522(unsigned long medikament){
char* Medi[] {"Update","Nanoclean","Dekon","Lifecleaner","Bloodclean","Cleanray","Drawback"};
unsigned long Bonus;
unsigned long delta;
unsigned long deltaray;
unsigned long time_writing;


int ziel_block1,ziel_block2,ziel_block3;
unsigned long block_writing_MFRC522[6];
int limit_tag=0;
int limit_con=0;
int used_tag=0;
int used_con=0;

//welches Medikament soll gebucht werden und welche Spezifikationen hat es
            
            // update
            if (medikament==1){
              Bonus=0;
              Tag_analyse_MFRC522(medikament,0);
              limit_tag= 100; 
              limit_con= 100;
              used_tag = 0;
              used_con = 0;
              buchungsgrund="Update     ";
            }

            //Nanoclean
            if (medikament==2){
              Tag_analyse_MFRC522(1,0);
              NanoClean=random(Nanoclean_min_effekt,Nanoclean_max_effekt)*1000UL;
              Bonus=NanoClean;
              Tag_analyse_MFRC522(medikament,0);
              limit_tag= Nano_per_day;   
              limit_con= Nano_per_con; 
              used_tag = Nanocounter_thisday;
              used_con = Nanocounter_allday;
              buchungsgrund="Nanoclean  ";
              
              ziel_block1=54;
              ziel_block2=53;
              
              for(int x=0;x<4;x++){
                block_writing_MFRC522[x]=NanoClean_read[x];
              }
            }

            //Dekon
            if (medikament==3){
              Tag_analyse_MFRC522(1,0);
              Dekon = random(Dekon_min_effekt,Dekon_max_effekt)*1000UL;    
              Bonus=Dekon;
              Tag_analyse_MFRC522(medikament,0);
              limit_tag= Dekon_per_day; 
              limit_con= Dekon_per_con; 
              used_tag = Dekoncounter_thisday;
              used_con = Dekoncounter_allday;
              buchungsgrund="Dekon      ";
              
              ziel_block1=50;
              ziel_block2=49;
              ziel_block3=48;
              
              for(int x=0;x<6;x++){
                block_writing_MFRC522[x]=Dekon_read[x];
              }
              
            }

            //Lifecleaner
            if (medikament==4){
              Tag_analyse_MFRC522(1,0);
              LifeCleaner=random(Lifecleaner_min_effekt,Lifecleaner_max_effekt)*1000UL;   //weil keinen Effekt auf Ray-Wert ist aber als Variable möglich
              Bonus=LifeCleaner;
            
              Tag_analyse_MFRC522(medikament,0);
              limit_tag= LifeCleaner_per_day;    
              limit_con= Life_per_con;  
              used_tag = Lifecounter_thisday;
              used_con = Lifecounter_allday;
              buchungsgrund="Lifecleaner";

              ziel_block1=46;
              ziel_block2=45;
              ziel_block3=44;
              
              for(int x=0;x<6;x++){
                block_writing_MFRC522[x]=LifeCleaner_read[x];
              }
            }

            //Bloodclean
            if (medikament==5){
              Tag_analyse_MFRC522(1,0);
              BloodClean=random(Bloodclean_min_effekt,Bloodclean_max_effekt)*1000UL; 
              Bonus=BloodClean;
              Tag_analyse_MFRC522(medikament,0);
              limit_tag= Blood_per_day; 
              limit_con= Blood_per_con;   
              used_tag = Bloodcounter_thisday;
              used_con = Bloodcounter_allday;
              buchungsgrund="Blutwäsche ";

              ziel_block1=42;
              ziel_block2=41;
              ziel_block3=40;
              
              for(int x=0;x<6;x++){
                block_writing_MFRC522[x]=BloodClean_read[x];
              }
            }

            //Cleanray
            if (medikament==6){
              Tag_analyse_MFRC522(1,0);
              Cleanray=random(Cleanray_min_effekt,Cleanray_max_effekt)*1000UL;  
              Bonus=Cleanray;
              Tag_analyse_MFRC522(medikament,0);
              limit_tag= Clean_per_day; 
              limit_con= Clean_per_con;
              used_tag = Cleancounter_thisday;
              used_con = Cleancounter_allday;
              buchungsgrund="Cleanray   ";

              ziel_block1=38;
              ziel_block2=37;
              ziel_block3=36;
              
              for(int x=0;x<6;x++){
                block_writing_MFRC522[x]=Cleanray_read[x];
              }
            }

            //Drawback
            if(medikament==7){
              Tag_analyse_MFRC522(1,0);
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
      Serial.println("------------------------------------------------");
 if(Last_Booking_read> aktuell_time){Last_Booking_read=aktuell_time;}
 
//Falls ein Gerät durchgängig läuft
con_tag_bestimmen(aktuell_time,con_start_time,rest_time);
     
      
//1. Richtiges Con und nach Anreise

Serial.print("Richtiges Con:");
             
 if(Con_Start_read==con_start_time&&con_tag>=erster_buchungstag&&con_tag<=anzahl_tage){
 Serial.println("ja");
          
//2. Einnahme Medis erlaubt          
      
     if(used_tag<limit_tag&&used_con<limit_con){ // muss kleiner sein, damit eine weitere buchung erlaubt ist
      
        //ja   
              Serial.println("------------------------------------------------");    
              Serial.print("Aktuelle Zeit:");
              Serial.println(aktuell_time);
              Serial.print("Letzte Buchung:");
              Serial.println(Last_Booking_read);
        
              
//3.Lifecleanereffekt aktiv?            
                  Serial.println("------------------------------------------------");
                  Serial.print("Lifecleanereffekt aktiv:");
                  if(LifeCleaner_effekt_read>=aktuell_time){
                      Serial.println("ja");
                      delta=0;
                      time_writing=LifeCleaner_effekt_read;
                      servo_value=rueckgabe;
                      Serial.println("rückgabe");
                      if(medikament==7){
                        Bonus=0;
                      }
                  }else {
                      Serial.println("nein");
                      if(aktuell_time-Last_Booking_read<0){
                        delta=0;
                      }
                        else{
                          delta=aktuell_time-Last_Booking_read;
                          }
                      
                      time_writing=aktuell_time;
                     
                   }
        
              Serial.println("------------------------------------------------");
              Serial.print("Raywert alt:");
              Serial.println(Ray_value_extern_read);
              Serial.println(Medi[medikament-1]);
        
              if(medikament!=7){
              Serial.print("Bonus:-");
              Serial.println(Bonus);
              Serial.print("Delta in RAY:+");
              deltaray=(tagesdosis*delta/86400)*1000;
              Serial.println(deltaray);

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
              Serial.print("Malus:+");
              Serial.println(Bonus);
              Serial.print("Delta in RAY:+");
              deltaray=(tagesdosis*delta/86400)*1000;
              Serial.println(deltaray);
        
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
              
              Serial.print("Raywert neu:");
              Serial.println(ray_writing);
              Serial.println();

             //update oder drawback
             if(medikament==1||medikament==7){
                writing_MFRC522(knownKeys[last_key],58,Con_Start_read,time_writing);
                writing_MFRC522(knownKeys[last_key],56,Ray_value_intern_read,ray_writing);
                 servo_value=rueckgabe;
                      Serial.println("rückgabe");
             }
              
              //Dekon, Bloodclean oder Cleanray
              if(medikament==3||medikament==5||medikament==6){

                writing_MFRC522(knownKeys[last_key],58,Con_Start_read,time_writing);
                writing_MFRC522(knownKeys[last_key],56,Ray_value_intern_read,ray_writing);
                
                block_writing_MFRC522[used_con]=aktuell_time;
                
                writing_MFRC522(knownKeys[last_key],ziel_block1, block_writing_MFRC522[0], block_writing_MFRC522[1]);
                writing_MFRC522(knownKeys[last_key],ziel_block2, block_writing_MFRC522[2], block_writing_MFRC522[3]);
                writing_MFRC522(knownKeys[last_key],ziel_block3, block_writing_MFRC522[4], block_writing_MFRC522[5]);
                 servo_value=tresor;
                      Serial.println("tresor");
              }
                // Lifecleaner 
                if (medikament==4){
                 writing_MFRC522(knownKeys[last_key],58,Con_Start_read,aktuell_time+LifeCleaner_buffer);
                 writing_MFRC522(knownKeys[last_key],57,aktuell_time+LifeCleaner_buffer,archtype_read); 
                 writing_MFRC522(knownKeys[last_key],56,Ray_value_intern_read,ray_writing);
                 
                block_writing_MFRC522[used_con]=aktuell_time;
                
                writing_MFRC522(knownKeys[last_key],ziel_block1, block_writing_MFRC522[0], block_writing_MFRC522[1]);
                writing_MFRC522(knownKeys[last_key],ziel_block2, block_writing_MFRC522[2], block_writing_MFRC522[3]);
                writing_MFRC522(knownKeys[last_key],ziel_block3, block_writing_MFRC522[4], block_writing_MFRC522[5]);
                  servo_value=tresor;
                      Serial.println("tresor");
                }
              
              //Nanoclean
              if(medikament==2){
                writing_MFRC522(knownKeys[last_key],58,Con_Start_read,time_writing);
                writing_MFRC522(knownKeys[last_key],56,Ray_value_intern_read,ray_writing);
                
                block_writing_MFRC522[used_con]=aktuell_time;
                
                writing_MFRC522(knownKeys[last_key],ziel_block1, block_writing_MFRC522[0], block_writing_MFRC522[1]);
                writing_MFRC522(knownKeys[last_key],ziel_block2, block_writing_MFRC522[2], block_writing_MFRC522[3]);
                  servo_value=tresor;
                      Serial.println("tresor");
              }
              
            }
//2. Einnahme Medis erlaubt 
//nein 
            else{ 
              if(used_tag>=limit_tag){
                Serial.println("Tageslimit erreicht");
                buchungsgrund2=" Limit erreicht";
                  servo_value=rueckgabe;
                      Serial.println("rückgabe");
              }
              
              if(used_con>=limit_con){
                Serial.println("Conlimit erreicht");
                buchungsgrund2=" Limit erreicht";
                servo_value=rueckgabe;
                      Serial.println("rückgabe");
              }
 //keine medibuchung_MFRC522 nur Update             
         Serial.println("------------------------------------------------");    
              Serial.print("Aktuelle Zeit:");
              Serial.println(aktuell_time);
              Serial.print("Letzte Buchung:");
              Serial.println(Last_Booking_read);
        
              Serial.println("------------------------------------------------");
               
              Serial.print("Lifecleanereffekt aktiv:");
              if(LifeCleaner_effekt_read>=aktuell_time){
                Serial.println("ja");
                delta=0;
                time_writing=LifeCleaner_effekt_read;
              }else {
                Serial.println("nein");
                 if(aktuell_time-Last_Booking_read<0){
                        delta=0;
                      }
                        else{
                          delta=aktuell_time-Last_Booking_read;
                          }
                time_writing=aktuell_time;
                }
        
              Serial.println("------------------------------------------------");
              Serial.print("Raywert alt:");
              Serial.println(Ray_value_extern_read);
              Serial.println(Medi[0]);
              Serial.print("Bonus:");
              Serial.println(0);
              Serial.print("Delta in RAY:+");
              deltaray=(tagesdosis*delta/86400)*1000;
              Serial.println(deltaray);
              ray_writing=(Ray_value_extern_read+deltaray);

              if(ray_writing<minimum_ray_writing){
                  ray_writing=minimum_ray_writing;
                }
                if(ray_writing>maximum_ray_writing){
                  ray_writing=maximum_ray_writing;
                }
              
              Serial.print("Raywert neu:");
              Serial.println(ray_writing);
              Serial.println(); 
              
              writing_MFRC522(knownKeys[last_key],58,Con_Start_read,time_writing);
              writing_MFRC522(knownKeys[last_key],56,Ray_value_intern_read,ray_writing);
          }
          raywert=ray_writing/1000;
                  if(raywert==0){msg3="kein Ray";}
        if(raywert>0&&raywert<=50){msg3="light Green";}  
        if(raywert>50&&raywert<=100){msg3="Green";}  
        if(raywert>100&&raywert<=150){msg3="dark Green";}  
        if(raywert>150&&raywert<=200){msg3="light Yellow";}
        if(raywert>200&&raywert<=250){msg3="Yellow";}
        if(raywert>250&&raywert<=300){msg3="dark Yellow";}
        if(raywert>300&&raywert<=350){msg3="light Red";}
        if(raywert>350&&raywert<=400){msg3="Red";}
        if(raywert>400){msg3="dark Red";}
    
    msg1="Neuer";
    msg2="Raywert";
    
    msg4="";
   }

   else {
//1. nicht richtiges Con, Anreisetag oder nach Conende
//, mach nichts
        if(Con_Start_read!=con_start_time){ 
        Serial.println("nein");

        buchungsgrund=" nicht richtiges con";
        servo_value=rueckgabe;
                      Serial.println("rückgabe");
        }
        if(con_tag<erster_buchungstag){
          Serial.println("zu früh");

        buchungsgrund=" zu früh";
        servo_value=rueckgabe;
                      Serial.println("rückgabe");
        }
        if(con_tag>anzahl_tage){
          Serial.println("zu spät");

        buchungsgrund=" zu spät";
        servo_value=rueckgabe;
                      Serial.println("rückgabe");
        }
        buzzer_play( 5,100);
    
    msg1="Keine";
    msg2="Buchung";
    msg3="";
    msg4="";
   }
   if (servo_value==rueckgabe){
    digitalWrite(ledPin2,HIGH);

   }
   myservo_wippe.write(servo_value);
   
      Serial.println("------------------------------------------------");

   

}

//*****************************************************************************************//


 
int medibuchung_PN532(unsigned long medikament){
char* Medi[] {"Update","Nanoclean","Dekon","Lifecleaner","Bloodclean","Cleanray","Drawback"};
unsigned long Bonus;
unsigned long delta;
unsigned long deltaray;
unsigned long time_writing;


int ziel_block1,ziel_block2,ziel_block3;
unsigned long block_writing_PN532[6];
int limit_tag=0;
int limit_con=0;
int used_tag=0;
int used_con=0;

//welches Medikament soll gebucht werden und welche Spezifikationen hat es
            
            // update
            if (medikament==1){
              Bonus=0;
              Tag_analyse_PN532(medikament,0);
              limit_tag= 100; 
              limit_con= 100;
              used_tag = 0;
              used_con = 0;
              buchungsgrund="Update     ";
            }

            //Nanoclean
            if (medikament==2){
              Tag_analyse_PN532(1,0);
              NanoClean=random(Nanoclean_min_effekt,Nanoclean_max_effekt)*1000UL;
              Bonus=NanoClean;
              Tag_analyse_PN532(medikament,0);
              limit_tag= Nano_per_day;   
              limit_con= Nano_per_con; 
              used_tag = Nanocounter_thisday;
              used_con = Nanocounter_allday;
              buchungsgrund="Nanoclean  ";
              
              ziel_block1=54;
              ziel_block2=53;
              
              for(int x=0;x<4;x++){
                block_writing_PN532[x]=NanoClean_read[x];
              }
            }

            //Dekon
            if (medikament==3){
              Tag_analyse_PN532(1,0);
              Dekon = random(Dekon_min_effekt,Dekon_max_effekt)*1000UL;    
              Bonus=Dekon;
              Tag_analyse_PN532(medikament,0);
              limit_tag= Dekon_per_day; 
              limit_con= Dekon_per_con; 
              used_tag = Dekoncounter_thisday;
              used_con = Dekoncounter_allday;
              buchungsgrund="Dekon      ";
              
              ziel_block1=50;
              ziel_block2=49;
              ziel_block3=48;
              
              for(int x=0;x<6;x++){
                block_writing_PN532[x]=Dekon_read[x];
              }
              
            }

            //Lifecleaner
            if (medikament==4){
              Tag_analyse_PN532(1,0);
              LifeCleaner=random(Lifecleaner_min_effekt,Lifecleaner_max_effekt)*1000UL;   //weil keinen Effekt auf Ray-Wert ist aber als Variable möglich
              Bonus=LifeCleaner;
            
              Tag_analyse_PN532(medikament,0);
              limit_tag= LifeCleaner_per_day;    
              limit_con= Life_per_con;  
              used_tag = Lifecounter_thisday;
              used_con = Lifecounter_allday;
              buchungsgrund="Lifecleaner";

              ziel_block1=46;
              ziel_block2=45;
              ziel_block3=44;
              
              for(int x=0;x<6;x++){
                block_writing_PN532[x]=LifeCleaner_read[x];
              }
            }

            //Bloodclean
            if (medikament==5){
              Tag_analyse_PN532(1,0);
              BloodClean=random(Bloodclean_min_effekt,Bloodclean_max_effekt)*1000UL; 
              Bonus=BloodClean;
              Tag_analyse_PN532(medikament,0);
              limit_tag= Blood_per_day; 
              limit_con= Blood_per_con;   
              used_tag = Bloodcounter_thisday;
              used_con = Bloodcounter_allday;
              buchungsgrund="Blutwäsche ";

              ziel_block1=42;
              ziel_block2=41;
              ziel_block3=40;
              
              for(int x=0;x<6;x++){
                block_writing_PN532[x]=BloodClean_read[x];
              }
            }

            //Cleanray
            if (medikament==6){
              Tag_analyse_PN532(1,0);
              Cleanray=random(Cleanray_min_effekt,Cleanray_max_effekt)*1000UL;  
              Bonus=Cleanray;
              Tag_analyse_PN532(medikament,0);
              limit_tag= Clean_per_day; 
              limit_con= Clean_per_con;
              used_tag = Cleancounter_thisday;
              used_con = Cleancounter_allday;
              buchungsgrund="Cleanray   ";

              ziel_block1=38;
              ziel_block2=37;
              ziel_block3=36;
              
              for(int x=0;x<6;x++){
                block_writing_PN532[x]=Cleanray_read[x];
              }
            }

            //Drawback
            if(medikament==7){
              Tag_analyse_PN532(1,0);
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
      Serial.println("------------------------------------------------");

//Falls ein Gerät durchgängig läuft
con_tag_bestimmen(aktuell_time,con_start_time,rest_time);
     
      
//1. Richtiges Con und nach Anreise

Serial.print("Richtiges Con:");
             
 if(Con_Start_read==con_start_time&&con_tag>=erster_buchungstag&&con_tag<=anzahl_tage){
 Serial.println("ja");
          
//2. Einnahme Medis erlaubt          
      
     if(used_tag<limit_tag&&used_con<limit_con){ // muss kleiner sein, damit eine weitere buchung erlaubt ist
      
        //ja   
              Serial.println("------------------------------------------------");    
              Serial.print("Aktuelle Zeit:");
              Serial.println(aktuell_time);
              Serial.print("Letzte Buchung:");
              Serial.println(Last_Booking_read);
        
              
//3.Lifecleanereffekt aktiv?            
                  Serial.println("------------------------------------------------");
                  Serial.print("Lifecleanereffekt aktiv:");
                  if(LifeCleaner_effekt_read>=aktuell_time){
                      Serial.println("ja");
                      delta=0;
                      time_writing=LifeCleaner_effekt_read;
                      servo_value=rueckgabe;
                      if(medikament==7){
                        Bonus=0;
                      }
                  }else {
                      Serial.println("nein");
                      if(aktuell_time-Last_Booking_read<0){
                        delta=0;
                      }
                        else{
                          delta=aktuell_time-Last_Booking_read;
                          }
                      
                      time_writing=aktuell_time;
                     
                   }
        
              Serial.println("------------------------------------------------");
              Serial.print("Raywert alt:");
              Serial.println(Ray_value_extern_read);
              Serial.println(Medi[medikament-1]);
        
              if(medikament!=7){
              Serial.print("Bonus:-");
              Serial.println(Bonus);
              Serial.print("Delta in RAY:+");
              deltaray=(tagesdosis*delta/86400)*1000;
              Serial.println(deltaray);

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
              Serial.print("Malus:+");
              Serial.println(Bonus);
              Serial.print("Delta in RAY:+");
              deltaray=(tagesdosis*delta/86400)*1000;
              Serial.println(deltaray);
        
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
              
              Serial.print("Raywert neu:");
              Serial.println(ray_writing);
              Serial.println();

             //update oder drawback
             if(medikament==1||medikament==7){
              delay(50);
                writing_PN532(knownKeys[last_key],58,Con_Start_read,time_writing);
                delay(50);
                writing_PN532(knownKeys[last_key],56,Ray_value_intern_read,ray_writing);
                servo_value=rueckgabe;
                
             }
              
              //Dekon, Bloodclean oder Cleanray
              if(medikament==3||medikament==5||medikament==6){

                writing_PN532(knownKeys[last_key],58,Con_Start_read,time_writing);
                writing_PN532(knownKeys[last_key],56,Ray_value_intern_read,ray_writing);
                
                block_writing_PN532[used_con]=aktuell_time;
                
                writing_PN532(knownKeys[last_key],ziel_block1, block_writing_PN532[0], block_writing_PN532[1]);
                writing_PN532(knownKeys[last_key],ziel_block2, block_writing_PN532[2], block_writing_PN532[3]);
                writing_PN532(knownKeys[last_key],ziel_block3, block_writing_PN532[4], block_writing_PN532[5]);
                servo_value=tresor;
              }
                // Lifecleaner 
                if (medikament==4){
                 writing_PN532(knownKeys[last_key],58,Con_Start_read,aktuell_time+LifeCleaner_buffer);
                 writing_PN532(knownKeys[last_key],57,aktuell_time+LifeCleaner_buffer,archtype_read); 
                 writing_PN532(knownKeys[last_key],56,Ray_value_intern_read,ray_writing);
                 
                block_writing_PN532[used_con]=aktuell_time;
                
                writing_PN532(knownKeys[last_key],ziel_block1, block_writing_PN532[0], block_writing_PN532[1]);
                writing_PN532(knownKeys[last_key],ziel_block2, block_writing_PN532[2], block_writing_PN532[3]);
                writing_PN532(knownKeys[last_key],ziel_block3, block_writing_PN532[4], block_writing_PN532[5]);
                servo_value=tresor;
                }
              
              //Nanoclean
              if(medikament==2){
                writing_PN532(knownKeys[last_key],58,Con_Start_read,time_writing);
                writing_PN532(knownKeys[last_key],56,Ray_value_intern_read,ray_writing);
                
                block_writing_PN532[used_con]=aktuell_time;
                
                writing_PN532(knownKeys[last_key],ziel_block1, block_writing_PN532[0], block_writing_PN532[1]);
                writing_PN532(knownKeys[last_key],ziel_block2, block_writing_PN532[2], block_writing_PN532[3]);
                servo_value=tresor;
              }
              
            }
//2. Einnahme Medis erlaubt 
//nein 
            else{ 
              if(used_tag>=limit_tag){
                Serial.println("Tageslimit erreicht");
                buchungsgrund2=" Limit erreicht";
                servo_value=rueckgabe;
              }
              
              if(used_con>=limit_con){
                Serial.println("Conlimit erreicht");
                buchungsgrund2=" Limit erreicht";
                servo_value=rueckgabe;
              }
 //keine medibuchung_PN532 nur Update             
         Serial.println("------------------------------------------------");    
              Serial.print("Aktuelle Zeit:");
              Serial.println(aktuell_time);
              Serial.print("Letzte Buchung:");
              Serial.println(Last_Booking_read);
        
              Serial.println("------------------------------------------------");
               
              Serial.print("Lifecleanereffekt aktiv:");
              if(LifeCleaner_effekt_read>=aktuell_time){
                Serial.println("ja");
                delta=0;
                time_writing=LifeCleaner_effekt_read;
              }else {
                Serial.println("nein");
                 if(aktuell_time-Last_Booking_read<0){
                        delta=0;
                      }
                        else{
                          delta=aktuell_time-Last_Booking_read;
                          }
                time_writing=aktuell_time;
                }
        
              Serial.println("------------------------------------------------");
              Serial.print("Raywert alt:");
              Serial.println(Ray_value_extern_read);
              Serial.println(Medi[0]);
              Serial.print("Bonus:");
              Serial.println(0);
              Serial.print("Delta in RAY:+");
              deltaray=(tagesdosis*delta/86400)*1000;
              Serial.println(deltaray);
              ray_writing=(Ray_value_extern_read+deltaray);

              if(ray_writing<minimum_ray_writing){
                  ray_writing=minimum_ray_writing;
                }
                if(ray_writing>maximum_ray_writing){
                  ray_writing=maximum_ray_writing;
                }
              
              Serial.print("Raywert neu:");
              Serial.println(ray_writing);
              Serial.println(); 
              
              writing_PN532(knownKeys[last_key],58,Con_Start_read,time_writing);
              writing_PN532(knownKeys[last_key],56,Ray_value_intern_read,ray_writing);
          }
                raywert=ray_writing/1000;
                  if(raywert==0){msg3="kein Ray";}
        if(raywert>0&&raywert<=50){msg3="light Green";}  
        if(raywert>50&&raywert<=100){msg3="Green";}  
        if(raywert>100&&raywert<=150){msg3="dark Green";}  
        if(raywert>150&&raywert<=200){msg3="light Yellow";}
        if(raywert>200&&raywert<=250){msg3="Yellow";}
        if(raywert>250&&raywert<=300){msg3="dark Yellow";}
        if(raywert>300&&raywert<=350){msg3="light Red";}
        if(raywert>350&&raywert<=400){msg3="Red";}
        if(raywert>400){msg3="dark Red";}
    
    msg1="Neuer";
    msg2="Raywert ";
    
    msg4="";
    
   }

   else {
//1. nicht richtiges Con, Anreisetag oder nach Conende
//, mach nichts
        if(Con_Start_read!=con_start_time){ 
        Serial.println("nein");

        buchungsgrund=" nicht richtiges con";
        servo_value=rueckgabe;
        }
        if(con_tag<erster_buchungstag){
          Serial.println("zu früh");

        buchungsgrund=" zu früh";
        servo_value=rueckgabe;
        }
        if(con_tag>anzahl_tage){
          Serial.println("zu spät");

        buchungsgrund=" zu spät";
        servo_value=rueckgabe;
        }
        buzzer_play( 5,100);
    
    msg1="Keine";
    msg2="Buchung";
    msg3="";
    msg4="";
   }
   myservo_wippe.write(servo_value);
 
      Serial.println("------------------------------------------------");

    

}
