#ifndef constants_include
// important settings
#define NUMPIXELS 600 // Number of pixels in the led-strip
#define USE_IR_Remote 1 // set to 0 if no IR-Reciver is connected
#define USE_Buttons 0 // set to 0 if no Buttons are connected

// optional settings
#define Max_Step 10
#define Max_Pause 100
#define Min_Brightness 50 //255 means full brightness
#define NL_DEBUG 0
// Colors
// imagine as 3 byte number with the bytes standing for Red, Green and Blue
#define C_Blue 255
#define C_Green 65280
#define C_Red 16711680
#define C_White 16777215
#define C_WhiteLow 8421504 //used because on longer strips full white often looks yellow in the middle

// Buttons
#if USE_Buttons
struct buttonInfo
{
    boolean state;
    int pin;
    void (*action)();
};

enum button_enum {B_CYCLE_UP,B_Speed,B_COLOR,B_Brightness,B_BUTTON_COUNT};
buttonInfo buttons[B_BUTTON_COUNT];
#endif //USE_Buttons

// remote
#if USE_IR_Remote
    #define RECV_PIN 7

    struct remoteInfo
    {
        uint32_t code;
        void (*action)();
    };

    enum remote_enum {R_On,R_Off,R_Fade,R_Breath,R_Filling,R_Red,R_Green,R_Blue,R_White,R_Up,R_Down,R_Remote_Count};
    remoteInfo remote[R_Remote_Count];
#endif

// Modes
enum lighting_mode {M_Filling,M_Fade,M_Breath,M_Color,M_Off,M_Mode_Count};
#if NL_DEBUG
    String modeName[] = {"Filling","Fade","Breath","Color","Off"};
#endif

// global variables
// start with simple blue
uint32_t G_color = C_Blue;
unsigned int loopCount = 0;
bool G_power = true;
byte pause = 0;
byte step = 1;
byte G_brightness = 255;

#endif
#define constants_include