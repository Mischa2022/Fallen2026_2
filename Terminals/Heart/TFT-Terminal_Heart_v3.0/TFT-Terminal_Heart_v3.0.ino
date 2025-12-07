#include <UTFT.h>
#include <URTouch.h>
#include <TimeLib.h>
#include <RTClib.h>
#include <Wire.h>
#include <SPI.h>

//Aufbau
/*
 * Mega mit ESp wird am TFT (tft-arduino)direkt angeschlossen und kommuniziert in Richtung ESP über Serial3
 * tft-arduino kommuniziert mit Terminal-arduino (worker-arduino) per Serial2
 * Serial per PC kann am tft-arduino benutzt werden, wird dann aber direkt an Serial2 weitergeleitet
 */


/**************************************************************************************************************/
//TFT

UTFT    myGLCD(SSD1963_800ALT,38,39,40,41);
URTouch  myTouch( 6, 5, 4, 3, 2);

extern uint8_t BigFont[];
extern uint8_t SmallFont[];
int x, y; //für toucherkennung
int posy=58; // start der bildschirmausgabe
int pos_counter=0; // zum springen in die nächste zeile
int max_read=48;


/**************************************************************************************************************/
//RTC

RTC_DS3231 rtc;
DateTime t;
String myTime="";
unsigned long UNIX_korrektur=3600;
unsigned long aktuell_time;
unsigned long timer=0;            //zwischenablage für unixtime zum übertragen
int UTC=0;  //für RTC
int stu,minu,sek,tag,mona,jahr;

/**************************************************************************************************************/
//bool für menübaum


//bool ebene2 menueebenen um zu entscheiden ob naechste ebene angezeigt werden soll
bool menue= false;
bool medis= false;
bool admin1= false;
bool com= false;

//bool ebene3 menueebenen um zu entscheiden ob naechste ebene angezeigt werden soll
bool typus= false;
bool ray= false;
bool life=false;
bool rechte=false;

//rechte bool writing
bool Nano =false;
bool Blood= false;
bool Clean= false;
bool Life =false;
bool Dekon =false;

//rechte bool display
bool Nano2 =false;
bool Blood2= false;
bool Clean2= false;
bool Life2 =false;
bool Dekon2 =false;
bool Update2=false;
bool Draw2=false;

//menue bools letzte ebene
bool modus= false;
bool connection=false;
bool konfig=false;//konfig bearbeiten
bool verbindung= false;   // um anzuzeigen das man mit einem gerät verbunden ist
bool zeit=false;

/**************************************************************************************************************/
//übergabewerte

char*msg="";
char*msg2="";
unsigned long msg3=0;
unsigned long wert=0;           //übertragungswert, buffer für ray, lifecleanereffekt usw
unsigned long wert_verbindung; //für anzeige, mit welchem esp man verbunden ist
/**************************************************************************************************************/
//bilder

extern unsigned int logo[];     // für LI-logo beim start
extern unsigned int godzilla[]; 
extern unsigned int vaultboy3[];
extern unsigned int Logo2[];

unsigned long current_millis;   //für bildschirmupdate
unsigned long last_millis;      //für bildschirmupdate
long warten=90000;              //für bildschirmupdate
int funktion=0;
bool on=false;
bool start_malen=true;


/**************************************************************************************************************/
//Beschriftungen  //dublikate entfernen

char* head[]{"Menue","Medis","Admin"," COM"};
char* med[]{"Dekon","Blood","Nano","Life","Clean","+date","Draw"};
char* med2[]{"Dekon","Blutwaesche","Nanoclean","Lifecleaner","Cleanray","Update","Drawback"};
char*admin[]{"Typus","Ray","Life","right"};
char*admin2[]{"Typus aendern   ","Raymanipulation ","Lifecleaneffekt ","Rechte          "};
char*com1[]{"Mode","cont","M.del","M.Log","Clock","Csend","Ksend","Konfi"};
char*com2[]{ "Modus aendern   ","Verbinden       ","Medilog loeschen","Show Medilog    ","Uhranzeigen     ","Uhruebertragen  ","Konfigbearbeiten"};
char*menue1[]{"Alyse","Chkin","Reset"};                                                                                        
char*menue2[]{"Analyse","Checkin","Reset"};
char*typus1[]{" Bunker"," Mutant"," Mensch"};
char*zahlen[]{" 0"," 1"," 2"," 3"," 4"," 5"," 6"," 7"," 8"," 9"," 10"};
char*befehl[]{" Clear"," Enter"," Write"};
char* typen[]{" N"," B"," C"," L"," D"};
char* mode[]{"Godzilla"," Buchung"," Checkin"};
char*farben[]{"gruen"," gelb"," rot"};
char* titel[]{  "Mensch         ","Mutant         ","Bunkerbewohner ",
                "Godzilla       ","Buchung        ","Checkin        ",
                "ray gruen rand ","ray gelb  rand ","ray rot   rand ","ray schreiben  ",
                "verbunden      ","Uhrstellen     ","Konfig stellen "
                };
                
