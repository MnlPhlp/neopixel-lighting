#include "../constants.h"

namespace myPixels
{
    void setPixelColor(int i, uint8_t r, uint8_t g, uint8_t b){
        r *= (double)G_brightness/255;
        g *= (double)G_brightness/255;
        b *= (double)G_brightness/255;
        pixels.setPixelColor(i,r,g,b);
    }

    void setPixelColor(int i, uint32_t c){
        uint8_t r = (uint8_t)(c >> 16);
        uint8_t g = (uint8_t)(c >>  8);
        uint8_t b = (uint8_t)c;
        setPixelColor(i,r,g,b);
    }

    void setAllPixels(uint8_t r,uint8_t g,uint8_t b){
        for (int i = 0; i < NUMPIXELS; i++)
        {
            setPixelColor(i,r,g,b);
        }
        pixels.show();
        
    }

    void setAllPixels(uint32_t c){
        uint8_t r = (uint8_t)(c >> 16);
        uint8_t g = (uint8_t)(c >>  8);
        uint8_t b = (uint8_t)c;
        setAllPixels(r,g,b);
    }

    void turnOff(){
        if (G_power){
            pixels.clear();
            pixels.show();
        }
    }
} // namespace pixels
