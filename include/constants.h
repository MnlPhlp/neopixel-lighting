#ifndef constants_include

#define NUMPIXELS 600

// Colors
// imagine as 3 byte number with the bytes standing for Red, Green and Blue
#define C_Blue 255
#define C_Green 65280
#define C_Red 16711680
#define C_White 16777215
#define C_WhiteLow 8421504


// Buttons
struct buttonInfo
{
    boolean state;
    int pin;
    void (*action)();
};

enum button_enum {B_CYCLE_UP,B_POWER,B_COLOR,B_BUTTON_COUNT};
buttonInfo buttons[B_BUTTON_COUNT];

// Modes
enum lighting_mode {M_Filling,M_Fade,M_Breath,M_Color,M_Mode_Count};

// settings
int pause = 0;

// global variables
// start with simple blue
uint32_t G_color = C_Blue;
unsigned int loopCount = 0;

#endif
#define constants_include