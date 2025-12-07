
int rotary_read(int mini,int maxi){
    if (result == DIR_CW) {
     
      
         counterx--;  
      if(vektor==false&&unterebene==0){
        menue=counterx;
 
     if(menue<=0){
          ebene=0;
          lock=false;
            }
          }
      else if(vektor==false&&unterebene==2&&menue==3){
        ray_malus=ray_malus-5000;
          }    
          
      if(vektor==true){
      unterebene=unterebene-1;
        }
 
 draw_mode(ebene);
 }

  
  if (result == DIR_CCW) {

        counterx++;  
        if(vektor==false&&unterebene==0){
      menue=counterx;
        }
       else if(vektor==false&&unterebene==2&&menue==3){
        ray_malus=ray_malus+5000;
          }   
           
        if(vektor==true){
      //unterebene=counterx;
      unterebene=unterebene+1;
        }
 draw_mode(ebene);
 }

  
    if (rotary.buttonPressedReleased(20)) {
      vektor=!vektor;

     draw_mode(ebene);
  }
if(menue>7){menue=7;}
    if (ebene<=0){
      ebene=0;
    }
     

    if (unterebene<=0){
      unterebene=0;
    }
      if (unterebene>=8){
        if(menue==1){
      unterebene=8;}
      else if(menue==3){
      unterebene=2;}
      else if(menue==6){
      unterebene=1;}
      else{unterebene=1;}
    }
   // Serial.print("menu");Serial.print(menue);Serial.print(" | ");Serial.print("ebene");Serial.print(ebene);Serial.print(" | ");Serial.print("unterebene");Serial.print(unterebene);Serial.println("");
}