/**************************************************************************************************************/
//Positionen

int b_h[4][2]{  {10,10},  {130,10}, {250,10}, {370,10}
              };  //head (Menue,Medis,Admin,Com)

int b_r[5][2]{  {120,570},  {192,570}, {264,570}, {336,570},{408,570}  
              };//rechte

int b_s[10][2]{{10,90 },{10,170},{10,250},{10,330},{10,410},{10,490},{10,570},{10,650},{10,730},{10,810}  }; //Selector

int b_k[10][2]{{10,40 },{10,100},{10,160},{10,220},{10,280},{10,340},{10,400},{10,460},{10,520},{10,580}  }; //konfig
              
int b_c[5][2]{  {120,570},{310,570},{120,660},{120,710},{310,710} };//commands (enter, write, clear, große buttons
                
int b_n[10][2]{   {120,570},{190,570},{260,570},{330,570},{400,570},{120,640},{190,640},{260,640},{330,640},{400,640} };// zahlen

/**************************************************************************************************************/
//Konfig

//String basis_konfig ="*FALLEN2034*1710925200*0*60*5*48*30*30*6*6*24*5*1*20*20*6*6*70*70*2*2*10*10*6*6*";
String neue_konfig;// nach bearbeiten zum senden an worker
String konfig_read1;
String konfig_read2;
String Con_Name="";
String konfigwerte[26];
String Einh[]{"min","max","/con","/tag","Std"};
//String konfigwerte2[26];
char* konfi2[]{"Con","Start","Tage","Dosis","Clean","Life","Blood","Nano","Dekon",""};
//unsigned long Speicherwerte_Konfig [26];//ablage für cut
int konfig_wert=-1;
int stern=0;
bool konfig0[25];

/**************************************************************************************************************/
//Reset Worker
int reset_Pin =A7;

/**************************************************************************************************************/
void setup()
{
  Wire.begin();    
  rtc.begin();
  SPI.begin();
  randomSeed(analogRead(0));
  // Initial setup
  //Serial ist für eingaben an den tft arduino gedacht, die dann zum worker geleitet werden
  //Serial2 ist für kommunikation von tft-arduino mit worker-arduino
  //Serial3 ist der tft-arduino zu seinem esp. also entweder befehle durch button raus oder antworten vom esp auf display
  
  Serial.begin(57600); //kommunikation eingang von pc über tft-arduino direkt an worker-arduino, keine ausgabe über Serial der antwort
  Serial2.begin(57600);//kommunikation eingang/ausgang tft-arduino direkt an worker-arduino, antworten gehen direkt auf tft
  Serial3.begin(57600); //kommunikation vom tft-arduino zum esp. antworten gehen auf tft
delay(500);

    

for(int x=0;x<25;x++){
                    
                   konfig0[x]=false;
                  }

        
  myGLCD.InitLCD(PORTRAIT);
  myGLCD.clrScr();

  myTouch.InitTouch(PORTRAIT);
  myTouch.setPrecision(PREC_HI);

pinMode(reset_Pin, OUTPUT);
digitalWrite(reset_Pin, LOW);
delay(1000);
digitalWrite(reset_Pin, HIGH);

 t = rtc.now();    
aktuell_time=t.unixtime();

      Serial.println("Terminal ");
      Serial.printf("Momentane Zeit: %4d-%02d-%02d %02d:%02d:%02d", year(aktuell_time), month(aktuell_time), day(aktuell_time), hour(aktuell_time), minute(aktuell_time), second(aktuell_time));
      Serial.write('\n');delay(50);
      Serial.write("Momentane Zeit Unix: ");
      Serial.print(aktuell_time); // Ohne UTC da allgemein gueltige Zeitangabe
      Serial.write('\n');delay(50);


}

void loop(){
 incoming_reading();
  if(on==false){ 
    
    myGLCD.clrScr();
    start_screen(0);
    start_malen=true;
    
    if(funktion==2){
      myGLCD.setFont(BigFont);
      button_paint(100,30,300,50,VGA_SILVER,"    BLOCKIERT",1);
      myGLCD.setFont(SmallFont);
      delay(1000);
      }
    }
  else{  
    if(start_malen==true){
 
      myGLCD.clrScr();
      serial_monitor();
      draw_ebene(funktion);
      
      start_malen=false;
    }
   current_millis=millis();

if(current_millis> last_millis+warten&&konfig!=true){
    //Serialmonitor
serial_monitor();
//serialmonitor leeren

  myGLCD.setColor(VGA_BLACK);
    stern=0;
    pos_counter=0;
    posy=58;
    last_millis=current_millis;
}
 
    incoming_reading();

   if (myTouch.dataAvailable()){
      last_millis= current_millis;
      myTouch.read();
      x=myTouch.getX();
      y=myTouch.getY();
     // Serial.print("X:");Serial.print(x);Serial.print(" | Y:");Serial.println(y);
      pushButtons(x,y,funktion);
      delay(100);
    }
  }
}
