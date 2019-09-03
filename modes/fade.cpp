#include "../constants.h"
#include "../externs.h"

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

// just a simple color fade
void fadeAllColors(){
    // limit to 765 different colors
    if (loopCount > 765) loopCount = 0;

    for (int i = 0; i < NUMPIXELS; i++)
    {
        pixels.Color(getRed(loopCount),getGreen(loopCount),getBlue(loopCount));
    }
}