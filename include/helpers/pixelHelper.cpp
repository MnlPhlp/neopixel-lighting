#include "../constants.h"
#include <IRremote.h>

extern Adafruit_NeoPixel neoPixels;
extern IRrecv recv;

namespace myPixels
{
    void show(){
        bool shown = false;
        while (!shown){
            if (recv.isIdle()){
                // wait for the ir reciver to not destroy current input
                neoPixels.show();
                shown = true;
            }
        }
    }
    
    void setPixelColor(int i, uint8_t r, uint8_t g, uint8_t b){
        r *= (double)G_brightness/255;
        g *= (double)G_brightness/255;
        b *= (double)G_brightness/255;
        neoPixels.setPixelColor(i,r,g,b);
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
        show();
        
    }

    void setAllPixels(uint32_t c){
        uint8_t r = (uint8_t)(c >> 16);
        uint8_t g = (uint8_t)(c >>  8);
        uint8_t b = (uint8_t)c;
        setAllPixels(r,g,b);
    }

    void turnOff(){
        neoPixels.clear();
        show();
    }
} // namespace pixels
