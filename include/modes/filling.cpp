#include "../all.h"

namespace modes
{
  void filling(){
    static int space = 5;
    static int offset = 0;

    if (loopCount > (NUMPIXELS/2)) loopCount=0;

    // moving a row of pixels with space
    for (int i = 0; i < loopCount; i++)
    {
      if (i%space == offset){
        myPixels::setPixelColor(i,G_color);
        myPixels::setPixelColor(i-1,0);
        myPixels::setPixelColor(NUMPIXELS-i,G_color);
        myPixels::setPixelColor(NUMPIXELS-i+1,0);
      }
    }
 
    myPixels::show();

    offset ++;
    if (offset == space) offset=0;
    
  }
} // namespace modes