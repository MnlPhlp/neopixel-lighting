#include "../constants.h"
#include "../externs.h"

void filling() {
  Serial.println("space: "+String(space));  
  
  int count = 0;
  int movingDots = 0;
  space++; // without this i had to add 1 every time i use the variable
  int maxJ = NUMPIXELS/2*space-1;
  
  int i = loopCount%(NUMPIXELS/2);
  int j = loopCount%maxJ;

  pixels.clear(); // Set all pixel colors to 'off'
  if (space==1){
    {
      pixels.setPixelColor(i,0,125,0);
      pixels.setPixelColor(NUMPIXELS-i,0,125,0);
      pixels.show();
      delay(pause);
    }
    {
      pixels.setPixelColor(i,0,0,0);
      pixels.setPixelColor(NUMPIXELS-i,0,0,0);
      pixels.show();
      delay(pause);
    }
    return;
  }
  
  {
    if(j%space == 0 && movingDots < NUMPIXELS/2) movingDots ++;
    
    for(int k=0; k < movingDots; k++ ){
       if ((j-k*space) < (NUMPIXELS/2)-count){
         pixels.setPixelColor(j-k*space,0,125,0);
         pixels.setPixelColor(j-k*space-1,0,0,0);

         pixels.setPixelColor(NUMPIXELS-(j-k*space)-1,0,125,0);
         pixels.setPixelColor(NUMPIXELS-(j-k*space),0,0,0);
       }
    }
    if(j>NUMPIXELS/2-1) i++;
    if(i == space-1){
      i=0;
      count++;
    }
    pixels.show();
    delay(pause);
  }
  
  i=0;
  movingDots=0;
  
  {
    if(j%(space-1) == 0 && movingDots < NUMPIXELS/2) movingDots ++;
   
    for(int k = 0; k<movingDots; k++){
      pixels.setPixelColor(k*space-j,0,0,0);
      pixels.setPixelColor(k*space-j-1,0,125,0);

      pixels.setPixelColor(NUMPIXELS-(k*space-j)-1,0,0,0);
      pixels.setPixelColor(NUMPIXELS-(k*space-j),0,125,0);
    }
    
    pixels.show();
    delay(pause);
  }
}
