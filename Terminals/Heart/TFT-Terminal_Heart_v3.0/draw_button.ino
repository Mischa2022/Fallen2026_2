void draw_ebene(int option)
{

if(option==0){  //Godzilla
if(konfig!=true){
  myGLCD.setColor(VGA_BLACK);
  myGLCD.fillRoundRect (0, 30, 119, 799);
  myGLCD.fillRoundRect (120, 531, 479, 799);
  myGLCD.drawBitmap(9,40,100,98,godzilla);
  }

//start mit vier Buttons
  
myGLCD.setFont(BigFont);

button_paint(b_h[0][0],b_h[0][1],100,22,VGA_SILVER,head[0],1); //Menue
button_paint(b_h[1][0],b_h[1][1],100,22,VGA_SILVER,head[1],1); //Medis
button_paint(b_h[2][0],b_h[2][1],100,22,VGA_SILVER,head[2],1); //Admin
button_paint(b_h[3][0],b_h[3][1],100,22,VGA_SILVER,head[3],1); //Com

if(menue==true){

  button_paint(b_s[1][0],b_s[1][1],90,50,VGA_BLUE,menue1[0],0); //Analyse
  button_paint(b_s[3][0],b_s[3][1],90,50,VGA_BLUE,menue1[1],0); //Checkin
  button_paint(b_s[5][0],b_s[5][1],90,50,VGA_BLUE,menue1[2],0); //Reset
  
  myGLCD.setColor(VGA_BLACK);
  myGLCD.fillRoundRect (9, 221, 101, 329);
  myGLCD.fillRoundRect (9, 381, 101, 489);
  myGLCD.fillRoundRect (9, 541, 119, 799);
  
}
else if(medis==true){
  
  //Medis

button_paint(b_s[1][0],b_s[1][1],90,50,VGA_BLUE,med[0],0);//Dekon
button_paint(b_s[2][0],b_s[2][1],90,50,VGA_BLUE,med[1],0);//Blood
button_paint(b_s[3][0],b_s[3][1],90,50,VGA_BLUE,med[2],0);//Nano
button_paint(b_s[4][0],b_s[4][1],90,50,VGA_BLUE,med[3],0);//Life
button_paint(b_s[5][0],b_s[5][1],90,50,VGA_BLUE,med[4],0);//Clean
button_paint(b_s[6][0],b_s[6][1],90,50,VGA_BLUE,med[5],0);//+date
button_paint(b_s[7][0],b_s[7][1],90,50,VGA_BLUE,med[6],0);//Draw

  myGLCD.setColor(VGA_BLACK);
  myGLCD.fillRoundRect (0, 701, 119, 799);
  
}

else if (admin1==true){

button_paint(b_s[1][0],b_s[1][1],90,50,VGA_BLUE,admin[0],0);//Typus
button_paint(b_s[2][0],b_s[2][1],90,50,VGA_BLUE,admin[1],0);//Ray
button_paint(b_s[3][0],b_s[3][1],90,50,VGA_BLUE,admin[2],0);//Life
button_paint(b_s[4][0],b_s[4][1],90,50,VGA_BLUE,admin[3],0);//right

  myGLCD.setColor(VGA_BLACK);
  myGLCD.fillRoundRect (0, 461, 119, 799);

}

else if(com==true){
   
button_paint(b_s[1][0],b_s[1][1],90,50,VGA_BLUE,com1[0],0);//Mode
button_paint(b_s[2][0],b_s[2][1],90,50,VGA_BLUE,com1[1],0);//Cont
button_paint(b_s[3][0],b_s[3][1],90,50,VGA_BLUE,com1[2],0);//M.del
button_paint(b_s[4][0],b_s[4][1],90,50,VGA_BLUE,com1[3],0);//M.log
button_paint(b_s[5][0],b_s[5][1],90,50,VGA_BLUE,com1[4],0);//Clock



button_paint(b_s[8][0],b_s[8][1],90,50,VGA_FUCHSIA,com1[7],0); // Konfigbearbeiten
  
}  
else{

  myGLCD.setColor(VGA_BLACK);
  myGLCD.fillRoundRect (0, 141, 119, 799);
  
}

if(zeit==true){
  button_paint(b_s[6][0],b_s[6][1],90,50,VGA_SILVER,com1[5],0); // CSend

        button_paint(130,90,24,24,VGA_LIME,"+",0);
        button_paint(190,90,24,24,VGA_LIME,"+",0);
        button_paint(300,90,24,24,VGA_LIME,"+",0);
        button_paint(360,90,24,24,VGA_LIME,"+",0);
        button_paint(420,90,24,24,VGA_LIME,"+",0);
   
       // button_paint2(125,90,374,50,VGA_FUCHSIA,myTime,0);
       button_paint2(125,120,374,50,VGA_FUCHSIA,"",0);
       

myGLCD.printNumI(stu, 130,130);
myGLCD.print(":", 160,130); 
myGLCD.printNumI(minu,180,130);
myGLCD.print(":", 210,130); 
myGLCD.printNumI(sek, 220,130);

myGLCD.printNumI(tag,300,130);
myGLCD.print("-", 330,130); 
myGLCD.printNumI(mona, 340,130);
myGLCD.print("-", 370,130); 
myGLCD.printNumI(jahr, 390,130);

        button_paint(130,180,24,24,VGA_BLUE,"-",0);
        button_paint(190,180,24,24,VGA_BLUE,"-",0);
        button_paint(300,180,24,24,VGA_BLUE,"-",0);
        button_paint(360,180,24,24,VGA_BLUE,"-",0);
        button_paint(420,180,24,24,VGA_BLUE,"-",0);

        button_paint2(125,250,374,50,VGA_SILVER,"Set time",1);

        ausgabe_paint(125,370,374,50,VGA_FUCHSIA,timer,"");
  
}


if(konfig==true){
  

  myGLCD.setColor(VGA_BLACK);
  myGLCD.fillRoundRect (120, 33,479,55);
  myGLCD.fillRoundRect (0, 39, 119, 799);
  myGLCD.fillRoundRect (119,55,479,799);
  
  button_paint2(b_k[0][0],b_k[0][1],90,50,VGA_FUCHSIA,konfi2[0],0);//Con
  button_paint2(b_k[0][0]+100,b_k[0][1],359,50,VGA_FUCHSIA,konfigwerte[0],"");  
  button_paint2(b_k[1][0],b_k[1][1],90,50,VGA_FUCHSIA,konfi2[1],0);//Start 
  button_paint2(b_k[2][0],b_k[2][1],90,50,VGA_FUCHSIA,konfi2[2],0);//Tage
  button_paint2(b_k[3][0],b_k[3][1],90,50,VGA_FUCHSIA,konfi2[3],0);//Dosis
  //abhier fünf buttons pro medi
  button_paint2(b_k[4][0],b_k[4][1],90,50,VGA_FUCHSIA,konfi2[4],0);//Clean
  button_paint2(b_k[5][0],b_k[5][1],90,50,VGA_FUCHSIA,konfi2[5],0);//Life
  button_paint2(b_k[6][0],b_k[6][1],90,50,VGA_FUCHSIA,konfi2[6],0);//Blood
  button_paint2(b_k[7][0],b_k[7][1],90,50,VGA_FUCHSIA,konfi2[7],0);//Nano  
  button_paint2(b_k[8][0],b_k[8][1],90,50,VGA_FUCHSIA,konfi2[8],0);//Dekon  

if(konfig_wert!=-1){
  wert=konfigwerte[konfig_wert].toInt();
 }
//0 Conname
if(konfig_wert!=1){button_paint2(b_k[1][0]+100,b_k[1][1],359,50,VGA_FUCHSIA,konfigwerte[1],"");}else{button_paint2(b_k[1][0]+100,b_k[1][1],359,50,VGA_SILVER,konfigwerte[1],"");}
//2 UTC
//3 Korrektur

if(konfig_wert!=4){button_paint2(b_k[2][0]+100,b_k[2][1],359,50,VGA_FUCHSIA,konfigwerte[4],"");}
else{
  button_paint2(b_k[2][0]+100,b_k[2][1],359,50,VGA_SILVER,konfigwerte[4],"");
}

if(konfig_wert!=5){button_paint2(b_k[3][0]+100,b_k[3][1],359,50,VGA_FUCHSIA,konfigwerte[5],"");}
else{
  button_paint2(b_k[3][0]+100,b_k[3][1],359,50,VGA_SILVER,konfigwerte[5],"");
}

if(konfig_wert!=24){button_paint2(b_k[8][0]+370,b_k[8][1],80,50,VGA_FUCHSIA,konfigwerte[24],"");}
else{
  button_paint2(b_k[8][0]+370,b_k[8][1],80,50,VGA_SILVER,konfigwerte[24],"");
  button_paint2(b_k[8][0]+370,b_k[8][1]+50,80,30,VGA_SILVER,Einh[3],"");
}

if(konfig_wert!=23){button_paint2(b_k[8][0]+280,b_k[8][1],80,50,VGA_FUCHSIA,konfigwerte[23],"");}
else{
  button_paint2(b_k[8][0]+280,b_k[8][1],80,50,VGA_SILVER,konfigwerte[23],"");
  button_paint2(b_k[8][0]+280,b_k[8][1]+50,80,30,VGA_SILVER,Einh[2],"");
}

if(konfig_wert!=22){button_paint2(b_k[8][0]+190,b_k[8][1],80,50,VGA_FUCHSIA,konfigwerte[22],"");}
else{
  button_paint2(b_k[8][0]+190,b_k[8][1],80,50,VGA_SILVER,konfigwerte[22],"");
  button_paint2(b_k[8][0]+190,b_k[8][1]+50,80,30,VGA_SILVER,Einh[1],"");
}

if(konfig_wert!=21){button_paint2(b_k[8][0]+100,b_k[8][1],80,50,VGA_FUCHSIA,konfigwerte[21],"");}
else{
  button_paint2(b_k[8][0]+100,b_k[8][1],80,50,VGA_SILVER,konfigwerte[21],"");
  button_paint2(b_k[8][0]+100,b_k[8][1]+50,80,30,VGA_SILVER,Einh[0],"");
}

if(konfig_wert!=20){button_paint2(b_k[7][0]+370,b_k[7][1],80,50,VGA_FUCHSIA,konfigwerte[20],"");}
else{
  button_paint2(b_k[7][0]+370,b_k[7][1],80,50,VGA_SILVER,konfigwerte[20],"");
  button_paint2(b_k[7][0]+370,b_k[7][1]+50,80,30,VGA_SILVER,Einh[3],"");
}

if(konfig_wert!=19){button_paint2(b_k[7][0]+280,b_k[7][1],80,50,VGA_FUCHSIA,konfigwerte[19],"");}
else{
  button_paint2(b_k[7][0]+280,b_k[7][1],80,50,VGA_SILVER,konfigwerte[19],"");
  button_paint2(b_k[7][0]+280,b_k[7][1]+50,80,30,VGA_SILVER,Einh[2],"");
}

if(konfig_wert!=18){button_paint2(b_k[7][0]+190,b_k[7][1],80,50,VGA_FUCHSIA,konfigwerte[18],"");}
else{
  button_paint2(b_k[7][0]+190,b_k[7][1],80,50,VGA_SILVER,konfigwerte[18],"");
  button_paint2(b_k[7][0]+190,b_k[7][1]+50,80,30,VGA_SILVER,Einh[1],"");
}

if(konfig_wert!=17){ button_paint2(b_k[7][0]+100,b_k[7][1],80,50,VGA_FUCHSIA,konfigwerte[17],"");}
else{ 
  button_paint2(b_k[7][0]+100,b_k[7][1],80,50,VGA_SILVER,konfigwerte[17],"");
  button_paint2(b_k[7][0]+100,b_k[7][1]+50,80,30,VGA_SILVER,Einh[0],"");
}

if(konfig_wert!=16){ button_paint2(b_k[6][0]+370,b_k[6][1],80,50,VGA_FUCHSIA,konfigwerte[16],"");}
else{
  button_paint2(b_k[6][0]+370,b_k[6][1],80,50,VGA_SILVER,konfigwerte[16],"");
  button_paint2(b_k[6][0]+370,b_k[6][1]+50,80,30,VGA_SILVER,Einh[3],"");
}

if(konfig_wert!=15){ button_paint2(b_k[6][0]+280,b_k[6][1],80,50,VGA_FUCHSIA,konfigwerte[15],"");}
else{ 
  button_paint2(b_k[6][0]+280,b_k[6][1],80,50,VGA_SILVER,konfigwerte[15],"");
  button_paint2(b_k[6][0]+280,b_k[6][1]+50,80,30,VGA_SILVER,Einh[2],"");
}

if(konfig_wert!=14){ button_paint2(b_k[6][0]+190,b_k[6][1],80,50,VGA_FUCHSIA,konfigwerte[14],"");}
else{ 
  button_paint2(b_k[6][0]+190,b_k[6][1],80,50,VGA_SILVER,konfigwerte[14],"");
  button_paint2(b_k[6][0]+190,b_k[6][1]+50,80,30,VGA_SILVER,Einh[1],"");
}

if(konfig_wert!=13){ button_paint2(b_k[6][0]+100,b_k[6][1],80,50,VGA_FUCHSIA,konfigwerte[13],"");}
else{ 
  button_paint2(b_k[6][0]+100,b_k[6][1],80,50,VGA_SILVER,konfigwerte[13],"");
  button_paint2(b_k[6][0]+100,b_k[6][1]+50,80,30,VGA_SILVER,Einh[0],"");
}

if(konfig_wert!=12){ button_paint2(b_k[5][0]+320,b_k[5][1],100,50,VGA_FUCHSIA,konfigwerte[12],"");}
else{ 
  button_paint2(b_k[5][0]+320,b_k[5][1],100,50,VGA_SILVER,konfigwerte[12],"");
  button_paint2(b_k[5][0]+320,b_k[5][1]+50,100,30,VGA_SILVER,Einh[3],"");
}

if(konfig_wert!=11){ button_paint2(b_k[5][0]+210,b_k[5][1],100,50,VGA_FUCHSIA,konfigwerte[11],"");}
else{
  button_paint2(b_k[5][0]+210,b_k[5][1],100,50,VGA_SILVER,konfigwerte[11],"");
  button_paint2(b_k[5][0]+210,b_k[5][1]+50,100,30,VGA_SILVER,Einh[2],"");
}

if(konfig_wert!=10){button_paint2(b_k[5][0]+100,b_k[5][1],100,50,VGA_FUCHSIA,konfigwerte[10],"");}
else{
  button_paint2(b_k[5][0]+100,b_k[5][1],100,50,VGA_SILVER,konfigwerte[10],"");
  button_paint2(b_k[5][0]+100,b_k[5][1]+50,100,30,VGA_SILVER,Einh[4],"");
}

if(konfig_wert!=9){ button_paint2(b_k[4][0]+370,b_k[4][1],80,50,VGA_FUCHSIA,konfigwerte[9],"");}
else{
  button_paint2(b_k[4][0]+370,b_k[4][1],80,50,VGA_SILVER,konfigwerte[9],"");
  button_paint2(b_k[4][0]+370,b_k[4][1]+50,80,30,VGA_SILVER,Einh[3],"");
}

if(konfig_wert!=8){ button_paint2(b_k[4][0]+280,b_k[4][1],80,50,VGA_FUCHSIA,konfigwerte[8],"");}
else{ 
  button_paint2(b_k[4][0]+280,b_k[4][1],80,50,VGA_SILVER,konfigwerte[8],"");
  button_paint2(b_k[4][0]+280,b_k[4][1]+50,80,30,VGA_SILVER,Einh[2],"");
}

if(konfig_wert!=7){ button_paint2(b_k[4][0]+190,b_k[4][1],80,50,VGA_FUCHSIA,konfigwerte[7],"");}
else{ 
  button_paint2(b_k[4][0]+190,b_k[4][1],80,50,VGA_SILVER,konfigwerte[7],"");
  button_paint2(b_k[4][0]+190,b_k[4][1]+50,80,30,VGA_SILVER,Einh[1],"");
}

if(konfig_wert!=6){ button_paint2(b_k[4][0]+100,b_k[4][1],80,50,VGA_FUCHSIA,konfigwerte[6],"");}
else{ 
  button_paint2(b_k[4][0]+100,b_k[4][1],80,50,VGA_SILVER,konfigwerte[6],"");
  button_paint2(b_k[4][0]+100,b_k[4][1]+50,80,30,VGA_SILVER,Einh[0],"");
}

/*
if(konfig_wert!=4){button_paint2(b_k[2][0]+100,b_k[2][1],359,50,VGA_FUCHSIA,konfigwerte[4]+ " Tage","");}else{button_paint2(b_k[2][0]+100,b_k[2][1],359,50,VGA_SILVER,konfigwerte[4]+ "Tage","");}
if(konfig_wert!=5){button_paint2(b_k[3][0]+100,b_k[3][1],359,50,VGA_FUCHSIA,konfigwerte[5]+ "Ray/Tag","");}else{button_paint2(b_k[3][0]+100,b_k[3][1],359,50,VGA_SILVER,konfigwerte[5]+"Ray/Tag","");}
if(konfig_wert!=6){ button_paint2(b_k[4][0]+100,b_k[4][1],80,50,VGA_FUCHSIA,konfigwerte[6]+"min","");}else{ button_paint2(b_k[4][0]+100,b_k[4][1],80,50,VGA_SILVER,konfigwerte[6]+"min","");}
if(konfig_wert!=7){ button_paint2(b_k[4][0]+190,b_k[4][1],80,50,VGA_FUCHSIA,konfigwerte[7]+"max","");}else{ button_paint2(b_k[4][0]+190,b_k[4][1],80,50,VGA_SILVER,konfigwerte[7]+"max","");}
if(konfig_wert!=8){ button_paint2(b_k[4][0]+280,b_k[4][1],80,50,VGA_FUCHSIA,konfigwerte[8]+"/con","");}else{ button_paint2(b_k[4][0]+280,b_k[4][1],80,50,VGA_SILVER,konfigwerte[8]+"/con","");}
if(konfig_wert!=9){ button_paint2(b_k[4][0]+370,b_k[4][1],80,50,VGA_FUCHSIA,konfigwerte[9]+"/tag","");}else{button_paint2(b_k[4][0]+370,b_k[4][1],80,50,VGA_SILVER,konfigwerte[9]+"/tag","");}
if(konfig_wert!=10){button_paint2(b_k[5][0]+100,b_k[5][1],100,50,VGA_FUCHSIA,konfigwerte[10]+"Std","");}else{button_paint2(b_k[5][0]+100,b_k[5][1],100,50,VGA_SILVER,konfigwerte[10]+"Std","");}
if(konfig_wert!=11){ button_paint2(b_k[5][0]+210,b_k[5][1],100,50,VGA_FUCHSIA,konfigwerte[11]+"/con","");}else{button_paint2(b_k[5][0]+210,b_k[5][1],100,50,VGA_SILVER,konfigwerte[11]+"/con","");}
if(konfig_wert!=12){ button_paint2(b_k[5][0]+320,b_k[5][1],100,50,VGA_FUCHSIA,konfigwerte[12]+"/tag","");}else{ button_paint2(b_k[5][0]+320,b_k[5][1],100,50,VGA_SILVER,konfigwerte[12]+"/tag","");}
if(konfig_wert!=13){ button_paint2(b_k[6][0]+100,b_k[6][1],80,50,VGA_FUCHSIA,konfigwerte[13]+"min","");}else{ button_paint2(b_k[6][0]+100,b_k[6][1],80,50,VGA_SILVER,konfigwerte[13]+"min","");}
if(konfig_wert!=14){ button_paint2(b_k[6][0]+190,b_k[6][1],80,50,VGA_FUCHSIA,konfigwerte[14]+"max","");}else{ button_paint2(b_k[6][0]+190,b_k[6][1],80,50,VGA_SILVER,konfigwerte[14]+"max","");}
if(konfig_wert!=15){ button_paint2(b_k[6][0]+280,b_k[6][1],80,50,VGA_FUCHSIA,konfigwerte[15]+"/con","");}else{ button_paint2(b_k[6][0]+280,b_k[6][1],80,50,VGA_SILVER,konfigwerte[15]+"/con","");}
if(konfig_wert!=16){ button_paint2(b_k[6][0]+370,b_k[6][1],80,50,VGA_FUCHSIA,konfigwerte[16]+"/tag","");}else{button_paint2(b_k[6][0]+370,b_k[6][1],80,50,VGA_SILVER,konfigwerte[16]+"/tag","");}
if(konfig_wert!=17){ button_paint2(b_k[7][0]+100,b_k[7][1],80,50,VGA_FUCHSIA,konfigwerte[17]+"min","");}else{ button_paint2(b_k[7][0]+100,b_k[7][1],80,50,VGA_SILVER,konfigwerte[17]+"min","");}
if(konfig_wert!=18){button_paint2(b_k[7][0]+190,b_k[7][1],80,50,VGA_FUCHSIA,konfigwerte[18]+"max","");}else{button_paint2(b_k[7][0]+190,b_k[7][1],80,50,VGA_SILVER,konfigwerte[18]+"max","");}
if(konfig_wert!=19){button_paint2(b_k[7][0]+280,b_k[7][1],80,50,VGA_FUCHSIA,konfigwerte[19]+"/con","");}else{button_paint2(b_k[7][0]+280,b_k[7][1],80,50,VGA_SILVER,konfigwerte[19]+"/con","");}
if(konfig_wert!=20){button_paint2(b_k[7][0]+370,b_k[7][1],80,50,VGA_FUCHSIA,konfigwerte[20]+"/tag","");}else{button_paint2(b_k[7][0]+370,b_k[7][1],80,50,VGA_SILVER,konfigwerte[20]+"/tag","");}
if(konfig_wert!=21){button_paint2(b_k[8][0]+100,b_k[8][1],80,50,VGA_FUCHSIA,konfigwerte[21]+"min","");}else{button_paint2(b_k[8][0]+100,b_k[8][1],80,50,VGA_SILVER,konfigwerte[21]+"min","");}
if(konfig_wert!=22){button_paint2(b_k[8][0]+190,b_k[8][1],80,50,VGA_FUCHSIA,konfigwerte[22]+"max","");}else{button_paint2(b_k[8][0]+190,b_k[8][1],80,50,VGA_SILVER,konfigwerte[22]+"max","");}
if(konfig_wert!=23){button_paint2(b_k[8][0]+280,b_k[8][1],80,50,VGA_FUCHSIA,konfigwerte[23]+"/con","");}else{button_paint2(b_k[8][0]+280,b_k[8][1],80,50,VGA_SILVER,konfigwerte[23]+"/con","");}
if(konfig_wert!=24){button_paint2(b_k[8][0]+370,b_k[8][1],80,50,VGA_FUCHSIA,konfigwerte[24]+"/tag","");}else{button_paint2(b_k[8][0]+370,b_k[8][1],80,50,VGA_SILVER,konfigwerte[24]+"/tag","");}
*/

       button_paint(b_n[0][0],b_n[0][1]+30,60,60,VGA_BLUE,zahlen[1],0); //1
       button_paint(b_n[1][0],b_n[1][1]+30,60,60,VGA_BLUE ,zahlen[2],0); //2
       button_paint(b_n[2][0],b_n[2][1]+30,60,60,VGA_BLUE ,zahlen[3],0); //3
       button_paint(b_n[3][0],b_n[3][1]+30,60,60,VGA_BLUE ,zahlen[4],0); //4
       button_paint(b_n[4][0],b_n[4][1]+30,60,60,VGA_BLUE ,zahlen[5],0); //5
       
       button_paint(b_n[5][0],b_n[5][1]+30,60,60,VGA_BLUE,zahlen[6],0); //6
       button_paint(b_n[6][0],b_n[6][1]+30,60,60,VGA_BLUE ,zahlen[7],0); //7
       button_paint(b_n[7][0],b_n[7][1]+30,60,60,VGA_BLUE ,zahlen[8],0); //8
       button_paint(b_n[8][0],b_n[8][1]+30,60,60,VGA_BLUE ,zahlen[9],0); //9
       button_paint(b_n[9][0],b_n[9][1]+30,60,60,VGA_BLUE ,zahlen[10],0); //10
       button_paint(b_c[3][0],b_c[3][1]+30,140,50,VGA_BLUE,befehl[0],0); // Clear
       button_paint(b_c[4][0],b_c[4][1]+30,140,50,VGA_BLUE,befehl[1],0); //   Enter

      button_paint(b_s[7][0],b_s[7][1],90,50,VGA_SILVER,com1[6],0); // KSend

}



if(typus==true){
     
        myGLCD.setColor(VGA_BLACK);
        myGLCD.fillRoundRect (0, 531, 479, 780);

      button_paint(b_c[0][0],b_c[0][1],150,60,VGA_BLUE,typus1[0],0);//Bunker
      button_paint(b_c[1][0],b_c[1][1],150,60,VGA_BLUE,typus1[1],0);//Mutant
      button_paint(b_c[2][0],b_c[2][1],150,60,VGA_BLUE,typus1[2],0);//Mensch

    }
    
    else if(ray==true){
      
       //Eingabefeld
       ausgabe_paint(120,531,359,30,VGA_FUCHSIA,wert,"");
       myGLCD.setColor(VGA_BLACK);
       myGLCD.fillRoundRect (120, 561, 479, 760);
        
       button_paint(b_n[0][0],b_n[0][1],60,60,VGA_BLUE,zahlen[1],0); //1
       button_paint(b_n[1][0],b_n[1][1],60,60,VGA_BLUE ,zahlen[2],0); //2
       button_paint(b_n[2][0],b_n[2][1],60,60,VGA_BLUE ,zahlen[3],0); //3
       button_paint(b_n[3][0],b_n[3][1],60,60,VGA_BLUE ,zahlen[4],0); //4
       button_paint(b_n[4][0],b_n[4][1],60,60,VGA_BLUE ,zahlen[5],0); //5
       
       button_paint(b_n[5][0],b_n[5][1],60,60,VGA_BLUE,zahlen[6],0); //6
       button_paint(b_n[6][0],b_n[6][1],60,60,VGA_BLUE ,zahlen[7],0); //7
       button_paint(b_n[7][0],b_n[7][1],60,60,VGA_BLUE ,zahlen[8],0); //8
       button_paint(b_n[8][0],b_n[8][1],60,60,VGA_BLUE ,zahlen[9],0); //9
       button_paint(b_n[9][0],b_n[9][1],60,60,VGA_BLUE ,zahlen[10],0); //10
        
        myGLCD.setColor(VGA_BLACK);
        myGLCD.fillRoundRect (0, 470, 100, 799);


        
        button_paint(b_c[3][0],b_c[3][1],140,50,VGA_BLUE,befehl[0],0); // Clear
        button_paint(b_c[4][0],b_c[4][1],140,50,VGA_BLUE,befehl[1],0); //   Enter
        button_paint(b_s[6][0],b_s[6][1],90,50,VGA_LIME,farben[0],1); //gruen
        button_paint(b_s[7][0],b_s[7][1],90,50,VGA_YELLOW,farben[1],1); //gelb
        button_paint(b_s[8][0],b_s[8][1],90,50,VGA_RED,farben[2],1); //rot
        
    }
    
    else if(life==true){
            
       //Eingabefeld
        ausgabe_paint(120,531,359,30,VGA_FUCHSIA,wert,"Std.");
        
        myGLCD.setColor(VGA_BLACK);
        myGLCD.fillRoundRect (120, 561, 479, 760);
        
       button_paint(b_n[0][0],b_n[0][1],60,60,VGA_BLUE,zahlen[1],0); //1
       button_paint(b_n[1][0],b_n[1][1],60,60,VGA_BLUE ,zahlen[2],0); //2
       button_paint(b_n[2][0],b_n[2][1],60,60,VGA_BLUE ,zahlen[3],0); //3
       button_paint(b_n[3][0],b_n[3][1],60,60,VGA_BLUE ,zahlen[4],0); //4
       button_paint(b_n[4][0],b_n[4][1],60,60,VGA_BLUE ,zahlen[5],0); //5
       
       button_paint(b_n[5][0],b_n[5][1],60,60,VGA_BLUE,zahlen[6],0); //6
       button_paint(b_n[6][0],b_n[6][1],60,60,VGA_BLUE ,zahlen[7],0); //7
       button_paint(b_n[7][0],b_n[7][1],60,60,VGA_BLUE ,zahlen[8],0); //8
       button_paint(b_n[8][0],b_n[8][1],60,60,VGA_BLUE ,zahlen[9],0); //9
       button_paint(b_n[9][0],b_n[9][1],60,60,VGA_BLUE ,zahlen[10],0);  //10
           

        myGLCD.setColor(VGA_BLACK);
        myGLCD.fillRoundRect (0, 561, 100, 799);

        button_paint(b_c[3][0],b_c[3][1],140,50,VGA_BLUE,befehl[0],0); // Clear
        button_paint(b_c[4][0],b_c[4][1],140,50,VGA_BLUE,befehl[1],0); //   Enter
        
        
    }
    else if(rechte==true){
      
  
        
        myGLCD.setColor(VGA_BLACK);
        myGLCD.fillRoundRect (120, 531, 479, 760);
      
       //Eingabefeld
       ausgabe_paint(120,531,359,30,VGA_FUCHSIA,wert,"");
      
          
       button_paint(b_r[0][0],b_r[0][1],60,60,VGA_BLUE,typen[0],0); //N
       button_paint(b_r[1][0],b_r[1][1],60,60,VGA_BLUE ,typen[1],0); //B
       button_paint(b_r[2][0],b_r[2][1],60,60,VGA_BLUE ,typen[2],0); //C
       button_paint(b_r[3][0],b_r[3][1],60,60,VGA_BLUE ,typen[3],0); //L
       button_paint(b_r[4][0],b_r[4][1],60,60,VGA_BLUE ,typen[4],0); //D

       button_paint(b_c[3][0],b_c[3][1],140,50,VGA_BLUE,befehl[2],0);// Write
        
    }
    else if(modus==true){
       
        
        myGLCD.setColor(VGA_BLACK);
        myGLCD.fillRoundRect (120, 531, 479, 760);

      button_paint(b_c[0][0],b_c[0][1],150,60,VGA_BLUE,mode[0],0); //Godzilla
      button_paint(b_c[1][0],b_c[1][1],150,60,VGA_BLUE,mode[1],0);// Buchen
      button_paint(b_c[2][0],b_c[2][1],150,60,VGA_BLUE,mode[2],0); //Checkin
    
    }
    
    else if(connection==true){
                   //Eingabefeld
        ausgabe_paint(120,531,359,30,VGA_FUCHSIA,wert,"");

        myGLCD.setColor(VGA_BLACK);
        myGLCD.fillRoundRect (120, 570, 460, 790);
          
       button_paint(b_n[0][0],b_n[0][1],60,60,VGA_BLUE,zahlen[1],0); //1
       button_paint(b_n[1][0],b_n[1][1],60,60,VGA_BLUE ,zahlen[2],0); //2
       button_paint(b_n[2][0],b_n[2][1],60,60,VGA_BLUE ,zahlen[3],0); //3
       button_paint(b_n[3][0],b_n[3][1],60,60,VGA_BLUE ,zahlen[4],0); //4
       button_paint(b_n[4][0],b_n[4][1],60,60,VGA_BLUE ,zahlen[5],0); //5
       
       button_paint(b_n[5][0],b_n[5][1],60,60,VGA_BLUE,zahlen[6],0); //6
       button_paint(b_n[6][0],b_n[6][1],60,60,VGA_BLUE ,zahlen[7],0); //7
       button_paint(b_n[7][0],b_n[7][1],60,60,VGA_BLUE ,zahlen[8],0); //8
       button_paint(b_n[8][0],b_n[8][1],60,60,VGA_BLUE ,zahlen[9],0); //9
       button_paint(b_n[9][0],b_n[9][1],60,60,VGA_BLUE ,zahlen[10],0); //10
       
       button_paint(b_c[3][0],b_c[3][1],140,50,VGA_BLUE,befehl[0],0); //Clear
       button_paint(b_c[4][0],b_c[4][1],140,50,VGA_BLUE,befehl[1],0); //Enter
       


/*
    myGLCD.setBackColor(VGA_BLUE);
  myGLCD.setColor(VGA_BLUE);
  myGLCD.fillRoundRect (10, 650, 100, 700);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.drawRoundRect (10, 650, 100, 700);
  myGLCD.print("ksend", 15, 667);*/
    }
      else{

      }
}

if(option==2){  //Buchung
myGLCD.drawBitmap(9,40,71,98,vaultboy3);
//start mit vier Buttons
  
myGLCD.setFont(BigFont);

button_paint(b_h[0][0],b_h[0][1],100,22,VGA_SILVER,head[0],1); //Menue
button_paint(b_h[1][0],b_h[1][1],100,22,VGA_SILVER,head[1],1); //Medis


if(menue==true){

  button_paint(b_s[1][0],b_s[1][1],90,50,VGA_BLUE,menue1[0],0); //Analyse

  
  myGLCD.setColor(VGA_BLACK);
  myGLCD.fillRoundRect (9, 221, 101, 329);
  myGLCD.fillRoundRect (9, 330, 101, 489);
  myGLCD.fillRoundRect (9, 490, 119, 799);
 
}
else if(medis==true){
  
  //Medis
  if(Nano2 ==true){button_paint(b_s[3][0],b_s[3][1],90,50,VGA_BLUE,med[2],0);}  else{}//Nano
  if(Blood2==true){button_paint(b_s[2][0],b_s[2][1],90,50,VGA_BLUE,med[1],0);}else{}//Blood
  if(Clean2==true){button_paint(b_s[5][0],b_s[5][1],90,50,VGA_BLUE,med[4],0);}else{}//Clean
  if(Life2 ==true){button_paint(b_s[4][0],b_s[4][1],90,50,VGA_BLUE,med[3],0);}else{}//Life
  if(Dekon2==true){button_paint(b_s[1][0],b_s[1][1],90,50,VGA_BLUE,med[0],0);}else{}//Dekon
  if(Draw2==true){button_paint(b_s[7][0],b_s[7][1],90,50,VGA_BLUE,med[6],0);}else{}//Draw
  if(Update2==true){button_paint(b_s[6][0],b_s[6][1],90,50,VGA_BLUE,med[5],0);}else{}//+date

  myGLCD.setColor(VGA_BLACK);
 myGLCD.fillRoundRect (0, 701, 119, 799);
  myGLCD.fillRoundRect (120, 531, 479, 799);
  
}

}

if(option==1){ //Checkin
myGLCD.drawBitmap(9,40,100,34,Logo2);
//start mit vier Buttons
  
myGLCD.setFont(BigFont);

button_paint(b_h[0][0],b_h[0][1],100,22,VGA_SILVER,head[0],1); //Menue
button_paint(b_h[2][0],b_h[2][1],100,22,VGA_SILVER,head[2],1); //Admin


if(menue==true){

  button_paint(b_s[1][0],b_s[1][1],90,50,VGA_BLUE,menue1[0],0); //Analyse
  button_paint(b_s[3][0],b_s[3][1],90,50,VGA_BLUE,menue1[1],0); //Checkin
  button_paint(b_s[5][0],b_s[5][1],90,50,VGA_BLUE,menue1[2],0); //Reset
  
  myGLCD.setColor(VGA_BLACK);
  myGLCD.fillRoundRect (9, 221, 101, 329);
  myGLCD.fillRoundRect (9, 381, 101, 489);
  myGLCD.fillRoundRect (9, 541, 119, 799);
  
}
else if(medis==true){
  
  //Medis



  myGLCD.setColor(VGA_BLACK);
  myGLCD.fillRoundRect (0, 701, 119, 799);
  
}

else if (admin1==true){

button_paint(b_s[1][0],b_s[1][1],90,50,VGA_BLUE,admin[0],0);//Typus
button_paint(b_s[2][0],b_s[2][1],90,50,VGA_BLUE,admin[1],0);//Ray
button_paint(b_s[3][0],b_s[3][1],90,50,VGA_BLUE,admin[2],0);//Life
button_paint(b_s[4][0],b_s[4][1],90,50,VGA_BLUE,admin[3],0);//right

  myGLCD.setColor(VGA_BLACK);
  myGLCD.fillRoundRect (0, 461, 119, 799);

}

else if(com==true){
   


  myGLCD.setColor(VGA_BLACK);
  myGLCD.fillRoundRect (0, 545, 100, 799);
  
}  
else{

  myGLCD.setColor(VGA_BLACK);
  myGLCD.fillRoundRect (0, 33, 119, 799);
  
}


if(typus==true){
     
        myGLCD.setColor(VGA_BLACK);
        myGLCD.fillRoundRect (0, 531, 479, 780);

      button_paint(b_c[0][0],b_c[0][1],150,60,VGA_BLUE,typus1[0],0);//Bunker
      button_paint(b_c[1][0],b_c[1][1],150,60,VGA_BLUE,typus1[1],0);//Mutant
      button_paint(b_c[2][0],b_c[2][1],150,60,VGA_BLUE,typus1[2],0);//Mensch

    }
    
    else if(ray==true){
      
       //Eingabefeld
       ausgabe_paint(120,531,359,30,VGA_FUCHSIA,wert,"");
       myGLCD.setColor(VGA_BLACK);
       myGLCD.fillRoundRect (120, 561, 479, 760);
        
       button_paint(b_n[0][0],b_n[0][1],60,60,VGA_BLUE,zahlen[1],0); //1
       button_paint(b_n[1][0],b_n[1][1],60,60,VGA_BLUE ,zahlen[2],0); //2
       button_paint(b_n[2][0],b_n[2][1],60,60,VGA_BLUE ,zahlen[3],0); //3
       button_paint(b_n[3][0],b_n[3][1],60,60,VGA_BLUE ,zahlen[4],0); //4
       button_paint(b_n[4][0],b_n[4][1],60,60,VGA_BLUE ,zahlen[5],0); //5
       
       button_paint(b_n[5][0],b_n[5][1],60,60,VGA_BLUE,zahlen[6],0); //6
       button_paint(b_n[6][0],b_n[6][1],60,60,VGA_BLUE ,zahlen[7],0); //7
       button_paint(b_n[7][0],b_n[7][1],60,60,VGA_BLUE ,zahlen[8],0); //8
       button_paint(b_n[8][0],b_n[8][1],60,60,VGA_BLUE ,zahlen[9],0); //9
       button_paint(b_n[9][0],b_n[9][1],60,60,VGA_BLUE ,zahlen[10],0); //10
        
        myGLCD.setColor(VGA_BLACK);
        myGLCD.fillRoundRect (0, 470, 100, 799);


        
        button_paint(b_c[3][0],b_c[3][1],140,50,VGA_BLUE,befehl[0],0); // Clear
        button_paint(b_c[4][0],b_c[4][1],140,50,VGA_BLUE,befehl[1],0); //   Enter
        button_paint(b_s[6][0],b_s[6][1],90,50,VGA_LIME,farben[0],1); //gruen
        button_paint(b_s[7][0],b_s[7][1],90,50,VGA_YELLOW,farben[1],1); //gelb
        button_paint(b_s[8][0],b_s[8][1],90,50,VGA_RED,farben[2],1); //rot
        
    }
    
    else if(life==true){
            
       //Eingabefeld
        ausgabe_paint(120,531,359,30,VGA_FUCHSIA,wert,"Std.");
        
        myGLCD.setColor(VGA_BLACK);
        myGLCD.fillRoundRect (120, 561, 479, 760);
        
       button_paint(b_n[0][0],b_n[0][1],60,60,VGA_BLUE,zahlen[1],0); //1
       button_paint(b_n[1][0],b_n[1][1],60,60,VGA_BLUE ,zahlen[2],0); //2
       button_paint(b_n[2][0],b_n[2][1],60,60,VGA_BLUE ,zahlen[3],0); //3
       button_paint(b_n[3][0],b_n[3][1],60,60,VGA_BLUE ,zahlen[4],0); //4
       button_paint(b_n[4][0],b_n[4][1],60,60,VGA_BLUE ,zahlen[5],0); //5
       
       button_paint(b_n[5][0],b_n[5][1],60,60,VGA_BLUE,zahlen[6],0); //6
       button_paint(b_n[6][0],b_n[6][1],60,60,VGA_BLUE ,zahlen[7],0); //7
       button_paint(b_n[7][0],b_n[7][1],60,60,VGA_BLUE ,zahlen[8],0); //8
       button_paint(b_n[8][0],b_n[8][1],60,60,VGA_BLUE ,zahlen[9],0); //9
       button_paint(b_n[9][0],b_n[9][1],60,60,VGA_BLUE ,zahlen[10],0);  //10
           

        myGLCD.setColor(VGA_BLACK);
        myGLCD.fillRoundRect (0, 561, 100, 799);

        button_paint(b_c[3][0],b_c[3][1],140,50,VGA_BLUE,befehl[0],0); // Clear
        button_paint(b_c[4][0],b_c[4][1],140,50,VGA_BLUE,befehl[1],0); //   Enter
        
        
    }
    else if(rechte==true){
      
  
        
        myGLCD.setColor(VGA_BLACK);
        myGLCD.fillRoundRect (120, 531, 479, 760);
      
       //Eingabefeld
       ausgabe_paint(120,531,359,30,VGA_FUCHSIA,wert,"");
      
          
       button_paint(b_r[0][0],b_r[0][1],60,60,VGA_BLUE,typen[0],0); //N
       button_paint(b_r[1][0],b_r[1][1],60,60,VGA_BLUE ,typen[1],0); //B
       button_paint(b_r[2][0],b_r[2][1],60,60,VGA_BLUE ,typen[2],0); //C
       button_paint(b_r[3][0],b_r[3][1],60,60,VGA_BLUE ,typen[3],0); //L
       button_paint(b_r[4][0],b_r[4][1],60,60,VGA_BLUE ,typen[4],0); //D

       button_paint(b_c[3][0],b_c[3][1],140,50,VGA_BLUE,befehl[2],0);// Write
        
    }
    else if(modus==true){
       
        
        myGLCD.setColor(VGA_BLACK);
        myGLCD.fillRoundRect (120, 531, 479, 760);

    
    }
    
    else if(connection==true){
                   //Eingabefeld
        ausgabe_paint(120,531,359,30,VGA_FUCHSIA,wert,"");

        myGLCD.setColor(VGA_BLACK);
        myGLCD.fillRoundRect (120, 570, 460, 799);
          
    }
      else{
        //Reset eingabefelder
        
        myGLCD.setColor(VGA_BLACK);
        myGLCD.fillRoundRect (120, 531, 479, 799);
      }
}

}
