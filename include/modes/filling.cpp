#include "../all.h"

namespace modes
{
  void filling(){
    const space = 5; //space between the points
    int maxI;
    static int stoppedPixels; //count of stoped pixels
    static int offset = 0;

    if (loopCount > (NUMPIXELS/2)){
      // after the first pixel reached the middle we calculate the moving region
      maxI = NUMPIXELS/2 - stoppedPixels;
    }
    else{
      maxI = loopCount;
    }
    
    // moving a row of pixels with space
    for (int i = 0; i < maxI; i++)
    {
      if (i%space == offset){
        myPixels::setPixelColor(i,G_color);
        myPixels::setPixelColor(i-1,0);
        // same pixel counted from the other side of the led-strip
        myPixels::setPixelColor(NUMPIXELS-i,G_color);
        myPixels::setPixelColor(NUMPIXELS-i+1,0);
        if (i == NUMPIXELS/2 - (stoppedPixels+1)){
          //if a pixel reched the end add 1 to stopped pixels
          stoppedPixels++;
        }
      }
    }
 
    myPixels::show();

    offset ++;
    if (offset == space) offset=0;
  }
} // namespace modes