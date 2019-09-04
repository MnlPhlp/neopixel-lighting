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
        // calculate color as single int
        setAllPixels((r << 16) + (g << 8) +b);
    }
} // namespace pixels
