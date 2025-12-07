int rtc_stellen(int Stunden,int Minuten,int Sekunden,int Tag, int Monat,long Jahr,int UTC){

//rtc.writeSqwPinMode(PCF8563_SquareWave1HZ);              
rtc.adjust(DateTime(Jahr, Monat, Tag, Stunden-UTC,Minuten,Sekunden));
}

//*****************************************************************************************//
void serial_monitor(){
myGLCD.setFont(BigFont);

       
    if(verbindung==false){
       
      myGLCD.setFont(BigFont);
      myGLCD.setColor(VGA_BLACK);
      //Aufgabenzeile  
      if(konfig!=true){
      button_paint( 120,33,359,22,VGA_SILVER,"",1);
      }else{
        myGLCD.setColor(VGA_BLACK);
        myGLCD.fillRoundRect (120, 33,479,55);
      }
      //Serialmonitor
      button_paint( 120,56,359,474,VGA_LIME,"",1);

      }
      
    if(verbindung==true){
          myGLCD.setFont(BigFont);
      myGLCD.setColor(VGA_BLACK);
      //Aufgabenzeile  
      if(konfig!=true){
      button_paint( 120,33,359,22,VGA_SILVER,"",1);
      }else{
        myGLCD.setColor(VGA_BLACK);
        myGLCD.fillRoundRect (120, 33,479,55);
      }
      //Serialmonitor
      button_paint( 120,56,359,474,VGA_BLACK,"",1);

      }
      
      pos_counter=0;
      posy=58;
      

        
}

//*****************************************************************************************//
void start_screen(int u){
int x;
int y;


for(int z=0;z<=u;z++){
  x=random(1,300);
  y=random(1,700)+50;
  
  myGLCD.drawBitmap(x,y,148,50,logo);
 // myGLCD.drawBitmap(x,y,100,98,godzilla);
  delay(1000); 

  }
}

//*****************************************************************************************//
/*
void cut(String Start, String Ziel[26], char trenner ) {


  for (int x = 0; x < 26; x++) {
    Ziel[x] = split(Start, trenner, x + 1);
    /*
    if (x == max_read - 1) {
      kontroll_key = txt[x];
   //   Serial.print( "Kontrollwert SD:");
   //   Serial.println( txt[x]);
    }
    if (x != 26- 1) {
       
      Speicherwerte_Konfig[x] = Ziel[x].toInt();
    
      //Dump zur Hilfe
     // Serial.println( Speicherwerte_Konfig[x]);
    }
  }
}
*/
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
/*void read_konfig_out_of_string(String basis[]) {

konfigwerte[0] = basis[0];
delay(2);
  konfigwerte[1] = basis[1].toInt();
  
      //con_start_time=konfig_time+(2*86400); //fuer tests bei verschiedenen startwerten
    //  con_start_time=konfig_time;
      delay(2);
     konfigwerte[2] =basis[2].toInt();
      konfigwerte[3] = basis[3]; // ist nun festgesetzt
      konfigwerte[4]=basis[4].toInt();// minuswert nur zum testen von konfigdaten
      delay(2);
      konfigwerte[5]=basis[5].toInt(); 
      delay(2);
      //con_end_time=con_start_time+(86400*anzahl_tage);
      
      
      konfigwerte[6]=basis[6].toInt();
      delay(2);
      konfigwerte[7]=basis[7].toInt();
      delay(2);
      konfigwerte[8]=basis[8].toInt(); 
      delay(2);
      konfigwerte[9]=basis[9].toInt(); 
      delay(2);
                           
      konfigwerte[10]=(basis[10].toInt());  //(XStunden *60Min*60Sekunden)        
      delay(2);
      konfigwerte[11]=basis[11].toInt();       
      delay(2);
      konfigwerte[12]=basis[12].toInt(); 
      delay(2); 
      konfigwerte[13]=basis[13].toInt();
      delay(2);
      konfigwerte[14]=basis[14].toInt();
      delay(2);
      konfigwerte[15]=basis[15].toInt();
      delay(2);             
      konfigwerte[16]=basis[16].toInt();
      delay(2);
      
      konfigwerte[17]=basis[17].toInt();
      delay(2);
      konfigwerte[18]=basis[18].toInt();
      delay(2);
      konfigwerte[19]=basis[19].toInt();    
      delay(2);                  
      konfigwerte[20]=basis[20].toInt();                                
      delay(2);
                           
      konfigwerte[21]=basis[21].toInt();
      delay(2);
      konfigwerte[22]=basis[22].toInt();
      delay(2);
      konfigwerte[23]=basis[23].toInt();
      delay(2);
      konfigwerte[24]=basis[24].toInt();
      //  Serial.println(con_start_time);
      for(int x=0;x<25;x++){
     //  Serial.print(x);Serial.print(":"); Serial.println(basis[x]);delay(50);
       Serial.print(x);Serial.print(":"); Serial.println(konfigwerte[x]);delay(50);
      }
      
}*/
//*****************************************************************************************//
int bool_anzeigen(){
  
    Serial.print("admin1: "); Serial.println(admin1);
       Serial.print("menue: "); Serial.println( menue);
         Serial.print("medis: "); Serial.println(medis);
         Serial.print("com: "); Serial.println( com);
          Serial.print("typus: "); Serial.println( typus);
           Serial.print("ray: "); Serial.println( ray);
           Serial.print("life: "); Serial.println( life);
            Serial.print("rechte: "); Serial.println( rechte);
             Serial.print("modus: "); Serial.println( modus);
              Serial.print("connection: "); Serial.println( connection);
               Serial.print("konfig: "); Serial.println( konfig);
               Serial.print("zeit: "); Serial.println( zeit);
}




