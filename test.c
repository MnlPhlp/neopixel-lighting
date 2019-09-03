#include <stdio.h>

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

int main(int argc, char const *argv[])
{
    for (int i = 0; i < 766; i++)
    {
        printf("%d, %d, %d\n",getRed(i),getGreen(i),getBlue(i));
    }
    return 0;
}
