
void pushButtons(int a,int b, int option){

    char*msg1="";
    char*msg12="";
    unsigned long msg13=0;

if(option==0){  //Godzilla

button_press(b_h[0][0],b_h[0][1],100,22,VGA_SILVER,0,head[0],"","");  //Menue
button_press(b_h[1][0],b_h[1][1],100,22,VGA_SILVER,1,head[1],"","");  //Medis
button_press(b_h[2][0],b_h[2][1],100,22,VGA_SILVER,2,head[2],"","");  //Admin
button_press(b_h[3][0],b_h[3][1],100,22,VGA_SILVER,3,head[3],"","");  //Com

          

  if(menue==true){
    wert=0;
    button_press( b_s[1][0],b_s[1][1],90,50,VGA_SILVER,"",menue2[0],"a",10);  // Analyse
    button_press( b_s[3][0],b_s[3][1],90,50,VGA_SILVER,"",menue2[1],"h",0);   // Checkin
    button_press( b_s[5][0],b_s[5][1],90,50,VGA_SILVER,"",menue2[2],"v",0);   // Reset
       
        msg3=wert;

  }

if(medis==true){
wert=0;

button_press(b_s[1][0],b_s[1][1],90,50,VGA_SILVER,"",med2[0],"b",3);  //Dekon
button_press(b_s[2][0],b_s[2][1],90,50,VGA_SILVER,"",med2[1],"b",5);  //Blutwäsche
button_press(b_s[3][0],b_s[3][1],90,50,VGA_SILVER,"",med2[2],"b",2);  //Nanoclean
button_press(b_s[4][0],b_s[4][1],90,50,VGA_SILVER,"",med2[3],"b",4);  //Lifecleaner
button_press(b_s[5][0],b_s[5][1],90,50,VGA_SILVER,"",med2[4],"b",6);  //Cleanray
button_press(b_s[6][0],b_s[6][1],90,50,VGA_SILVER,"",med2[5],"b",1);  //Update
button_press(b_s[7][0],b_s[7][1],90,50,VGA_SILVER,"",med2[6],"b",7);  //Drawback

     msg3=wert;
 
}

if(admin1==true){
  //wert=0;
button_press(b_s[1][0],b_s[1][1],90,50,VGA_SILVER,4,admin2[0],"",0);  //Typus ändern
button_press(b_s[2][0],b_s[2][1],90,50,VGA_SILVER,5,admin2[1],"",0);  // Raymanipulation
button_press(b_s[3][0],b_s[3][1],90,50,VGA_SILVER,6,admin2[2],"",0);  // Lifecleanereffekt
button_press(b_s[4][0],b_s[4][1],90,50,VGA_SILVER,7,admin2[3],"",0);  // Rechte

}


if( com==true){

button_press(b_s[1][0],b_s[1][1],90,50,VGA_SILVER,8,com2[0],"",0);  //  Modus ändern
button_press(b_s[2][0],b_s[2][1],90,50,VGA_SILVER,9,com2[1],"",0);  //  Verbinden
button_press(b_s[3][0],b_s[3][1],90,50,VGA_SILVER,10,com2[2],"=",0);  // Medilog löschen
button_press(b_s[4][0],b_s[4][1],90,50,VGA_SILVER,11,com2[3],"k",0);  // Medilog anzeigen
button_press(b_s[5][0],b_s[5][1],90,50,VGA_SILVER,12,com2[4],"",0); //   Uhrzeitanzeigen
button_press(b_s[8][0],b_s[8][1],90,50,VGA_SILVER,13,com2[6],"",0); //    Konfigbearbeiten


}

if(zeit==true){

        button_press(130,90,24,24,VGA_SILVER,15,"","",1);
        button_press(190,90,24,24,VGA_SILVER,15,"","",10);
        button_press(300,90,24,24,VGA_SILVER,15,"","",100);
        button_press(360,90,24,24,VGA_SILVER,15,"","",1000);
        button_press(420,90,24,24,VGA_SILVER,15,"","",10000);

        button_press(130,180,24,24,VGA_SILVER,15,"","",-1);
        button_press(190,180,24,24,VGA_SILVER,15,"","",-10);
        button_press(300,180,24,24,VGA_SILVER,15,"","",-100);
        button_press(360,180,24,24,VGA_SILVER,15,"","",-1000);
        button_press(420,180,24,24,VGA_SILVER,15,"","",-10000);

        button_press(125,250,374,50,VGA_SILVER,16,"","","");
  
  //uhr übertragen
    if((a>=5&&a<135)&&(b>=565&&b<605)){
     
      //serial_monitor();
      msg=com2[5];
         myGLCD.setColor(VGA_BLACK);
        myGLCD.setBackColor(VGA_SILVER);
        myGLCD.print(msg, 205, 37);
      t = rtc.now();      
      timer=t.unixtime(); 
      msg12="j";msg13=timer;
      //Serial.print("Mitt:");Serial.print("j");Serial.print(timer);Serial.write('\n');
      draw_ebene(funktion); 
      }

     msg3=wert;
}

if(konfig==true){

  
  //0 Con_name
  button_press(b_k[1][0]+100,b_k[1][1],359,50,VGA_FUCHSIA,14,konfi2[9],"",1); //Start
 //2 UTC
 //3 60
  button_press(b_k[2][0]+100,b_k[2][1],359,50,VGA_FUCHSIA,14,konfi2[9],"",4);//Tage
  
  button_press(b_k[3][0]+100,b_k[3][1],359,50,VGA_FUCHSIA,14,konfi2[9],"",5);//Dosis

  button_press(b_k[4][0]+100,b_k[4][1],80,50,VGA_FUCHSIA,14,konfi2[9],"",6);//Clean
  button_press(b_k[4][0]+190,b_k[4][1],80,50,VGA_FUCHSIA,14,konfi2[9],"",7);//Clean
  button_press(b_k[4][0]+280,b_k[4][1],80,50,VGA_FUCHSIA,14,konfi2[9],"",8);//Clean
  button_press(b_k[4][0]+370,b_k[4][1],80,50,VGA_FUCHSIA,14,konfi2[9],"",9);//Clean
  

  button_press(b_k[5][0]+100,b_k[5][1],100,50,VGA_FUCHSIA,14,konfi2[9],"",10);//Life
  button_press(b_k[5][0]+210,b_k[5][1],100,50,VGA_FUCHSIA,14,konfi2[9],"",11);//Life
  button_press(b_k[5][0]+320,b_k[5][1],100,50,VGA_FUCHSIA,14,konfi2[9],"",12);//Life

  button_press(b_k[6][0]+100,b_k[6][1],80,50,VGA_FUCHSIA,14,konfi2[9],"",13);//Blood
  button_press(b_k[6][0]+190,b_k[6][1],80,50,VGA_FUCHSIA,14,konfi2[9],"",14);//Blood
  button_press(b_k[6][0]+280,b_k[6][1],80,50,VGA_FUCHSIA,14,konfi2[9],"",15);//Blood
  button_press(b_k[6][0]+370,b_k[6][1],80,50,VGA_FUCHSIA,14,konfi2[9],"",16);//Blood
  
  button_press(b_k[7][0]+100,b_k[7][1],80,50,VGA_FUCHSIA,14,konfi2[9],"",17);//Nano
  button_press(b_k[7][0]+190,b_k[7][1],80,50,VGA_FUCHSIA,14,konfi2[9],"",18);//Nano
  button_press(b_k[7][0]+280,b_k[7][1],80,50,VGA_FUCHSIA,14,konfi2[9],"",19);//Nano
  button_press(b_k[7][0]+370,b_k[7][1],80,50,VGA_FUCHSIA,14,konfi2[9],"",20);//Nano
  
  button_press(b_k[8][0]+100,b_k[8][1],80,50,VGA_FUCHSIA,14,konfi2[9],"",21);//Dekon 
  button_press(b_k[8][0]+190,b_k[8][1],80,50,VGA_FUCHSIA,14,konfi2[9],"",22);//Dekon 
  button_press(b_k[8][0]+280,b_k[8][1],80,50,VGA_FUCHSIA,14,konfi2[9],"",23);//Dekon 
  button_press(b_k[8][0]+370,b_k[8][1],80,50,VGA_FUCHSIA,14,konfi2[9],"",24);//Dekon 

  button_press(b_s[7][0],b_s[7][1],90,50,VGA_SILVER,17,"","",0);// KSend
}
if(konfig_wert!=-1){
    myGLCD.setFont(BigFont);   
ausgabe_paint(b_k[0][0],b_k[0][1],459,50,VGA_SILVER,wert,"");  
  
  //1 
  if((a>=120&&a<170)&&(b>=590&&b<650)){
  wert=(wert*10)+1;  
ausgabe_paint(b_k[0][0],b_k[0][1],459,50,VGA_SILVER,wert,"");
  //Serial.println("1");
  }
  
//2 
  if((a>=180&&a<250)&&(b>=590&&b<650)){
      wert=(wert*10)+2;  
ausgabe_paint(b_k[0][0],b_k[0][1],459,50,VGA_SILVER,wert,"");
  //Serial.println("2");
  }
  
//3
  if((a>=250&&a<320)&&(b>=590&&b<650)){
        wert=(wert*10)+3;  
ausgabe_paint(b_k[0][0],b_k[0][1],459,50,VGA_SILVER,wert,"");
  //Serial.println("3");
  }
  
//4 
  if((a>=320&&a<380)&&(b>=590&&b<650)){
          wert=(wert*10)+4;  
ausgabe_paint(b_k[0][0],b_k[0][1],459,50,VGA_SILVER,wert,"");
  //Serial.println("4");
  }
  
//5  
  if((a>=380&&a<460)&&(b>=590&&b<650)){
          wert=(wert*10)+5;  
ausgabe_paint(b_k[0][0],b_k[0][1],459,50,VGA_SILVER,wert,"");
 //Serial.println("5");
  }
  
//6 
  if((a>=120&&a<170)&&(b>=640&&b<710)){
          wert=(wert*10)+6;  
ausgabe_paint(b_k[0][0],b_k[0][1],459,50,VGA_SILVER,wert,"");
  //Serial.println("6");
  }
  
//7 
  if((a>=180&&a<250)&&(b>=660&&b<730)){
          wert=(wert*10)+7;  
ausgabe_paint(b_k[0][0],b_k[0][1],459,50,VGA_SILVER,wert,"");
  //Serial.println("7");
  }
  
//8
  if((a>=250&&a<320)&&(b>=640&&b<710)){
          wert=(wert*10)+8;  
ausgabe_paint(b_k[0][0],b_k[0][1],459,50,VGA_SILVER,wert,"");
  //Serial.println("8");
  }
  
//9 
  if((a>=320&&a<380)&&(b>=660&&b<730)){
          wert=(wert*10)+9;  
ausgabe_paint(b_k[0][0],b_k[0][1],459,50,VGA_SILVER,wert,"");
  //Serial.println("9");
  }
  
//0 
  if((a>=380&&a<460)&&(b>=660&&b<730)){
          wert=(wert*10);  
ausgabe_paint(b_k[0][0],b_k[0][1],459,50,VGA_SILVER,wert,"");
  //Serial.println("0");
  }
  
//Clear 
  if((a>=120&&a<260)&&(b>=730&&b<780)){
   
        wert=0;  
ausgabe_paint(b_k[0][0],b_k[0][1],459,50,VGA_SILVER,wert,"");
  }
 
//Enter 
  if((a>=280&&a<420)&&(b>=730&&b<780)){
    if(wert==0){wert=konfigwerte[konfig_wert].toInt();  }
    konfigwerte[konfig_wert]=wert;
    konfig_wert=-1;
     draw_ebene(funktion); 
   // msg12="";msg13=wert;
   // serial_monitor();
    

  }
     
}


if(life==true){
    myGLCD.setFont(BigFont);   
  //1
  if((a>=120&&a<170)&&(b>=570&&b<630)){
  wert=(wert*10)+1;  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.print("Std.", 300, 535);
  myGLCD.printNumI(wert, 125, 535);
  //Serial.println("1");
  }
//2
  if((a>=180&&a<250)&&(b>=570&&b<630)){
      wert=(wert*10)+2;  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.print("Std.", 300, 535);
  myGLCD.printNumI(wert, 125, 535);
  //Serial.println("2");
  }
//3
  if((a>=250&&a<320)&&(b>=570&&b<630)){
        wert=(wert*10)+3;  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.print("Std.", 300, 535);
  myGLCD.printNumI(wert, 125, 535);  
  //Serial.println("3");
  }
//4
  if((a>=320&&a<380)&&(b>=570&&b<630)){
          wert=(wert*10)+4;  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.print("Std.", 300, 535);
  myGLCD.printNumI(wert, 125, 535);
  //Serial.println("4");
  }
//5  
  if((a>=380&&a<460)&&(b>=570&&b<630)){
          wert=(wert*10)+5;  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.print("Std.", 300, 535);
  myGLCD.printNumI(wert, 125, 535);
 //Serial.println("5");
  }
//6  
  if((a>=120&&a<170)&&(b>=640&&b<710)){
          wert=(wert*10)+6;  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.print("Std.", 300, 535);
  myGLCD.printNumI(wert, 125, 535);
  //Serial.println("6");
  }
//7 
  if((a>=180&&a<250)&&(b>=640&&b<710)){
          wert=(wert*10)+7;  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.print("Std.", 300, 535);
  myGLCD.printNumI(wert, 125, 535);
  //Serial.println("7");
  }
//8 
  if((a>=250&&a<320)&&(b>=640&&b<710)){
          wert=(wert*10)+8;  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.print("Std.", 300, 535);
  myGLCD.printNumI(wert, 125, 535);
  //Serial.println("8");
  }
//9
  if((a>=320&&a<380)&&(b>=640&&b<710)){
          wert=(wert*10)+9;  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.print("Std.", 300, 535);
  myGLCD.printNumI(wert, 125, 535);
  //Serial.println("9");
  }
//0
  if((a>=380&&a<460)&&(b>=640&&b<710)){
          wert=(wert*10);  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.print("Std.", 300, 535);
  myGLCD.printNumI(wert, 125, 535);
  //Serial.println("0");
  }
//Clear
  if((a>=120&&a<260)&&(b>=710&&b<760)){
    serial_monitor();
        wert=0;  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.print("Std.", 300, 535);
  myGLCD.printNumI(wert, 125, 535);
 // Serial.println("Clear");
  }
  
//Enter
  if((a>=280&&a<420)&&(b>=710&&b<760)){
    
    msg12="l";msg13=wert;
    serial_monitor();
    

  }
}

 
if(connection==true){
  myGLCD.setFont(BigFont);   
 //enter 
   if((a>=280&&a<420)&&(b>=710&&b<760)){   
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  msg1=titel[10]; 
  
       
        myGLCD.setFont(BigFont);
        myGLCD.setBackColor(VGA_LIME);
        myGLCD.setColor(VGA_BLACK);
        myGLCD.print(msg1, 205, 37);
        
     wert_verbindung=wert;
//    Serial.print(wert_verbindung);Serial.print(" : ");Serial.print(wert);Serial.print(" : ");Serial.println(verbindung);Serial.println();


 Serial3.print("x");Serial3.println(wert+10);//Serial3.write('\n');//Damit die Werte an den ESP direkt gehen

 serial_monitor();
 draw_ebene(funktion);

 
  } 
//Clear  & verbindung lösen
  if((a>=120&&a<260)&&(b>=710&&b<760)){
       wert=0;  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.printNumI(wert, 125, 535);

  verbindung=false;
  wert_verbindung=0;
  msg12="x"; msg13=0; //verbindung zu esp 0 aufbauen, der ist nicht vergeben und so gibt es keine offenen verbindungen
  myGLCD.setBackColor(VGA_BLACK);
  myGLCD.setColor(VGA_BLACK);
 // myGLCD.fillRoundRect (432, 1,479,29);
          serial_monitor();
        draw_ebene(funktion);
 
  }
  //uhr übertragen
    if((a>=5&&a<135)&&(b>=565&&b<605)){
     
      serial_monitor();
      msg=com2[5];
         myGLCD.setColor(VGA_BLACK);
        myGLCD.setBackColor(VGA_SILVER);
        myGLCD.print(msg, 205, 37);
      t = rtc.now();      
      timer=t.unixtime(); 
      msg12="j";msg13=timer;
      //Serial.print("Mitt:");Serial.print("j");Serial.print(timer);Serial.write('\n');
      draw_ebene(funktion); 
      }

//1
  if((a>=120&&a<170)&&(b>=570&&b<630)){
  wert=(wert*10)+1; 
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.printNumI(wert, 125, 535);

  }
//2
  if((a>=180&&a<250)&&(b>=570&&b<630)){
  wert=(wert*10)+2; 
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.printNumI(wert, 125, 535);

  }
//3
  if((a>=250&&a<320)&&(b>=570&&b<630)){
  wert=(wert*10)+3;
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.printNumI(wert, 125, 535);  
 
  }
//4
  if((a>=320&&a<380)&&(b>=570&&b<630)){
  wert=(wert*10)+4; 
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.printNumI(wert, 125, 535);

  }
//5  
  if((a>=380&&a<460)&&(b>=570&&b<630)){
  wert=(wert*10)+5;  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.printNumI(wert, 125, 535);

  }
//6  
  if((a>=120&&a<170)&&(b>=640&&b<710)){
  wert=(wert*10)+6;
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.printNumI(wert, 125, 535);

  }
//7 
  if((a>=180&&a<250)&&(b>=640&&b<710)){
  wert=(wert*10)+7;
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.printNumI(wert, 125, 535);
 
  }
//8 
  if((a>=250&&a<320)&&(b>=640&&b<710)){
  wert=(wert*10)+8;  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.printNumI(wert, 125, 535);

  }
//9
  if((a>=320&&a<380)&&(b>=640&&b<710)){
  wert=(wert*10)+9; 
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.printNumI(wert, 125, 535);

  }
//10
  if((a>=380&&a<460)&&(b>=640&&b<710)){
  wert=(wert*10); 
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.printNumI(wert, 125, 535);
 
  }
}

if(ray==true){
  myGLCD.setFont(BigFont);
//1
  if((a>=120&&a<170)&&(b>=570&&b<630)){
  wert=(wert*10)+1;  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.printNumI(wert, 125, 535);
  //Serial.println("1");
  }
//2
  if((a>=180&&a<250)&&(b>=570&&b<630)){
      wert=(wert*10)+2;  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.printNumI(wert, 125, 535);
  //Serial.println("2");
  }
//3
  if((a>=250&&a<320)&&(b>=570&&b<630)){
        wert=(wert*10)+3;  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.printNumI(wert, 125, 535);  
  //Serial.println("3");
  }
//4
  if((a>=320&&a<380)&&(b>=570&&b<630)){
          wert=(wert*10)+4;  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.printNumI(wert, 125, 535);
  //Serial.println("4");
  }
//5  
  if((a>=380&&a<460)&&(b>=570&&b<630)){
          wert=(wert*10)+5;  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.printNumI(wert, 125, 535);
 //Serial.println("5");
  }
//6  
  if((a>=120&&a<170)&&(b>=640&&b<710)){
          wert=(wert*10)+6;  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.printNumI(wert, 125, 535);
  //Serial.println("6");
  }
//7 
  if((a>=180&&a<250)&&(b>=640&&b<710)){
          wert=(wert*10)+7;  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.printNumI(wert, 125, 535);
  //Serial.println("7");
  }
//8 
  if((a>=250&&a<320)&&(b>=640&&b<710)){
          wert=(wert*10)+8;  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.printNumI(wert, 125, 535);
  //Serial.println("8");
  }
//9
  if((a>=320&&a<380)&&(b>=640&&b<710)){
          wert=(wert*10)+9;  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.printNumI(wert, 125, 535);
  //Serial.println("9");
  }
//0
  if((a>=380&&a<460)&&(b>=640&&b<710)){
          wert=(wert*10);  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.printNumI(wert, 125, 535);
  //Serial.println("0");
  }
//Clear
  if((a>=120&&a<260)&&(b>=710&&b<760)){
    serial_monitor();
        wert=0;  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.printNumI(wert, 125, 535);
 // Serial.println("Clear");
  }
  
//Enter
  if((a>=280&&a<420)&&(b>=710&&b<760)){
    serial_monitor();
    msg1=titel[9];msg12="r";msg13=wert;
 // Serial.println("Return");
  }

   if((a>=5&&a<105)&&(b>=565&&b<625)){
    serial_monitor();
      msg1=titel[6];msg12="r";msg13=10;
      myGLCD.setColor(VGA_SILVER);
      myGLCD.fillRoundRect (10, 330, 100, 380);
      delay(10);
      draw_ebene(funktion);

      }
   if((a>=5&&a<105)&&(b>=645&&b<705)){
    serial_monitor();
      msg1=titel[7];msg12="r";msg13=20;
      myGLCD.setColor(VGA_SILVER);
      myGLCD.fillRoundRect (10, 330, 100, 380);
      delay(10);
      draw_ebene(funktion);

      } 

   if((a>=5&&a<105)&&(b>=725&&b<785)){
    serial_monitor();
      msg1=titel[8];msg12="r";msg13=30;
      myGLCD.setColor(VGA_SILVER);
      myGLCD.fillRoundRect (10, 330, 100, 380);
      delay(10);

      draw_ebene(funktion);
      }    
}




if(modus==true){
     
    button_press(b_c[0][0],b_c[0][1],150,60,VGA_SILVER,"",titel[3],"t",0);  //  Godzilla
    button_press(b_c[1][0],b_c[1][1],150,60,VGA_SILVER,"",titel[4],"t",20); // Buchung
    button_press(b_c[2][0],b_c[2][1],150,60,VGA_SILVER,"",titel[5],"t",10); // Checkin
    delay(10);
  //uhr übertragen
    if((a>=5&&a<135)&&(b>=565&&b<605)){
     
      serial_monitor();
      msg=com2[5];
         myGLCD.setColor(VGA_BLACK);
        myGLCD.setBackColor(VGA_SILVER);
        myGLCD.print(msg, 205, 37);
      t = rtc.now();      
      timer=t.unixtime(); 
      msg2="j";wert=timer;
      //Serial.print("Mitt:");Serial.print("j");Serial.print(timer);Serial.write('\n');
      draw_ebene(funktion); 
      }
      
    msg12=msg2;
    msg2="";
    msg1=msg;
    msg="";
    msg13=wert;
}
 
if(typus==true){

    button_press(b_c[0][0],b_c[0][1],150,60,VGA_SILVER,"",titel[2],"m",250);  //  Bunkerbewohner
    button_press(b_c[1][0],b_c[1][1],150,60,VGA_SILVER,"",titel[1],"m",360);  // Mutant
    button_press(b_c[2][0],b_c[2][1],150,60,VGA_SILVER,"",titel[0],"m",100);  // Mensch
    delay(10);
    msg12=msg2;
    msg2="";
    msg1=msg;
    msg="";
    msg13=wert;
}

if(rechte==true){
  
   myGLCD.setFont(BigFont);
  if((a>=120&&a<170)&&(b>=570&&b<630)){
     Nano=!Nano;
    if(Nano==true){
          wert=wert+10000;  
          }
     else{
        wert=wert-10000;   
     }   
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.printNumI(wert, 125, 535);
  }
  
  if((a>=180&&a<250)&&(b>=570&&b<630)){
       Blood=!Blood;
    if(Blood==true){
          wert=wert+1000;  
          }
     else{
        wert=wert-1000;   
     }
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.printNumI(wert, 125, 535);
  }
  
  if((a>=250&&a<320)&&(b>=570&&b<630)){
       Clean=!Clean;
    if(Clean==true){
          wert=wert+100;  
          }
     else{
        wert=wert-100;   
     }
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.printNumI(wert, 125, 535);  
  }
  
  if((a>=320&&a<380)&&(b>=570&&b<630)){
   Life=!Life;
    if(Life==true){
          wert=wert+10;  
          }
     else{
        wert=wert-10;   
     }
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.printNumI(wert, 125, 535);
  }
  
  if((a>=380&&a<460)&&(b>=570&&b<630)){
    Dekon=!Dekon;
    if(Dekon==true){
          wert=wert+1;  
          }
     else{
        wert=wert-1;   
     }
     
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.printNumI(wert, 125, 535);

  }
  
  if((a>=120&&a<260)&&(b>=710&&b<760)){
    serial_monitor();
  msg12="o";msg13=wert;  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.printNumI(wert, 125, 535);

  }  
}

   if(msg2!=""){
      
        myGLCD.setFont(BigFont);
        myGLCD.setBackColor(VGA_SILVER);
        myGLCD.setColor(VGA_BLACK);
        myGLCD.print(msg, 205, 37);
        
        if(verbindung==false){
          myGLCD.setBackColor(VGA_LIME);
          myGLCD.setColor(VGA_BLACK);
        }
        if(verbindung==true){
          myGLCD.setBackColor(VGA_BLACK);
          myGLCD.setColor(VGA_LIME);
        }
                 
      if(verbindung==true){
        Serial3.print(msg2);
        Serial3.print(msg3);
        Serial3.write('\n');
        delay(10);
        Serial.print("Nachricht an ESP (0):");
        Serial.print(msg2);Serial.println(msg3);

      }
      else{
        Serial2.print(msg2);
        Serial2.print(msg3);
        Serial2.write('\n');
        delay(10);
        Serial.print("Nachricht an Worker (0):");
        Serial.print(msg2);Serial.println(msg3);
       }
        
    }      
 
   if(msg12!=""){      
      
        myGLCD.setFont(BigFont);
        myGLCD.setBackColor(VGA_SILVER);
        myGLCD.setColor(VGA_BLACK);
        myGLCD.print(msg1, 205, 37);
        
        if(verbindung==false){
          myGLCD.setBackColor(VGA_LIME);
          myGLCD.setColor(VGA_BLACK);
        }
        if(verbindung==true){
          myGLCD.setBackColor(VGA_BLACK);
          myGLCD.setColor(VGA_LIME);
        }
        
        
      if(verbindung==true){
        Serial3.print(msg12);
        Serial3.print(msg13);
        Serial3.write('\n');
        delay(10);
        Serial.print("Nachricht an ESP (1):");
        Serial.print(msg12);Serial.println(msg13);

      }
      else{
        Serial2.print(msg12);
        Serial2.print(msg13);
        Serial2.write('\n');
        delay(10);
        Serial.print("Nachricht an worker (1):");
        Serial.print(msg12);Serial.println(msg13);
       }
        
    }   
}

if(option==1){  //Checkin

button_press(b_h[0][0],b_h[0][1],100,22,VGA_SILVER,0,head[0],"","");  //Menue

button_press(b_h[2][0],b_h[2][1],100,22,VGA_SILVER,2,head[2],"","");  //Admin


          

  if(menue==true){
    wert=0;
    button_press( b_s[1][0],b_s[1][1],90,50,VGA_SILVER,"",menue2[0],"a",10);  // Analyse
    button_press( b_s[3][0],b_s[3][1],90,50,VGA_SILVER,"",menue2[1],"h",0);   // Checkin
    button_press( b_s[5][0],b_s[5][1],90,50,VGA_SILVER,"",menue2[2],"v",0);   // Reset
       
        msg3=wert;

  }



if(admin1==true){
  //wert=0;
button_press(b_s[1][0],b_s[1][1],90,50,VGA_SILVER,4,admin2[0],"",0);  //Typus ändern
button_press(b_s[2][0],b_s[2][1],90,50,VGA_SILVER,5,admin2[1],"",0);  // Raymanipulation
button_press(b_s[3][0],b_s[3][1],90,50,VGA_SILVER,6,admin2[2],"",0);  // Lifecleanereffekt
button_press(b_s[4][0],b_s[4][1],90,50,VGA_SILVER,7,admin2[3],"",0);  // Rechte

}



if(life==true){
    myGLCD.setFont(BigFont);   
  //1
  if((a>=120&&a<170)&&(b>=570&&b<630)){
  wert=(wert*10)+1;  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.print("Std.", 300, 535);
  myGLCD.printNumI(wert, 125, 535);
  //Serial.println("1");
  }
//2
  if((a>=180&&a<250)&&(b>=570&&b<630)){
      wert=(wert*10)+2;  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.print("Std.", 300, 535);
  myGLCD.printNumI(wert, 125, 535);
  //Serial.println("2");
  }
//3
  if((a>=250&&a<320)&&(b>=570&&b<630)){
        wert=(wert*10)+3;  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.print("Std.", 300, 535);
  myGLCD.printNumI(wert, 125, 535);  
  //Serial.println("3");
  }
//4
  if((a>=320&&a<380)&&(b>=570&&b<630)){
          wert=(wert*10)+4;  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.print("Std.", 300, 535);
  myGLCD.printNumI(wert, 125, 535);
  //Serial.println("4");
  }
//5  
  if((a>=380&&a<460)&&(b>=570&&b<630)){
          wert=(wert*10)+5;  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.print("Std.", 300, 535);
  myGLCD.printNumI(wert, 125, 535);
 //Serial.println("5");
  }
//6  
  if((a>=120&&a<170)&&(b>=640&&b<710)){
          wert=(wert*10)+6;  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.print("Std.", 300, 535);
  myGLCD.printNumI(wert, 125, 535);
  //Serial.println("6");
  }
//7 
  if((a>=180&&a<250)&&(b>=640&&b<710)){
          wert=(wert*10)+7;  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.print("Std.", 300, 535);
  myGLCD.printNumI(wert, 125, 535);
  //Serial.println("7");
  }
//8 
  if((a>=250&&a<320)&&(b>=640&&b<710)){
          wert=(wert*10)+8;  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.print("Std.", 300, 535);
  myGLCD.printNumI(wert, 125, 535);
  //Serial.println("8");
  }
//9
  if((a>=320&&a<380)&&(b>=640&&b<710)){
          wert=(wert*10)+9;  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.print("Std.", 300, 535);
  myGLCD.printNumI(wert, 125, 535);
  //Serial.println("9");
  }
//0
  if((a>=380&&a<460)&&(b>=640&&b<710)){
          wert=(wert*10);  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.print("Std.", 300, 535);
  myGLCD.printNumI(wert, 125, 535);
  //Serial.println("0");
  }
//Clear
  if((a>=120&&a<260)&&(b>=710&&b<760)){
    serial_monitor();
        wert=0;  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.print("Std.", 300, 535);
  myGLCD.printNumI(wert, 125, 535);
 // Serial.println("Clear");
  }
  
//Enter
  if((a>=280&&a<420)&&(b>=710&&b<760)){
    
    msg12="l";msg13=wert;
    serial_monitor();
    

  }
}

 


if(ray==true){
  myGLCD.setFont(BigFont);
//1
  if((a>=120&&a<170)&&(b>=570&&b<630)){
  wert=(wert*10)+1;  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.printNumI(wert, 125, 535);
  //Serial.println("1");
  }
//2
  if((a>=180&&a<250)&&(b>=570&&b<630)){
      wert=(wert*10)+2;  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.printNumI(wert, 125, 535);
  //Serial.println("2");
  }
//3
  if((a>=250&&a<320)&&(b>=570&&b<630)){
        wert=(wert*10)+3;  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.printNumI(wert, 125, 535);  
  //Serial.println("3");
  }
//4
  if((a>=320&&a<380)&&(b>=570&&b<630)){
          wert=(wert*10)+4;  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.printNumI(wert, 125, 535);
  //Serial.println("4");
  }
//5  
  if((a>=380&&a<460)&&(b>=570&&b<630)){
          wert=(wert*10)+5;  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.printNumI(wert, 125, 535);
 //Serial.println("5");
  }
//6  
  if((a>=120&&a<170)&&(b>=640&&b<710)){
          wert=(wert*10)+6;  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.printNumI(wert, 125, 535);
  //Serial.println("6");
  }
//7 
  if((a>=180&&a<250)&&(b>=640&&b<710)){
          wert=(wert*10)+7;  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.printNumI(wert, 125, 535);
  //Serial.println("7");
  }
//8 
  if((a>=250&&a<320)&&(b>=640&&b<710)){
          wert=(wert*10)+8;  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.printNumI(wert, 125, 535);
  //Serial.println("8");
  }
//9
  if((a>=320&&a<380)&&(b>=640&&b<710)){
          wert=(wert*10)+9;  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.printNumI(wert, 125, 535);
  //Serial.println("9");
  }
//0
  if((a>=380&&a<460)&&(b>=640&&b<710)){
          wert=(wert*10);  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.printNumI(wert, 125, 535);
  //Serial.println("0");
  }
//Clear
  if((a>=120&&a<260)&&(b>=710&&b<760)){
    serial_monitor();
        wert=0;  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.printNumI(wert, 125, 535);
 // Serial.println("Clear");
  }
  
//Enter
  if((a>=280&&a<420)&&(b>=710&&b<760)){
    serial_monitor();
    msg1=titel[9];msg12="r";msg13=wert;
 // Serial.println("Return");
  }

   if((a>=5&&a<105)&&(b>=565&&b<625)){
    serial_monitor();
      msg1=titel[6];msg12="r";msg13=10;
      myGLCD.setColor(VGA_SILVER);
      myGLCD.fillRoundRect (10, 330, 100, 380);
      delay(10);
      draw_ebene(funktion);

      }
   if((a>=5&&a<105)&&(b>=645&&b<705)){
    serial_monitor();
      msg1=titel[7];msg12="r";msg13=20;
      myGLCD.setColor(VGA_SILVER);
      myGLCD.fillRoundRect (10, 330, 100, 380);
      delay(10);
      draw_ebene(funktion);

      } 

   if((a>=5&&a<105)&&(b>=725&&b<785)){
    serial_monitor();
      msg1=titel[8];msg12="r";msg13=30;
      myGLCD.setColor(VGA_SILVER);
      myGLCD.fillRoundRect (10, 330, 100, 380);
      delay(10);

      draw_ebene(funktion);
      }    
}

 
if(typus==true){

    button_press(b_c[0][0],b_c[0][1],150,60,VGA_SILVER,"",titel[2],"m",250);  //  Bunkerbewohner
    button_press(b_c[1][0],b_c[1][1],150,60,VGA_SILVER,"",titel[1],"m",360);  // Mutant
    button_press(b_c[2][0],b_c[2][1],150,60,VGA_SILVER,"",titel[0],"m",100);  // Mensch
    delay(10);
    msg12=msg2;
    msg2="";
    msg1=msg;
    msg="";
    msg13=wert;
}

if(rechte==true){
  
   myGLCD.setFont(BigFont);
  if((a>=120&&a<170)&&(b>=570&&b<630)){
     Nano=!Nano;
    if(Nano==true){
          wert=wert+10000;  
          }
     else{
        wert=wert-10000;   
     }   
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.printNumI(wert, 125, 535);
  }
  
  if((a>=180&&a<250)&&(b>=570&&b<630)){
       Blood=!Blood;
    if(Blood==true){
          wert=wert+1000;  
          }
     else{
        wert=wert-1000;   
     }
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.printNumI(wert, 125, 535);
  }
  
  if((a>=250&&a<320)&&(b>=570&&b<630)){
       Clean=!Clean;
    if(Clean==true){
          wert=wert+100;  
          }
     else{
        wert=wert-100;   
     }
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.printNumI(wert, 125, 535);  
  }
  
  if((a>=320&&a<380)&&(b>=570&&b<630)){
   Life=!Life;
    if(Life==true){
          wert=wert+10;  
          }
     else{
        wert=wert-10;   
     }
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.printNumI(wert, 125, 535);
  }
  
  if((a>=380&&a<460)&&(b>=570&&b<630)){
    Dekon=!Dekon;
    if(Dekon==true){
          wert=wert+1;  
          }
     else{
        wert=wert-1;   
     }
     
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.printNumI(wert, 125, 535);

  }
  
  if((a>=120&&a<260)&&(b>=710&&b<760)){
    serial_monitor();
  msg12="o";msg13=wert;  
  myGLCD.setBackColor(VGA_FUCHSIA);
  myGLCD.setColor(VGA_FUCHSIA);  
  myGLCD.fillRoundRect (120, 530, 479, 560);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (120, 530, 479, 560);
  myGLCD.printNumI(wert, 125, 535);

  }  
}

   if(msg2!=""){
      
        myGLCD.setFont(BigFont);
        myGLCD.setBackColor(VGA_SILVER);
        myGLCD.setColor(VGA_BLACK);
        myGLCD.print(msg, 205, 37);
        
        if(verbindung==false){
          myGLCD.setBackColor(VGA_LIME);
          myGLCD.setColor(VGA_BLACK);
        }
        if(verbindung==true){
          myGLCD.setBackColor(VGA_BLACK);
          myGLCD.setColor(VGA_LIME);
        }
                 
      if(verbindung==true){
        Serial3.print(msg2);
        Serial3.print(msg3);
        Serial3.write('\n');

      }
      else{
        Serial2.print(msg2);
        Serial2.print(msg3);
        Serial2.write('\n');
       }
        
    }      
 
   if(msg12!=""){      
      
        myGLCD.setFont(BigFont);
        myGLCD.setBackColor(VGA_SILVER);
        myGLCD.setColor(VGA_BLACK);
        myGLCD.print(msg1, 205, 37);
        
        if(verbindung==false){
          myGLCD.setBackColor(VGA_LIME);
          myGLCD.setColor(VGA_BLACK);
        }
        if(verbindung==true){
          myGLCD.setBackColor(VGA_BLACK);
          myGLCD.setColor(VGA_LIME);
        }
        
        
      if(verbindung==true){
        Serial3.print(msg12);
        Serial3.print(msg13);
        Serial3.write('\n');

      }
      else{
        Serial2.print(msg12);
        Serial2.print(msg13);
        Serial2.write('\n');
       }
        
   }   
} 


if(option==2){  //Buchung

button_press(b_h[0][0],b_h[0][1],100,22,VGA_SILVER,0,head[0],"","");  //Menue
button_press(b_h[1][0],b_h[1][1],100,22,VGA_SILVER,1,head[1],"","");  //Medis


          

  if(menue==true){
    wert=0;
    button_press( b_s[1][0],b_s[1][1],90,50,VGA_SILVER,"",menue2[0],"a",20);  // Analyse

       
        msg3=wert;

  }

if(medis==true){
wert=0;

  if(Nano2 ==true){button_press(b_s[3][0],b_s[3][1],90,50,VGA_SILVER,"",med2[2],"b",2);}else{}//Nano
  if(Blood2==true){button_press(b_s[2][0],b_s[2][1],90,50,VGA_SILVER,"",med2[1],"b",5);}else{}//Blood
  if(Clean2==true){button_press(b_s[5][0],b_s[5][1],90,50,VGA_SILVER,"",med2[4],"b",6);}else{}//Clean
  if(Life2 ==true){button_press(b_s[4][0],b_s[4][1],90,50,VGA_SILVER,"",med2[3],"b",4);}else{}//Life
  if(Dekon2==true){button_press(b_s[1][0],b_s[1][1],90,50,VGA_SILVER,"",med2[0],"b",3);}else{}//Dekon
  if(Draw2==true){button_press(b_s[7][0],b_s[7][1],90,50,VGA_SILVER,"",med2[6],"b",7); }else{}//Draw
  if(Update2==true){button_press(b_s[6][0],b_s[6][1],90,50,VGA_SILVER,"",med2[5],"b",1);}else{}//+date

     msg3=wert;
 
}


   if(msg2!=""){
      
        myGLCD.setFont(BigFont);
        myGLCD.setBackColor(VGA_SILVER);
        myGLCD.setColor(VGA_BLACK);
        myGLCD.print(msg, 205, 37);
        
        if(verbindung==false){
          myGLCD.setBackColor(VGA_LIME);
          myGLCD.setColor(VGA_BLACK);
        }
        if(verbindung==true){
          myGLCD.setBackColor(VGA_BLACK);
          myGLCD.setColor(VGA_LIME);
        }
                 
      if(verbindung==true){
        Serial3.print(msg2);
        Serial3.print(msg3);
        Serial3.write('\n');

      }
      else{
        Serial2.print(msg2);
        Serial2.print(msg3);
        Serial2.write('\n');
       }
        
    }      
 
   if(msg12!=""){      
      
        myGLCD.setFont(BigFont);
        myGLCD.setBackColor(VGA_SILVER);
        myGLCD.setColor(VGA_BLACK);
        myGLCD.print(msg1, 205, 37);
        
        if(verbindung==false){
          myGLCD.setBackColor(VGA_LIME);
          myGLCD.setColor(VGA_BLACK);
        }
        if(verbindung==true){
          myGLCD.setBackColor(VGA_BLACK);
          myGLCD.setColor(VGA_LIME);
        }
        
        
      if(verbindung==true){
        Serial3.print(msg12);
        Serial3.print(msg13);
        Serial3.write('\n');
     //   delay(10);
     //   Serial.print("Nachricht an ESP:");
     //   Serial.print(msg12);Serial.println(msg13);

      }
      else{
        Serial2.print(msg12);
        Serial2.print(msg13);
        Serial2.write('\n');
   //     delay(10);
   //     Serial.print("Nachricht an worker:");
   //     Serial.print(msg12);Serial.println(msg13);
       }
        
    }   
}

}
