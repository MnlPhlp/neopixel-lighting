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
}}
namespace modes
{
    using namespace modeIntern;

        // just a simple color fade
    void fadeMyColors(){
        // limit to 765 different colors
        if (loopCount > 765) loopCount = 0;
        myPixels::setAllPixels(getRed(loopCount),getGreen(loopCount), getBlue(loopCount));
    }

    void fadeAllColors(){
        static bool invert;
        // limit to maximum value for just RGB Colors
        if (loopCount > C_White){
            loopCount = 0;
            invert = !invert;
        } 

        if (invert){
            myPixels::setAllPixels(loopCount);
        } 
        else {
            myPixels::setAllPixels(C_White - loopCount);    
        }
        
        
    }
} // namespace modes

