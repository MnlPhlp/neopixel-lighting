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
            loopCount = 50;
            dim = !dim;
        }
        if (loopCount < 50) loopCount = 50;
        byte oldBrightness = G_brightness;
        G_brightness = (dim ? 305 - loopCount : loopCount);
        myPixels::setAllPixels(G_color);
        G_brightness = oldBrightness;
        // reset brightness in case the mode changes
    }

} // namespace modes

