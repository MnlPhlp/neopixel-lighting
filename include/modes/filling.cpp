#include "../all.h"

namespace modes
{
  void filling(){
    const int space = 5; //space between the points
    int maxI;
    static int stoppedPixels; //count of stoped pixels
    static bool filling = true;
    static int offset = 0;

    if (loopCount > (NUMPIXELS/2)){
      // after the first pixel reached the middle we calculate the moving region
      maxI = NUMPIXELS/2 - stoppedPixels;
    }
    else{
      maxI = loopCount;
    }

    uint32_t c1 = filling ? G_color : 0;
    uint32_t c2 = filling ? 0 : G_color;

    // moving a row of pixels with space
    for (int i = 0; i < maxI; i++)
    {
      if (i%space == offset){
        myPixels::setPixelColor(i,c1);
        myPixels::setPixelColor(i-1,c2);
        // same pixel counted from the other side of the led-strip
        myPixels::setPixelColor(NUMPIXELS-i,c1);
        myPixels::setPixelColor(NUMPIXELS-i+1,c2);
        if (i == NUMPIXELS/2 - (stoppedPixels+1)){
          if (filling){
            //if a pixel reched the end add 1 to stopped pixels
            stoppedPixels += filling ? 1 : -1;
          }
        }
      }
    }
 
    myPixels::show();

    if (stoppedPixels == NUMPIXELS/2) filling = !filling;
    offset += filling ? 1 : -1;
    if (offset == space) offset=0;
    if (offset == -1) offset = space-1;
  }
} // namespace modes