#include "../all.h"

namespace modes
{
  void filling(){
    const int space = 5; //space between the points
    int maxI;
    static int stoppedPixels; //count of stoped pixels
    static bool filling = true;
    static bool stopMore = true; //count up stopped pixels
    static int offset = 0;

    if (loopCount > (NUMPIXELS/2)){
      // after the first pixel reached the middle we calculate the moving region
      maxI = NUMPIXELS/2 - stoppedPixels;
    }
    else{
      maxI = loopCount;
    }

    if (maxI == NUMPIXELS/2) stopMore = true;

    uint32_t c1 = filling ? G_color : 0;
    uint32_t c2 = filling ? 0 : G_color;

    // moving a row of pixels with space
    for (int i = 0; i < maxI; i++)
    {
      if (i%space == offset){
        myPixels::setPixelColor(i,c1);
        myPixels::setPixelColor(i-1,c2);
        // same pixel counted from the other side of the led-strip
        myPixels::setPixelColor(NUMPIXELS-i-1,c1);
        myPixels::setPixelColor(NUMPIXELS-i,c2);
        if (i == NUMPIXELS/2 - (stoppedPixels+1)){
          //if a pixel reched the end add 1 to stopped pixels
          stoppedPixels += stopMore ? 1 : -1;
          Serial.println("Stopped: "+String(stoppedPixels)); //debug
        }
      }
    }
 
    myPixels::show();
    if (stoppedPixels == NUMPIXELS/2){
      filling = !filling;
      stopMore = false;
      stoppedPixels--;
    } 
    offset += filling ? 1 : -1;
    if (offset == space) offset=0;
    if (offset == -1) offset = space-1;
  }
} // namespace modes