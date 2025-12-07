void myprint(char*titel,String inhalt,unsigned long wert,bool wp,bool ln,bool unix,int debuglevel,int ausgabe){
 
//  myprint(Text:"",Text2:"",Wert:"",writeorprint:false,ln_on:true,unix_on:false,debug:1,0:0);
  
  
 // myprint(Text:"Nun Dongel auflegen",Text2:""          ,""                 ,false    ,true     ,false      ,1              ,0);
  //myprint(char*titel           ,char*inhalt ,unsigned long wert ,bool wp  ,bool ln  ,bool unix  ,int debuglevel ,int ausgabe){
  /*titel= bezeichnung der Ausgabe
   * inhalt = falls text und keine werte
   * wert = ausgabewerte
   * wp = write ==0 print ==1
   * ln = neue line oder nicht
   * unix= long konvertieren oder nur als wert ausgeben
   * debuglevel = falls ausgabe nur in bestimmten situationen erwünscht
   * ausgabe= auswahl des seriellen 0s
   */
  
  if(debuglevel>=debug){

    if(ausgabe==0){
      
        if(titel!=""){
        Serial.print(titel);
          } 
        if(inhalt!=""){
        Serial.print(inhalt);
          }
        if(wert!=""){
          if(unix==false){
          Serial.print(wert);
            }
          if(unix==true){
          unix_converter(wert,UTC);  
            }
          }
          
      if(ln==true){
        Serial.println("");
      }
      else{
        Serial.print("");
      }    
    }
//************************************************************
    if(ausgabe==1){
      
      if(titel!=""){
      Serial1.print(titel);
      } 
        if(inhalt!=""){
        Serial1.print(inhalt);
        }
        if(wert!=""){
          if(unix==false){
          Serial1.print(wert);
          }
          if(unix==true){
          unix_converter(wert,UTC);  
          }
        }
      if(ln==true){
        Serial1.println("");
      }
      else{
        Serial1.print("");
      }    
    }
//************************************************************
    if(ausgabe==2){
      
      if(titel!=""){
      Serial2.print(titel);delay(10);
      } 
        if(inhalt!=""){
        Serial2.print(inhalt);delay(10);
        }
        if(wert!=""){
          if(unix==false){
          Serial2.print(wert);delay(10);
          }
          if(unix==true){
          unix_converter(wert,UTC);  
          }
        }
      if(ln==true){
        Serial2.println("");delay(10);
      }
      else{
        Serial2.print("");delay(10);
      }    
    }
//************************************************************
    if(ausgabe==3){
      
        if(titel!=""){
        Serial3.write(titel);//delay(50);
          } 
        if(inhalt!=""){
         Serial3.print(inhalt);//delay(50);
          }
        if(wert!=""){
          if(unix==false){
          Serial3.print(wert);//delay(50);
            }
          if(unix==true){
          unix_converter(wert,UTC);  
            }
          }
          
      if(ln==true){
        Serial3.write('\n');delay(50);
      }
      else{
        Serial3.write("");delay(50);
      }    
    }

//************************************************************    
  }
}
int unix_converter(unsigned long t_unix_date_start,int Zeitzone){
  
  unsigned long t_unix_date;
  char* typen3[]{""," WZ"," SZ","Leer"};
  
  t_unix_date=t_unix_date_start+(Zeitzone*3600);
  
if (t_unix_date==0){

  myprint(typen3[3],"","",true,false,false,1,0);
  delay(50);
  }
else{

  Serial.printf(" Date: %4d-%02d-%02d %02d:%02d:%02d", year(t_unix_date), month(t_unix_date), day(t_unix_date), hour(t_unix_date), minute(t_unix_date), second(t_unix_date));


  myprint(typen3[Zeitzone],"","",true,false,false,1,0);
}
}
//**************************************************************************************************************************************
//*****************************************************************************************//
void cut(String Start, String Ziel[max_read], char trenner ) {


  for (int x = 0; x < max_read; x++) {
    Ziel[x] = split(Start, trenner, x + 1);
    /*
    if (x == max_read - 1) {
      kontroll_key = txt[x];
   //   Serial.print( "Kontrollwert SD:");
   //   Serial.println( txt[x]);
    }*/
    if (x != max_read - 1) {
       
      Speicherwerte_Konfig[x] = Ziel[x].toInt();
    
      //Dump zur Hilfe
     // Serial.println( Speicherwerte_Konfig[x]);
    }
  }
}

//*****************************************************************************************//

String split(String s, char parser, int index) {
  String rs = "";
  int parserIndex = index;
  int parserCnt = 0;
  int rFromIndex = 0, rToIndex = -1;
  while (index >= parserCnt) {
    rFromIndex = rToIndex + 1;
    rToIndex = s.indexOf(parser, rFromIndex);
    if (index == parserCnt) {
      if (rToIndex == 0 || rToIndex == -1) return "";
      return s.substring(rFromIndex, rToIndex);
    } else parserCnt++;
  }
  return rs;
}
//*****************************************************************************************//

void read_konfig_out_of_string_light() {

Con_Name = basis[0];

  konfig_time = basis[1].toInt();
  
      //con_start_time=konfig_time+(2*86400); //für tests bei verschiedenen startwerten
      con_start_time=konfig_time;
      UTC =basis[2].toInt();
      //UNIX_korrektur = basis[3]*60; // ist nun festgesetzt
      anzahl_tage=basis[4].toInt();// minuswert nur zum testen von konfigdaten
      tagesdosis=basis[5].toInt();       
      Nanoclean_min_effekt=basis[17].toInt();
      Nanoclean_max_effekt=basis[18].toInt();
   
      Clean_per_day=basis[9].toInt(); 
      Clean_per_con=basis[8].toInt(); 
      Cleanray_min_effekt=basis[6].toInt();
      Cleanray_max_effekt=basis[7].toInt();
                           
      LifeCleaner_per_day=basis[12].toInt(); 
      Life_per_con=basis[11].toInt();    
      LifeCleaner_buffer=(basis[10].toInt()*3600);  //(XStunden *60Min*60Sekunden)        
             
      Blood_per_day=basis[16].toInt();
      Blood_per_con=basis[15].toInt();           
      Bloodclean_min_effekt=basis[13].toInt();
      Bloodclean_max_effekt=basis[14].toInt();
                   
      Nano_per_day=basis[20].toInt();
      Nano_per_con=basis[19].toInt(); 

                            
      Dekon_per_day=basis[24].toInt();                                
      Dekon_per_con=basis[23].toInt();                     
      Dekon_min_effekt=basis[21].toInt();
      Dekon_max_effekt=basis[22].toInt();
      
}
