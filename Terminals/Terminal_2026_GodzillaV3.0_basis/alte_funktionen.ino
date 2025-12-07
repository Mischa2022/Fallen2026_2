/*
void initialisierung() {

  Serial.println( "Initialisierung");

  //keine SD-Karte
  if (!SD.begin(chipSelect)) {
    Serial.write("SD-Karte nicht ok");
    Serial.write('\n');delay(write_pause);
    
    while (1);
  }
  //------------------------------------------------
  else

  delay(50);

  //konfig ok
  if (SD.exists("konfig.txt")) {
    konfig_check = konfig_read();
    if (konfig_check == 1) {
      Serial.write("neue Konfig geladen");
      Serial.write('\n');delay(write_pause);
      save_konfig_to_eeprom();
      read_konfig_from_eeprom();
      SD.remove("konfig.txt");
     buzzer_play( 1,100);
    }
    //--------------------------------------------------------------
  //konfig nicht ok
    if (konfig_check == 0  ) {
      Serial.write("neue Konfig hat fehler");
      Serial.write('\n');delay(write_pause);
      read_konfig_from_eeprom();
      
      Serial.write("benutze alte Konfig");
      Serial.write('\n');delay(write_pause);
      SD.remove("konfig.txt");
      konfig_check=1;
      buzzer_play( 5,50);
    }
  }

  //konfig nicht vorhanden
      if (!SD.exists("konfig.txt")){

      read_konfig_from_eeprom();
     
      konfig_check=1;
      buzzer_play( 5,50);
}

  moduslog = SD.open("moduslog.txt");
                      if (moduslog) {
                        while (moduslog.available()) {
                          moduslog.seek(0);
                         modusbuffer[0] =moduslog.read()-'0'; 
                          modus=modusbuffer[0];
                         
                          lcd.setCursor(0, 0);
   if (modus==0){
    Serial.println("Godzilla");
   // lcd.print("  Mit PC verbunden  ");
  
    locked=false;
    //lcd.print("Godzilla");
    }    
   if (modus==1){
    
    Serial.println("Checkin");
     
   // lcd.print("  Checkinterminal   ");
    locked=false;
    }  
   if (modus==2){
    
    Serial.println("Buchung");
    
  //  lcd.print("  Buchungsterminal  ");
  //  lcd.setCursor(0, 1);
  //  lcd.print("      Blockiert     ");  
    locked=true;
    }     
                          moduslog.close();
                            
                          
                          }
                        
                        }
                       else {
                        modus=0;
                        myprint("moduslog.txt nicht vorhanden","","",true,true,false,1,port);
                      }
  

    

}
*/
//*****************************************************************************************//
/*
int konfig_read() {

  //erstellen SD konfig read string
  konfigFile = SD.open("konfig.txt", FILE_READ);

  if (konfigFile) {

    while (konfigFile.available() ) {

      text = text + (char)konfigFile.read();

      if ( text == '\n') {

        konfigFile.close();
      }
    }
  }
  // aufteilen string in einzelne strings
  cut(text, txt, '*');

  //kontrollwert erstellen und mit kontrollwert auf SD vergleichen

  for (int x = 0; x < max_read - 1; x++) {
    kontrolle = kontrolle + txt[x];
  }
 // Serial.print( "Kontrollwert addiert:");
 // Serial.println( kontrolle);

  char kontrollwert[kontrolle.length() + 1];
  kontrolle.toCharArray(kontrollwert, kontrolle.length() + 1);

  unsigned char* hash = MD5::make_hash(kontrollwert);
  char *kontrollwert_md5 = MD5::make_digest(hash, 16);
  free(hash);
 // Serial.print( "Kontrollwert berechnet: ");
 // Serial.println( kontrollwert_md5);

  String kontrollwert_md5_str = String(kontrollwert_md5);
  String kontroll_key_str = String(kontroll_key);

  kontroll_key_str.remove(kontrollwert_md5_str.length());

  if (kontrollwert_md5_str == kontroll_key_str) {
    return 1;
  }
  else return 0;

  free(kontrollwert_md5);


}
*/
//*****************************************************************************************//
/*
void save_konfig_to_eeprom() {

unsigned long timeA[5];
unsigned long timeB[5];

  char Con_title[txt[0].length() + 1];
  txt[0].toCharArray(Con_title, txt[0].length() + 1); //Array fuer den Con-Namen (11)

  timeA[0] = Speicherwerte_Konfig[1] % 256;
  timeB[0] = timeA[0];
  timeA[1] = (Speicherwerte_Konfig[1] - timeB[0]) / 256;
  timeB[1] = timeA[1] % 256;
  timeA[2] = (Speicherwerte_Konfig[1] - timeB[1]) / 256 / 256;
  timeB[2] = timeA[2] % 256;
  timeA[3] = (Speicherwerte_Konfig[1] - timeB[2]) / 256 / 256 / 256;
  timeB[3] = timeA[3] % 256;
  timeA[4] = (Speicherwerte_Konfig[1] - timeB[3]) / 256 / 256 / 256 / 256;
  timeB[4] = timeA[4] % 256;

  //EEPROM 0-10 = Eventname
  for (int x = 0; x <= 10; x++) {
    EEPROM.update(x, Con_title[x] );
    delay(5);
  }

  //EEPROM 11-15 = Zeit
  EEPROM.update(11, timeB[0]);
  EEPROM.update(12, timeB[1]);
  EEPROM.update(13, timeB[2]);
  EEPROM.update(14, timeB[3]);
  EEPROM.update(15, timeB[4]);

//EEPROM 16-39 =Werte

//17 Korrektur ist ein Faktor ( 60*x min ( normal= 60))
//24 ist Lifecleanereffekt, Wert als Stunden angeben 1= 1Stunde, 2=2 Stunden usw. also x*3600 um auf sekunden zu kommen
for (int z = 16; z <= 39; z++) {
  EEPROM.update(z, Speicherwerte_Konfig[z-14]);
  delay(5);
}
}
*/
//*****************************************************************************************//
/*
void read_konfig_from_eeprom() {

unsigned long timeC[5];
unsigned long timeD[5];

for (int z = 0; z <=10; z++) {
  Puffer[z]=EEPROM.read(z);
           }
           
Con_Name = String(Puffer);

  timeC[4] = EEPROM.read(15);
  timeC[3] = EEPROM.read(14);
  timeC[2] = EEPROM.read(13);
  timeC[1] = EEPROM.read(12);
  timeC[0] = EEPROM.read(11);

  timeD[4] = ((timeC[4] * 256));
  timeD[3] = ((timeD[4] * 256) + timeC[3]);
  timeD[2] = ((timeD[3] * 256) + timeC[2]);
  timeD[1] = ((timeD[2] * 256) + timeC[1]);
  timeD[0] = ((timeD[1] * 256) + timeC[0]);
  
  konfig_time = timeD[0];

 for (int y = 16; y < 39; y++) {
    Speicherwerte_Konfigread[y] = EEPROM.read(y);
    delay(10);
  }
    //allgemeine Konfig_eeprom
      //con_start_time=konfig_time+(2*86400); //fuer tests bei verschiedenen startwerten
      con_start_time=konfig_time;
      UTC =Speicherwerte_Konfigread[16];
     // UNIX_korrektur = Speicherwerte_Konfigread[17]*60; // ist nun festgesetzt
      anzahl_tage=Speicherwerte_Konfigread[18];// minuswert nur zum testen von konfigdaten
      tagesdosis=Speicherwerte_Konfigread[19]; 

      // Medi Konfig_eeprom
      
      Clean_per_day=Speicherwerte_Konfigread[23]; 
      Clean_per_con=Speicherwerte_Konfigread[22]; 
      Cleanray_min_effekt=Speicherwerte_Konfigread[20];
      Cleanray_max_effekt=Speicherwerte_Konfigread[21];
                           
      LifeCleaner_per_day=Speicherwerte_Konfigread[26]; 
      Life_per_con=Speicherwerte_Konfigread[25];    
      LifeCleaner_buffer=(Speicherwerte_Konfigread[24]*3600);  //(XStunden *60Min*60Sekunden)        
             
      Blood_per_day=Speicherwerte_Konfigread[30];
      Blood_per_con=Speicherwerte_Konfigread[29];           
      Bloodclean_min_effekt=Speicherwerte_Konfigread[27];
      Bloodclean_max_effekt=Speicherwerte_Konfigread[28];
                   
      Nano_per_day=Speicherwerte_Konfigread[34];
      Nano_per_con=Speicherwerte_Konfigread[33]; 
      Nanoclean_min_effekt=Speicherwerte_Konfigread[31];
      Nanoclean_max_effekt=Speicherwerte_Konfigread[32];
                            
      Dekon_per_day=Speicherwerte_Konfigread[38];                                
      Dekon_per_con=Speicherwerte_Konfigread[37];                     
      Dekon_min_effekt=Speicherwerte_Konfigread[35];
      Dekon_max_effekt=Speicherwerte_Konfigread[36];
      
 //   Serial.write("EEPROM_read: done");
}
*/
//*****************************************************************************************//
/*
int serial_print_konfig(){
    char* bereiche[] {
   "Con-Name: ", "Con-Start:", "UTC:", "Korrektur:", "Anzahl Tage:", "Tagesdosis RAY:",
   "Cleanray Effekt in Ray/Tag(min):", "Cleanray Effekt in Ray/Tag(max):", "Anzahl Cleanray/ Con:", "Anzahl Cleanray/ Tag:",
   "Lifecleaner Effekt in Stunden :", "Anzahl Lifecleaner/ Con:", "Anzahl Lifecleaner/ Tag:",
   "Bloodclean Effekt in Ray/Tag(min):", "Bloodclean Effekt in Ray/Tag(max):", "Anzahl Bloodclean/ Con:", "Anzahl Bloodclean/ Tag:",
   "Nanoclean Effekt in Ray/Tag(min):", "Nanoclean Effekt in Ray/Tag(max):", "Anzahl Nanoclean/ Con:", "Anzahl Nanoclean/ Tag:",
   "Dekon Effekt in Ray/Tag(min):", "Dekon Effekt in Ray/Tag(max):", "Anzahl Dekon/ Con:", "Anzahl Dekon/ Tag:"
  };
  
unsigned long timeC[5];
unsigned long timeD[5];

//Serial.write("aktuelle konfig:");
//Serial.write('\n');delay(write_pause);
myprint("aktuelle konfig:","","",true,true,false,1,port);  

for (int z = 0; z <=10; z++) {
  Puffer[z]=EEPROM.read(z);
           }
           
Con_Name = String(Puffer);
//      Serial.print( bereiche[0]);
//      Serial.print( " ");
//      Serial.println( Con_Name);
myprint(bereiche[0],Con_Name,"",true,true,false,1,port);  

  timeC[4] = EEPROM.read(15);
  timeC[3] = EEPROM.read(14);
  timeC[2] = EEPROM.read(13);
  timeC[1] = EEPROM.read(12);
  timeC[0] = EEPROM.read(11);

  timeD[4] = ((timeC[4] * 256));
  timeD[3] = ((timeD[4] * 256) + timeC[3]);
  timeD[2] = ((timeD[3] * 256) + timeC[2]);
  timeD[1] = ((timeD[2] * 256) + timeC[1]);
  timeD[0] = ((timeD[1] * 256) + timeC[0]);
  
  konfig_time = timeD[0];
  
    //  Serial.print( bereiche[1]);
    //  Serial.print( " ");
    //  Serial.println( konfig_time);
 myprint(bereiche[1],"",konfig_time,true,true,false,1,port);       
 
 for (int y = 16; y < 39; y++) {
    Speicherwerte_Konfigread[y] = EEPROM.read(y);
    
          //Dump zur Hilfe
     // Serial.print( bereiche[y-14]);
     // Serial.print( " ");
     // Serial.println( Speicherwerte_Konfigread[y]);
       myprint(bereiche[y-14],"",Speicherwerte_Konfigread[y],true,true,false,1,port);  
      delay(10);
  }
  Serial.println();

}
*/

