//watchdog_read
#include <Arduino.h>
#include <U8g2lib.h>
#include <SoftwareSerial.h>
#include <Wire.h>

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R2, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ SCL, /* data=*/ SDA);   // pin remapping with ESP8266 HW I2C

//MP3
#define ARDUINO_RX 3  
#define ARDUINO_TX 5  

SoftwareSerial mp3(ARDUINO_RX, ARDUINO_TX);
static int8_t Send_buf[8] = {0}; 
static uint8_t ansbuf[10] = {0}; 
/************ Command byte **************************/
#define CMD_NEXT_SONG     0X01  // Play next song.
#define CMD_PREV_SONG     0X02  // Play previous song.
#define CMD_PLAY_W_INDEX  0X03
#define CMD_VOLUME_UP     0X04
#define CMD_VOLUME_DOWN   0X05
#define CMD_SET_VOLUME    0X06
#define CMD_SEL_DEV 0X09 //SELECT STORAGE DEVICE, DATA IS REQUIRED
#define DEV_TF 0X02 //HELLO,IM THE DATA REQUIRED

#define anzahl_werte2 11
unsigned long wert2=0;
String read_String2 = "";
char char_read2[anzahl_werte2];
int counter2=0;
int port2= 0;
int werte2[anzahl_werte2];
bool stringComplete2 = false; 
bool meldung=false;

//watchdog
unsigned long ziel_longwtd=0;
unsigned long aktuelleMillis;
unsigned long vergangeneMillis = 0;  

char ziel_charwtd=' ';       
int reset_Pin =A3; //pin der reset auslöst
int input_Pin=6; //für manuellen reset
bool button=0;  //state für manueller reset
int anzahl_reset=0;

int warnung=3;
int reset_timer=30;


void setup() {
  mp3.begin(9600);
  delay(500);
  sendCommand(CMD_SEL_DEV, DEV_TF);
  sendCommand(CMD_SET_VOLUME, 0x01E); //laut
u8g2.begin();
pinMode(reset_Pin, OUTPUT);
pinMode(input_Pin, INPUT_PULLUP);
digitalWrite(reset_Pin, HIGH);
digitalWrite(input_Pin, HIGH);

Serial.begin(57600); 

}

void loop() {
aktuelleMillis = millis();
button=digitalRead(input_Pin);


if(button==0){ //manueller Reset/ Entstörung
   
    digitalWrite(reset_Pin, LOW);
    delay(1000);
    digitalWrite(reset_Pin, HIGH);
    meldung=false;
    anzahl_reset=0;
    //vergangeneMillis =0;
    
  }
  else{
watchdog(reset_timer*1000);
  }
}
