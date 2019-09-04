#include "../constants.h"
#include "../externs.h"
namespace myPixels
{
    void setAllPixels(uint32_t color){
        for (int i = 0; i < NUMPIXELS; i++)
        {
            pixels.setPixelColor(i,color);
        }
        pixels.show();
    }

    void setAllPixels(uint8_t r,uint8_t g,uint8_t b){
        for (int i = 0; i < NUMPIXELS; i++)
        {
            pixels.setPixelColor(i,r,g,b);
        }
        pixels.show();
        
    }
} // namespace pixels