//*****************************************************************************************//
/*
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
                                      
}
*/
//*****************************************************************************************//
/*
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
 if( aktuell_time<(con_start_time-432000)||aktuell_time > 1893452460){
    Serial.write("Uhr steht auf:");
    Serial.print(abgleichwert);
    Serial.write('\n');delay(write_pause);
    Serial.write("Uhr ist nicht gestellt");
    Serial.write('\n');delay(write_pause);
    Serial.write("Bitte gib eine Zeit in folgenden Format ein:");
    Serial.write('\n');delay(write_pause);
    Serial.write("Stunden:Minuten:Sekunden-Tag.Monat.Jahr:UTC");
    Serial.write('\n');delay(write_pause);
    Serial.write("SS:MM:SS-TT.MM.JJJJ:U"); 
    Serial.write('\n');delay(write_pause);
    Serial.write("oder als UNIX mit anfuehrendem j"); 
    Serial.write('\n');delay(write_pause);
    
while(!fertig){
  if (Serial.available() > 0) {
    
    String eingabeString = Serial.readStringUntil('\n');

    //Serial.write("Eingegeben: ");
    //Serial.println(eingabeString);
    eingabeString.toCharArray(Zeit,22);
    
 if(Zeit[0]=='j'){
      unsigned long timex=0;

      for(int x=1;x<11;x++){
      timex=timex*10+(Zeit[x]-'0');
      
      delay(10);
      }
      //Serial.println(timex);
      
            rtc_stellen(hour(timex), minute(timex), second(timex),day(timex),month(timex), year(timex),  UTC);
    delay(100);
    t = rtc.now(); 
  
  
        Serial.print(t.hour(), DEC);
        Serial.print(':');
        Serial.print(t.minute(), DEC);
        Serial.print(':');
        Serial.print(t.second(), DEC); 
        Serial.print("-");
        Serial.print(t.day(), DEC);
        Serial.print('.');
        Serial.print(t.month(), DEC);
        Serial.print('.');
        Serial.print(t.year(), DEC);
        Serial.print(':');
        Serial.println(UTC);
        Serial.print("Zeit jetzt:");Serial.println(t.unixtime());
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Uhr gestellt");        
        t = rtc.now();
        
        delay(2000);

        lcd.clear();
        fertig= true;
      }
  else if(Zeit[2]!=':'||Zeit[5]!=':'||Zeit[8]!='-'||Zeit[11]!='.'||Zeit[14]!='.'||Zeit[19]!=':'){
        Serial.write("Falsche Eingabe");
        Serial.write('\n');delay(write_pause);
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
    
         rtc_stellen(Stunden,Minuten,Sekunden,Tag,Monat,Jahr,UTC2);
         delay(50);
         Serial.write("Uhr ist gestellt");
         Serial.write('\n');delay(write_pause);
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
      Serial.write('\n');delay(write_pause);
      Serial.write("Momentane Zeit Unix: ");
      Serial.print(aktuell_time); // Ohne UTC da allgemein gueltige Zeitangabe
      Serial.write('\n');delay(write_pause);
      Serial.write("Con_Start:");
      Serial.print(con_start_time);
      Serial.write('\n');delay(write_pause);
       if(aktuell_time>con_start_time+rest_time){
      Serial.write("vergangene Sekunden ab Anreise:");
      Serial.print(aktuell_time-(con_start_time+rest_time));
       Serial.write(" | vergangene Stunden ab Anreise:");
      Serial.print((aktuell_time-(con_start_time+rest_time))/3600);
      Serial.write('\n');delay(write_pause);
       }
       else{Serial.print("Vor Constart");
      Serial.write('\n');delay(write_pause);
      }
      delay(50);
      con_tag_bestimmen(aktuell_time,con_start_time,rest_time);
      Serial.write("Contag:");
      Serial.print(con_tag);
      Serial.write('\n');delay(write_pause);
 }
 else{
      //zum Aktualisieren der Zeitwerte hier nochmal
      t = rtc.now();
      aktuell_time=t.unixtime();
     
      rest_time=86400- ((con_start_time+(UTC*UNIX_korrektur))%86400); 
      a_t_korrektur=aktuell_time+(UTC*3600);
                                                                  
      Serial.printf("Momentane Zeit: %4d-%02d-%02d %02d:%02d:%02d", year(a_t_korrektur), month(a_t_korrektur), day(a_t_korrektur), hour(a_t_korrektur), minute(a_t_korrektur), second(a_t_korrektur));
      Serial.println();
      Serial.write("Momentane Zeit Unix: ");
      Serial.print(aktuell_time); // Ohne UTC da allgemein gueltige Zeitangabe
      Serial.write('\n');delay(write_pause);
      Serial.write("Con_Start:");
      Serial.print(con_start_time);
      Serial.write('\n');delay(write_pause);
      if(aktuell_time>con_start_time+rest_time){
      Serial.write("vergangene Sekunden ab Anreise:");
      Serial.print(aktuell_time-(con_start_time+rest_time));
      Serial.write(" | vergangene Stunden ab Anreise:");
      Serial.print((aktuell_time-(con_start_time+rest_time))/3600);
      Serial.write('\n');delay(write_pause);
      }
      else{Serial.print("Vor Constart");
      Serial.write('\n');delay(write_pause);
      }
      delay(50);
      con_tag_bestimmen(aktuell_time,con_start_time,rest_time);
      Serial.write("Contag:");
      Serial.print(con_tag);
      Serial.write('\n');delay(write_pause);
    }
}*/
//*****************************************************************************************//
/*
//**************************************************************************************************************************************
bool tagabgleich(int vergleich,unsigned long variable){

int tag;

if(variable<con_start_time){
  if(variable==0){tag=-1;}else{tag=0;}
  }//"0" wuerde bedeuten, dass am Anreisetag leere Werte gegen das Limit laufen, was nicht richtig ist

if(variable>con_start_time&&variable<=con_start_time+rest_time){
  tag=1;
  }// 1 ist richtig, damit medibuchungen theoretisch bei anreise moeglich waeren aber dann gegen das limit am 1 spieltag laufen

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
if(variable>=con_start_time+rest_time+1+(6*86400)&&variable<con_start_time+rest_time+(7*86400)){
  tag=7;
  }
if(variable>=con_start_time+rest_time+1+(7*86400)&&variable<con_start_time+rest_time+(8*86400)){
  tag=8;
  }
if(variable>=con_start_time+rest_time+1+(8*86400)&&variable<con_start_time+rest_time+(9*86400)){
  tag=9;
  }
if(variable>=con_start_time+rest_time+1+(9*86400)&&variable<con_start_time+rest_time+(10*86400)){
  tag=10;
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
*/
//**************************************************************************************************************************************

/*bool tagabgleich(int vergleich,unsigned long variable){ //neu
wdt_reset();
int tag;
int faktor=1
;
if(variable<con_start_time||variable<con_start_time+rest_time){
  if(variable==0){tag=-1;}else{tag=0;}
  }//"0" wuerde bedeuten, dass am Anreisetag leere Werte gegen das Limit laufen, was nicht richtig ist

else if(variable>=con_start_time+rest_time+1+(anzahl_tage*86400)+1){
  tag=99;
  }

else{
  while(1){  
  if(variable>=con_start_time+rest_time+1+((faktor-1)*86400)&&variable<con_start_time+rest_time+(faktor*86400)){
    tag=faktor;
    return tag;  
    }
  else{faktor++;}
  }
}
  
  
if(tag==vergleich){
  return true;
  }
if(tag!=vergleich){
  return false;
  }
}
*/
