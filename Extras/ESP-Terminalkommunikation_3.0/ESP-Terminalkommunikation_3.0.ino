#include <espnow.h>
#include "ESP8266WiFi.h"


char connection_select = 'x'; // für einleitung verbindung esp zu esp
char connection_select3 = 'y'; // verbindungen lösen
char connection_select2 = 'z'; // für einleitung verbindung esp zu seinem arduino wenn esp zu esp verbunden wurde
const int anzahl_verbindungen = 21;



uint8_t receiverAddress[anzahl_verbindungen][6] ={ 
                              {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},         //leer                0
                              {0x5C, 0xCF, 0x7F, 0x1A, 0x9E, 0xFB},         //Godzilla 1          1 
                              {0x40, 0x22, 0xD8, 0x95, 0x76, 0x6B},         //Terminal 2          2
                              {0x40, 0x22, 0xD8, 0x95, 0x76, 0xAB},         //Terminal 3          3
                              {0x40, 0x22, 0xD8, 0x95, 0x76, 0xFA},         //Terminal 4          4
                              {0x40, 0x22, 0xD8, 0x95, 0x77, 0x31},         //Terminal 5          5
                              {0x40, 0x22, 0xD8, 0x95, 0x77, 0x79},         //Terminal 6          6
                              {0x5C, 0xCF, 0x7F, 0x1A, 0x9F, 0xD2},         //Terminal 7          7
                              {0x5C, 0xCF, 0x7F, 0x1A, 0x9F, 0x39},         //Terminal 8          8
                              {0xD8, 0xBF, 0xC0, 0xFD, 0xA9, 0x0F},         //Godzilla_Slave 9    9 //wird neu ersetzt
                              
                              {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF},         //leer                10
                              {0xE0, 0x98, 0x06, 0x93, 0x6D, 0x23},         //ESP 11              11  
                              {0x2C, 0xF4, 0x32, 0x75, 0xE7, 0x6A},         //ESP 12              12
                              {0x84, 0xF3, 0xEB, 0x82, 0xFA, 0x62},         //ESP 13              13
                              {0xFC, 0xF5, 0xC4, 0x89, 0xDA, 0xF5},         //ESP 14              14
                              {0x84, 0xCC, 0xA8, 0x99, 0xB7, 0x1F},         //ESP 15              15
                              {0x8C, 0xCE, 0x4E, 0xC8, 0x92, 0x6B},         //ESP 16              16
                              {0x8C, 0xCE, 0x4E, 0xE1, 0xAC, 0x67},         //ESP 17              17
                              {0xB4, 0xE6, 0x2D, 0x3B, 0x32, 0x49},         //ESP 18              18
                              {0x50, 0x02, 0x91, 0xFB, 0x3A, 0x5A},         //ESP 19              19
                              
                              {0x40, 0x22, 0xD8, 0x95, 0x74, 0xBF}          //  x1 Reserve        20
                                                                     };  
bool verbindung =false;
int ziel=0;
char neue_verbindung[6];


typedef struct messageToBeSent {
    char text[200];
} messageToBeSent;


typedef struct receivedMessage {
    char text[200];   
} receivedMessage;


messageToBeSent myMessageToBeSent; 
receivedMessage myReceivedMessage; 

String myString="";
char char_read[200];

void messageSent(uint8_t *macAddr, uint8_t status) {
    
    if(status == 0){
  
    }
    else{
      Serial.println("nicht verbunden");
     //   Serial.print("MAC-Address: ");
     //   Serial.println(WiFi.macAddress());
    }
}

void messageReceived(uint8_t* macAddr, uint8_t* incomingData, uint8_t len){
    memcpy(&myReceivedMessage, incomingData, sizeof(myReceivedMessage));
  
  if( verbindung==false){
      
    uint8_t result = esp_now_add_peer(receiverAddress[ziel], ESP_NOW_ROLE_COMBO, 0, NULL, 0);
    if(result != 0){
        //Serial.println("hab mich nicht verbunden");
        //Serial.println();
    }
    else{
      //Serial.print("hab mich verbunden ");
      //Serial.println(ziel);
      //Serial.println(" ok");
  
    esp_now_send(receiverAddress[ziel], (uint8_t *) &connection_select2, sizeof(connection_select2));
      verbindung=true;
      // Serial.print("Eingang1: ");
      // Serial.println(myReceivedMessage.text);
      }
   }
   else{
    //Serial.print("Eingang2: ");
    Serial.println(myReceivedMessage.text);
   
   }
}

void setup(){
    Serial.begin(57600);
  

    WiFi.mode(WIFI_STA);
    
    if (esp_now_init() == 0) {
    //    Serial.println("ESPNow Init success");
    }
    else {
      //  Serial.println("ESPNow Init fail");
        return;
    }
    esp_now_set_self_role(ESP_NOW_ROLE_COMBO);

    esp_now_register_send_cb(messageSent);  
    esp_now_register_recv_cb(messageReceived); 

        Serial.print("MAC-Address: ");
        Serial.println(WiFi.macAddress());
   
}
 
void loop(){

   while (Serial.available() > 0) {
        
      myString=Serial.readStringUntil('\n'); // greif neuen string und leg ihn ab
      //Serial.println(myString);
      
      myString.toCharArray(char_read,200); // wandle string in char array
      
  if(char_read[0]==connection_select3&&verbindung==true){
    verbindung=false;
  }
  
  if(char_read[0]==connection_select&&verbindung==false){
        ziel=(((char_read[1]-'0')*10)+(char_read[2]-'0'))-10;
        myString.remove(0,3);
        //Serial.print("Verbindung:");Serial.println(ziel);
    
        
        myString.toCharArray(char_read,200); // wandle string in char array   
        
 
      
    uint8_t result = esp_now_add_peer(receiverAddress[ziel], ESP_NOW_ROLE_COMBO, 0, NULL, 0);
    if(result != 0){
        Serial.println("Failed to add peer");
        //Serial.println();
      }
      else{
      // Serial.print("peer to ");
      // Serial.print(ziel);
      // Serial.println(" ok");
      char_read[0]=connection_select2; //weiß nicht ob nötig
      memcpy(&myMessageToBeSent.text, (uint8_t *) &connection_select2, sizeof(connection_select2));
      esp_now_send(receiverAddress[ziel], (uint8_t *) &myMessageToBeSent, sizeof(myMessageToBeSent));
        verbindung=true;
        }

      }
  if(verbindung==true){
        memcpy(&myMessageToBeSent.text, char_read, sizeof(char_read));
    esp_now_send(receiverAddress[ziel], (uint8_t *) &myMessageToBeSent, sizeof(myMessageToBeSent));
    delay(50);
    }
  }
  while (Serial.read() > 0) {myString="";memset(char_read, 0, 200);}
}
