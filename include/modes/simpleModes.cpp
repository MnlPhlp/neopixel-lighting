#include "../all.h"

namespace modeIntern{
    // get rgb color from int in range 0-765
    // sum is always 255 and only two colors are active
    int getRed(int n){
        if (n <= 255) return n;
        if (n >255 && n<=510) return 510-n;
        return 0;
    }
    int getGreen(int n){
        if (n>255 && n <= 510) return n-255;
        if (n >510 && n<=765) return 765-n;
        return 0;
    }
    int getBlue(int n){
        if (n <= 255) return 255-n;
        if (n >510 && n<=765) return n-510;
        return 0;
    }
}
namespace modes
{
    using namespace modeIntern;

    // just a simple color fade
    void fade(){
        // limit to 765 different colors
        if (loopCount > 765) loopCount = 0;
        myPixels::setAllPixels(getRed(loopCount),getGreen(loopCount), getBlue(loopCount));
    }

    void breath(){
        // store if dimming or getting brighter
        static bool dim = false;
        // limit brightness values
        if (loopCount >= 255) {
            loopCount = Min_Brightness;
            dim = !dim;
        }
        if (loopCount < Min_Brightness){
            loopCount = Min_Brightness;
        } 
        byte oldBrightness = G_brightness;
        G_brightness = (dim ? (255+Min_Brightness) - loopCount : loopCount);
        myPixels::setAllPixels(G_color);
        // reset brightness in case the mode changes
        G_brightness = oldBrightness;
    }

    bool turnOnOffAnimation(bool turnOn){
        if (turnOn){
            myPixels::setPixelColor(loopCount,G_color);
            myPixels::setPixelColor(NUMPIXELS-loopCount-1,G_color);
        }else
        {
            myPixels::setPixelColor(NUMPIXELS/2-loopCount-1,0);
            myPixels::setPixelColor(NUMPIXELS/2+loopCount,0);    
        }
        myPixels::show();
        if (loopCount == NUMPIXELS/2 - 1){
            loopCount = 0;
            return false; //stop transition
        } 
        else {
            return true;
        }
    }

} // namespace modes

