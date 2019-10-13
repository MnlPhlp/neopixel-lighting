#include "../constants.h"
#include <IRremote.h>

extern Adafruit_NeoPixel neoPixels;
extern IRrecv recv;

namespace myPixels
{
    void show(){
        bool shown = false;
        while (!shown){
            // wait for the ir reciver to not destroy current input
            if (recv.isIdle()){
                neoPixels.show();
                shown = true;
            }
        }
    }

    uint8_t modifyBrightness(uint8_t color, uint8_t brightness){
        return color * ((double)brightness/255);
    }

    uint32_t modifyBrightness(uint32_t color, uint8_t brightness){
        uint8_t r = modifyBrightness((uint8_t)(color >> 16),brightness);
        uint8_t g = modifyBrightness((uint8_t)(color >>  8),brightness);
        uint8_t b = modifyBrightness((uint8_t) color,brightness);
        return (uint32_t)r<<16 + (uint32_t)g<<8 + (uint32_t)b;
    }
    
    void setPixelColor(int i, uint8_t r, uint8_t g, uint8_t b,bool useGlobalBrightness = true){
        if (useGlobalBrightness){
            r = modifyBrightness(r,G_brightness);
            g = modifyBrightness(g,G_brightness);
            b = modifyBrightness(b,G_brightness);
        }
        neoPixels.setPixelColor(i,r,g,b);
    }

    void setPixelColor(int i, uint32_t color,bool useGlobalBrightness = true){
        if (useGlobalBrightness){
            color = modifyBrightness(color,G_brightness);
        }
        neoPixels.setPixelColor(i,color);
    }

    void setAllPixels(uint8_t r,uint8_t g,uint8_t b,bool useGlobalBrightness = true){
        if (useGlobalBrightness){
            r = modifyBrightness(r,G_brightness);
            g = modifyBrightness(g,G_brightness);
            b = modifyBrightness(b,G_brightness);
        }
        for (int i = 0; i < NUMPIXELS; i++)
        {
            neoPixels.setPixelColor(i,r,g,b);
        }
        show();  
    }

    void setAllPixels(uint32_t color,bool useGlobalBrightness = true){
        // split here because otherwise the color is split by the 
        // NeoPixel library for every iteration of the loop
        uint8_t r = modifyBrightness((uint8_t)(color >> 16),G_brightness);
        uint8_t g = modifyBrightness((uint8_t)(color >>  8),G_brightness);
        uint8_t b = modifyBrightness((uint8_t)color,G_brightness);
        for (int i = 0; i < NUMPIXELS; i++)
        {
            neoPixels.setPixelColor(i,r,g,b);
        }
        show();
    }

    void turnOff(){
        neoPixels.clear();
        show();
    }
} // namespace pixels
