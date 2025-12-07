      

void button_press(int start_h,int start_v, int breite,int hoehe,char*Farbe,int bool_veraenderung,char*Ausgabe,char*nachricht,unsigned long ausgabe){
  

      if((x>=start_h-5&&x<start_h+breite+5)&&(y>=start_v-5&&y<start_v+hoehe+5)){
        Serial.println(bool_veraenderung);
        //serial_monitor();
        
        msg2=nachricht;
        msg=Ausgabe;
        wert=ausgabe;
 
        myGLCD.setColor(VGA_BLACK);
        myGLCD.setBackColor(VGA_SILVER);
        myGLCD.print(msg, 205, 37);

if(nachricht=="a"||nachricht=="h"||nachricht=="v"){
  if(nachricht=="a"){max_read=70;}
  if(nachricht=="h"){max_read=69;}
  if(nachricht=="v"){max_read=68;}
 
    if(verbindung==false){
       
      myGLCD.setFont(BigFont);
      //Aufgabenzeile  
      if(konfig!=true){
      button_paint( 120,33,359,22,VGA_SILVER,"",1);
      }else{
        myGLCD.setColor(VGA_BLACK);
        myGLCD.fillRoundRect (120, 33,479,55);
      }
      //Serialmonitor
      button_paint( 120,56,359,742,VGA_LIME,"",1);

      }
      
    if(verbindung==true){
      myGLCD.setFont(BigFont);
      //Aufgabenzeile  
      if(konfig!=true){
      button_paint( 120,33,359,22,VGA_SILVER,"",1);
      }else{
        myGLCD.setColor(VGA_BLACK);
        myGLCD.fillRoundRect (120, 33,479,55);
      }
      //Serialmonitor
      button_paint( 120,56,359,742,VGA_BLACK,"",1);

      }
}
else{max_read=48;}
           
         switch (bool_veraenderung){

      
      case 0: //Menü
                  serial_monitor();
                  menue=!menue;
                  medis=false;
                  com=false;
                  admin1=false;
                  typus=false;
                  ray=false;
                  life=false;
                  rechte=false;
                  modus= false;
                  connection=false;
                   konfig=false;
                   zeit=false;
                   konfig_wert=-1;
                  draw_ebene(funktion);// bool_anzeigen();
      break;
      
        case 1: //Medis
                  serial_monitor();
                  medis=!medis;
                  menue=false;
                  com=false;
                  admin1=false;
                  typus=false;
                  ray=false;
                  life=false;
                  rechte=false;
                  modus= false;
                  connection=false;
                   konfig=false;
                   zeit=false;
                   konfig_wert=-1;
                  draw_ebene(funktion);// bool_anzeigen();
        break;
        
        case 2: //admin
                  serial_monitor();
                  admin1=!admin1;
                  menue=false;
                  medis=false;
                  com=false;
                  typus=false;
                  ray=false;
                  life=false;
                  rechte=false;
                  modus= false;
                  connection=false;
                   konfig=false;
                   zeit=false;
                   konfig_wert=-1;
                  draw_ebene(funktion);// bool_anzeigen();
                  
        break;
        
        case 3: //com
                  serial_monitor();
                  com=!com;
                  menue=false;
                  medis=false;
                  admin1=false;
                  typus=false;
                  ray=false;
                  life=false;
                  rechte=false;
                  modus= false;
                  connection=false;
                   konfig=false;
                   zeit=false;
                   konfig_wert=-1;
                  draw_ebene(funktion);// bool_anzeigen();
        break;    
           
        case 4: //typusändern
                  serial_monitor();
                  typus=!typus;
                  admin1=true;
                  menue=false;
                  medis=false;
                  com=false;
                  ray=false;
                  life=false;
                  rechte=false;
                  modus= false;
                  connection=false;
                   konfig=false;
                   zeit=false;
                   konfig_wert=-1;
                  draw_ebene(funktion);// bool_anzeigen();
        break;
        
        case 5:   //raywert manipulieren
                  serial_monitor();
                  ray=!ray;
                  admin1=true;
                  menue=false;
                  medis=false;
                  com=false;
                  typus=false;
                  life=false;
                  rechte=false;
                  modus= false;
                  connection=false;
                   konfig=false;
                   zeit=false;
                   konfig_wert=-1;
                  draw_ebene(funktion);// bool_anzeigen();
        break;

        case 6: //lifecleaner
                  serial_monitor();
                  admin1=true;
                  menue=false;
                  medis=false;
                  com=false;
                  typus=false;
                  ray=false;
                  life=!life;
                  rechte=false;
                  modus= false;
                  connection=false;
                   konfig=false;
                   zeit=false;
                   konfig_wert=-1;
                  draw_ebene(funktion);// bool_anzeigen();
        break;
        
        case 7: 
                  //rechte
                  serial_monitor();
                   admin1=true;
                  menue=false;
                  medis=false;
                  com=false;
                  typus=false;
                  ray=false;
                  life=false;
                  rechte=!rechte;
                  modus= false;
                  connection=false;
                  konfig=false;
                  zeit=false;
                  konfig_wert=-1;
                  draw_ebene(funktion);// bool_anzeigen();
        break;
        
        case 8:   //mode
                  serial_monitor();
                  admin1=false;
                  menue=false;
                  medis=false;
                  com=true;
                  typus=false;
                  ray=false;
                  life=false;
                  rechte=false;
                  modus=!modus;
                  connection=false;
                   konfig=false;
                   zeit=false;
                   konfig_wert=-1;
                  draw_ebene(funktion);// bool_anzeigen();
        break;
        
        case 9:   //verbinden
                  serial_monitor();
                   admin1=false;
                  menue=false;
                  medis=false;
                  com=true;
                  typus=false;
                  ray=false;
                  life=false;
                  rechte=false;
                  modus= false;
                  connection=!connection;
                   konfig=false;
                   zeit=false;
                   konfig_wert=-1;
                  draw_ebene(funktion);// bool_anzeigen();
        break;
        
        case 10:   //Medilog löschen
                  serial_monitor();
                   admin1=false;
                  menue=false;
                  medis=false;
                  com=true;
                  typus=false;
                  ray=false;
                  life=false;
                  rechte=false;
                  modus= false;
                  connection=false;
                   konfig=false;
                   zeit=false;
                   konfig_wert=-1;
                  draw_ebene(funktion);// bool_anzeigen();
        break;
         case 11:   //Medilog anzeigen
                  serial_monitor();
                   admin1=false;
                  menue=false;
                  medis=false;
                  com=true;
                  typus=false;
                  ray=false;
                  life=false;
                  rechte=false;
                  modus= false;
                  connection=false;
                   konfig=false;
                   zeit=false;
                   konfig_wert=-1;
                  draw_ebene(funktion);// bool_anzeigen();
        break;

        case 13: //konfig menü aufbauen
                  //serial_monitor();
                  admin1=false;
                  menue=false;
                  medis=false;
                  com=false;
                  typus=false;
                  ray=false;
                  life=false;
                  rechte=false;
                  modus= false;
                  connection=false;
                  konfig=true;
                  zeit=false;
                  Serial2.write('u');Serial2.write('\n');
                  konfig_wert=-1;
                  //cut(basis_konfig, konfigwerte, '*');
                  //read_konfig_out_of_string(konfigwerte);
                  while(stern!=25){incoming_reading();}
                  draw_ebene(funktion);
                  
                  // bool_anzeigen();
        break;
        
         case 14: //konfig bearbeiten
                  
                  admin1=false;
                  menue=false;
                  medis=false;
                  com=false;
                  typus=false;
                  ray=false;
                  life=false;
                  rechte=false;
                  modus= false;
                  connection=false;
                  zeit=false;
                 // konfig=true;
                 konfig_wert=ausgabe;
                  konfig0[ausgabe]=!konfig0[ausgabe];
                  for(int x=0;x<26;x++){
                    if(x==ausgabe){konfig0[ausgabe]=konfig0[ausgabe];}
                    else{
                      konfig0[x]=false;
                    }
                  }
                  draw_ebene(funktion);// bool_anzeigen();
        break; 
           case 15:   //Uhr stellen
                 // serial_monitor();
                   admin1=false;
                  menue=false;
                  medis=false;
                  com=false;
                  typus=false;
                  ray=false;
                  life=false;
                  rechte=false;
                  modus= false;
                  connection=false;
                   konfig=false;
                   konfig_wert=-1;
                   zeit=true;

                  if(ausgabe==1){stu=stu+1; if(stu>24){stu=0;}}
                  if(ausgabe==-1){stu=stu-1; if(stu<0){stu=24;}}
                  
                  if(ausgabe==10){minu=minu+1;if(minu>60){minu=0;}}
                  if(ausgabe==-10){minu=minu-1;if(minu<0){minu=60;}}

                  if(ausgabe==100){tag=tag+1;if(tag>31){tag=1;}}
                  if(ausgabe==-100){tag=tag-1;if(tag<1){tag=31;}}

                  if(ausgabe==1000){mona=mona+1;if(mona>12){mona=1;}}
                  if(ausgabe==-1000){mona=mona-1;if(mona<1){mona=12;}}
                  
                  if(ausgabe==10000){jahr=jahr+1;if(jahr<2024){jahr=2024;}}
                  if(ausgabe==-10000){jahr=jahr+1;if(jahr<2024){jahr=2024;}}
                  draw_ebene(funktion);// bool_anzeigen();

           break;        

           case 16:   //Uhr stellen speichern
                 // serial_monitor();
                   admin1=false;
                  menue=false;
                  medis=false;
                  com=false;
                  typus=false;
                  ray=false;
                  life=false;
                  rechte=false;
                  modus= false;
                  connection=false;
                   konfig=false;
                   konfig_wert=-1;
                   zeit=true;
                   
                   rtc_stellen(stu,minu,sek,tag,mona,jahr,0);
                   //rtc.adjust(DateTime(jahr, mona,tag, stu,minu,sek));
                   
                   draw_ebene(funktion);// bool_anzeigen();
           break;

           case 17: //konfig übermitteln
                  
                  admin1=false;
                  menue=false;
                  medis=false;
                  com=true;
                  typus=false;
                  ray=false;
                  life=false;
                  rechte=false;
                  modus= false;
                  connection=false;
                  zeit=false;
                  konfig=false;
                  konfig_wert=-1;
                  
                  for(int x=0;x<25;x++){
                  neue_konfig=neue_konfig+'*'+konfigwerte[x];
                  }
                 // Serial.write("c");Serial.write('\n');delay(1000);Serial.print(neue_konfig);Serial.print("*");Serial.write('\n');
                  Serial2.write("c");Serial2.write('\n');delay(1000);Serial2.print(neue_konfig);Serial2.print("*");Serial2.write('\n');
                  draw_ebene(funktion);
        break; 
          
         case 12:   //Uhr anzeigen
                 // serial_monitor();
                   admin1=false;
                  menue=false;
                  medis=false;
                  com=false;
                  typus=false;
                  ray=false;
                  life=false;
                  rechte=false;
                  modus= false;
                  connection=false;
                   konfig=false;
                   konfig_wert=-1;
                   zeit=true;
                  
  //  myTime="";
       t = rtc.now();      
      timer=t.unixtime();

      myGLCD.setColor(VGA_BLACK);

  //myGLCD.fillRoundRect (0, 39, 119, 799);
  myGLCD.fillRoundRect (119,55,479,799);
      myGLCD.setFont(BigFont);
      
     
   //  myTime=myTime+  t.hour()+':'+t.minute()+':'+t.second()+" - "+t.day()+'.'+t.month()+'.'+t.year();

stu=t.hour();
minu=t.minute();
sek=t.second();
tag=t.day();
mona=t.month();
jahr=t.year();


        draw_ebene(funktion);// bool_anzeigen();
        break;
 
      
        
        default:
        break;
    }/*
    //testausgabe
        if(verbindung==false){
            myGLCD.setBackColor(VGA_LIME);
            myGLCD.setColor(VGA_BLACK);
            myGLCD.setFont(SmallFont);

        }
        
      if(verbindung==true){
            myGLCD.setBackColor(VGA_BLACK);
            myGLCD.setColor(VGA_LIME);
            myGLCD.setFont(SmallFont);
            myGLCD.print(msg2, 123, 58);
            myGLCD.printNumI(wert, 130, 58);

        }*/
        //testausgabe ende
  }

}
              
