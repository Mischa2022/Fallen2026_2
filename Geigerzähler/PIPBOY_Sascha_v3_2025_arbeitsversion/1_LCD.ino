void draw_mode(int ebene) {
  unsigned long lc_sekunden,lc_minuten,lc_stunden,lc_basis;
  int stunden;
  int minuten;
  int sekunden;
   Display.clearDisplay();

    DateTime now = rtc.now(); 
    aktuell_time=now.unixtime();
 if(ebene!=0){
  if(vektor==true){
      Display.setCursor(100 , 52);
  Display.print("<->");
  }
 }
    
  if(ebene==0&&unterebene==0){
  Display.clearDisplay();
  Display.setTextSize(1);
  Display.setTextColor(WHITE);
  Display.setCursor( 20, 10);
  Display.print(now.hour(),DEC);
  Display.print(":");
  Display.print(now.minute(),DEC);
  Display.print(":");
  Display.print(now.second(),DEC);

  
Display.drawLine(0,38,87,38, KS0108_WHITE);
Display.drawLine(27,30,27, 64, KS0108_WHITE);
Display.drawLine(57,30,57, 64, KS0108_WHITE);
Display.drawLine(87,0,87, 64, KS0108_WHITE);
Display.drawLine(108,0,108, 64, KS0108_WHITE);
  Display.setCursor(92 ,4);
  Display.print("LC");
 
  //Display.setCursor(112 , 35);
 // Display.print("12");
  Display.setCursor(118 , 52);
  Display.print("0");
  
Display.setCursor(6 , 30);
  Display.print("BIO");
  Display.setCursor(31 , 30);
  Display.print("CHEM");
  Display.setCursor(63 , 30);
  Display.print("RAD");
  //anzeige

if(LC_aktiv==0){lc_counter=0;}
else{
  
lc_counter=((LifeCleaner_effekt_read-aktuell_time)/1800);
//lc_counter=36;
//Serial.print("lc_counter:");Serial.println(lc_counter);
}
  ray_counter=raywert2/5;

for( y=64;y>=64-(lc_counter);y-=2){
  Display.fillRect(90,y-1, 15, 1, KS0108_INVERSE);
 
}
 Display.setCursor(112 , y-10);
  Display.print(lc_counter/2);

  
  for( x=0;x<ray_counter;x+=10){
  Display.fillRect(x, 40, 5, 20, KS0108_INVERSE);
  }
  Display.display();


  }
  if(unterebene==0){
    ray_malus=0;
  }

      if(menue==1&&unterebene==0){
  Display.setTextSize(1);
  Display.setTextColor(WHITE);
  Display.setCursor( 0, 10);
  Display.print("Analyse");
  Display.display();
  }
      if(menue==1&&unterebene==1){
  Display.setTextSize(1);
  Display.setTextColor(WHITE);
  Display.setCursor( 0, 10);
  Display.print("Dongel auflegen");
  Display.display();
  }
  if(menue==1&&unterebene==2){
  Display.setTextSize(1);
  Display.setTextColor(WHITE);
  Display.setCursor( 0,0);
  
  Display.print("Con_Start_read:");
  Display.setCursor( 0,10);
  Display.print(Con_Start_read);
  Display.setCursor( 0,20);
  Display.print("Raywert:");
  Display.setCursor( 0,30);
  Display.print(Ray_value_extern_read/1000);
  Display.setCursor( 0,40);
    Display.print("Raywert berechnet:");
  Display.setCursor( 0,50);
  Display.print(raywert2);
  Display.display();
  }
   if(menue==1&&unterebene==3){
  Display.setTextSize(1);
  Display.setTextColor(WHITE);
  Display.setCursor( 0,0);
  Display.print("Rechte:NBCLD:");
  Display.setCursor( 0,10);
  Display.print(rights);
  Display.setCursor( 0,20);
  Display.print("LifeCleanereffekt:");
  Display.setCursor( 0,30);
  Display.print(LifeCleaner_effekt_read);
  Display.setCursor( 0,40);
  Display.print("Letzte Buchung:");
  Display.setCursor( 0,50);
  Display.print(Last_Booking_read);
  Display.display();
  }
    if(menue==1&&unterebene==4){
  Display.setTextSize(1);
  Display.setTextColor(WHITE);
  Display.setCursor( 0,0);
  Display.print("Nanoclean1");
  Display.setCursor( 0,10);
  Display.print(NanoClean_read[0]);
  Display.setCursor( 0,20);
  Display.print("Nanoclean2");
  Display.setCursor( 0,30);
  Display.print(NanoClean_read[1]);
  Display.setCursor( 0,40);
  Display.print("");
  Display.setCursor( 0,50);
  Display.print("");
  Display.display();
  }
      if(menue==1&&unterebene==5){
  Display.setTextSize(1);
  Display.setTextColor(WHITE);
  Display.setCursor( 0,0);
  Display.print("Blutwaesche1");
  Display.setCursor( 0,10);
  Display.print(BloodClean_read[0]);
  Display.setCursor( 0,20);
  Display.print("Blutwaesche2");
  Display.setCursor( 0,30);
  Display.print(BloodClean_read[1]);
  Display.setCursor( 0,40);
  Display.print("Blutwaesche3");
  Display.setCursor( 0,50);
  Display.print(BloodClean_read[2]);
  Display.display();
  }
        if(menue==1&&unterebene==6){
  Display.setTextSize(1);
  Display.setTextColor(WHITE);
  Display.setCursor( 0,0);
  Display.print("Cleanray1");
  Display.setCursor( 0,10);
  Display.print(Cleanray_read[0]);
  Display.setCursor( 0,20);
  Display.print("Cleanray2");
  Display.setCursor( 0,30);
  Display.print(Cleanray_read[1]);
  Display.setCursor( 0,40);
  Display.print("");
  Display.setCursor( 0,50);
  Display.print("");
  Display.display();
  }
  if(menue==1&&unterebene==7){
  Display.setTextSize(1);
  Display.setTextColor(WHITE);
  Display.setCursor( 0,0);
  Display.print("Dekon1");
  Display.setCursor( 0,10);
  Display.print(Dekon_read[0]);
  Display.setCursor( 0,20);
  Display.print("Dekon2");
  Display.setCursor( 0,30);
  Display.print(Dekon_read[1]);
  Display.setCursor( 0,40);
  Display.print("Dekon3");
  Display.setCursor( 0,50);
  Display.print(Dekon_read[2]);
  Display.display();
  }
  if(menue==1&&unterebene==8){
  Display.setTextSize(1);
  Display.setTextColor(WHITE);
  Display.setCursor( 0,0);
  Display.print("Dekon4");
  Display.setCursor( 0,10);
  Display.print(Dekon_read[3]);
  Display.setCursor( 0,20);
  Display.print("Dekon5");
  Display.setCursor( 0,30);
  Display.print(Dekon_read[4]);
  Display.setCursor( 0,40);
  Display.print("Dekon6");
  Display.setCursor( 0,50);
  Display.print(Dekon_read[5]);
  Display.display();
  }

   if(menue==2&&unterebene==0){
   
  Display.setTextSize(1);
  Display.setTextColor(WHITE);
  Display.setCursor( 0, 10);
  Display.print("Medi");
  Display.setCursor( 0, 20);
  Display.print("bearbeiten");
  Display.display();
  }
 if(menue==2&&unterebene==1){
  Display.setTextSize(1);
  Display.setTextColor(WHITE);
  Display.setCursor( 0, 10);
  Display.print("Update");
  Display.setCursor( 0, 20);
  Display.print("schreiben");

  Display.display();
 
  }
     if(menue==2&&unterebene==2){
  Display.setTextSize(1);
  Display.setTextColor(WHITE);
  Display.setCursor( 0, 10);
  Display.print("Nanoclean");
  Display.setCursor( 0, 20);
  Display.print("schreiben");

  Display.display();
 
  }
       if(menue==2&&unterebene==3){
  Display.setTextSize(1);
  Display.setTextColor(WHITE);
  Display.setCursor( 0, 10);
  Display.print("Dekon");
  Display.setCursor( 0, 20);
  Display.print("schreiben");

  Display.display();
 
  }
  if(menue==2&&unterebene==4){
  Display.setTextSize(1);
  Display.setTextColor(WHITE);
  Display.setCursor( 0, 10);
  Display.print("Lifecleaner");
  Display.setCursor( 0, 20);
  Display.print("schreiben");

  Display.display();
 
  }
  if(menue==2&&unterebene==5){
  Display.setTextSize(1);
  Display.setTextColor(WHITE);
  Display.setCursor( 0, 10);
  Display.print("Bloodcleaner");
  Display.setCursor( 0, 20);
  Display.print("schreiben");

  Display.display();
 
  }
   if(menue==2&&unterebene==6){
  Display.setTextSize(1);
  Display.setTextColor(WHITE);
  Display.setCursor( 0, 10);
  Display.print("Cleanray");
  Display.setCursor( 0, 20);
  Display.print("schreiben");

  Display.display();
 
  }

 if(menue==2&&unterebene==7){
  Display.setTextSize(1);
  Display.setTextColor(WHITE);
  Display.setCursor( 0, 10);
  Display.print("Drawback");
  Display.setCursor( 0, 20);
  Display.print("schreiben");

  Display.display();
 
  }
  if(menue==3&&unterebene==0){
    ray_malus=0;
  Display.setTextSize(1);
  Display.setTextColor(WHITE);
  Display.setCursor( 0, 10);
  Display.print("Raywert");
  Display.setCursor( 0, 20);
  Display.print("bearbeiten");
  Display.display();
  }

  if(menue==3&&unterebene==1){
  Display.setTextSize(1);
  Display.setTextColor(WHITE);
  Display.setCursor( 0, 5);
  Display.print("Raywert gelesen");
  Display.setCursor( 0, 15);
  Display.print(raywert);
  Display.setCursor( 35, 15);
  Display.print(msg);
  Display.setCursor( 0, 25);
  Display.print("Raywert berechnet");
  Display.setCursor( 0, 35);
  Display.print(raywert2);
  
  Display.display();
  }
 if(menue==3&&unterebene==2){
  Display.setTextSize(1);
  Display.setTextColor(WHITE);
  Display.setCursor( 0, 5);
  Display.print("Raywert");
  Display.setCursor( 0, 15);
  Display.print("bearbeiten");
 Display.setCursor( 0, 25);
  Display.print(raywert+(ray_malus/1000));
  Display.display();
 
  }
   if(menue==3&&unterebene==3){
  Display.setTextSize(1);
  Display.setTextColor(WHITE);
  Display.setCursor( 0, 10);
  Display.print("Raywert");
  Display.setCursor( 0, 20);
  Display.print("schreiben");

  Display.display();
 
  }
  if(menue==4&&unterebene==0){
  Display.setTextSize(1);
  Display.setTextColor(WHITE);
  Display.setCursor( 0, 10);
  Display.print("Lifeclean");
  Display.setCursor( 0, 20);
  Display.print("bearbeiten");

  Display.display();
  }
   if(menue==4&&unterebene==1){
  Display.setTextSize(1);
  Display.setTextColor(WHITE);
  Display.setCursor( 0, 10);
  Display.print("Lifecleaner");
  Display.setCursor( 0, 20);
  if(LC_aktiv==0){lc_basis=0;}
  else{
  lc_basis=LifeCleaner_effekt_read-aktuell_time; 
  }
  
  //Serial.print("Lifecleaner/lc_basis:");Serial.println(lc_basis);
  stunden=lc_basis/3600; 
  lc_minuten=lc_basis%3600;
  minuten=lc_minuten/60;
  lc_sekunden=lc_minuten%60;
  
  
  Display.print(stunden);
  Display.print(":");
  Display.print(minuten);
  Display.print(":");
  Display.print(lc_sekunden);
  //Display.print(LifeCleaner_effekt_read-aktuell_time);
  Display.display();
  }
     if(menue==4&&unterebene==2){
  Display.setTextSize(1);
  Display.setTextColor(WHITE);
  Display.setCursor( 0, 10);
  Display.print("Lifecleaner");
 Display.setCursor( 0, 20);
  Display.print("schreiben");
  Display.display();
  }

     if(menue==6&&unterebene==1){
  Display.setTextSize(1);
  Display.setTextColor(WHITE);
  Display.setCursor( 0, 10);
  Display.print("Dongel auflegen");
  Display.display();
  }
    if(menue==6&&unterebene==0){
  Display.setTextSize(1);
  Display.setTextColor(WHITE);
  Display.setCursor( 0, 10);
  Display.print("Checkin");
  Display.display();
  }
      if(menue==6&&unterebene==1){
  Display.setTextSize(1);
  Display.setTextColor(WHITE);
  Display.setCursor( 0, 10);
  Display.print("Dongel auflegen");
  Display.display();
  }
    if(menue==7&&unterebene==0){
  Display.setTextSize(1);
  Display.setTextColor(WHITE);
  Display.setCursor( 0, 10);
  Display.print("Reset");
  Display.display();
  }
}

//*****************************************************************************************//