//*****************************************************************************************//
void button_paint(int start_h,int start_v, int breite,int hoehe,char*Farbe,char*sortiment,bool black){
  
  myGLCD.setBackColor(Farbe);
  myGLCD.setColor(Farbe);
  myGLCD.fillRoundRect (start_h, start_v, (start_h+breite),(start_v+hoehe));
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (start_h, start_v, (start_h+breite),(start_v+hoehe));
  if(black==true){myGLCD.setColor(VGA_BLACK);}else{myGLCD.setColor(VGA_WHITE);}
  myGLCD.print(sortiment, start_h+5,start_v+(hoehe/4)); 
  
}

//*****************************************************************************************//
void button_paint2(int start_h,int start_v, int breite,int hoehe,char*Farbe,String sortiment,bool black){
  
  myGLCD.setBackColor(Farbe);
  myGLCD.setColor(Farbe);
  myGLCD.fillRoundRect (start_h, start_v, (start_h+breite),(start_v+hoehe));
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (start_h, start_v, (start_h+breite),(start_v+hoehe));
  if(black==true){myGLCD.setColor(VGA_BLACK);}else{myGLCD.setColor(VGA_WHITE);}
  myGLCD.print(sortiment, start_h+5,start_v+(hoehe/4)); 
  
}

//*****************************************************************************************//
void ausgabe_paint(int start_h,int start_v, int breite,int hoehe,char*Farbe,unsigned long ausgabe,char*Einheit){
  myGLCD.setBackColor(Farbe);
  myGLCD.setColor(Farbe);
  myGLCD.fillRoundRect (start_h, start_v, (start_h+breite),(start_v+hoehe));
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (start_h, start_v, (start_h+breite),(start_v+hoehe));
  myGLCD.printNumI(ausgabe, start_h+5,start_v+(hoehe/4)); 
  if(Einheit!=""){
    myGLCD.drawRoundRect (120, 530, 479, 560);
        myGLCD.print(Einheit, start_h+180,start_v+(hoehe/4)); 
  }
}  
