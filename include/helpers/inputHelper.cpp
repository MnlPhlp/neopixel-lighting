#include "../constants.h"
extern lighting_mode mode;
extern boolean power;

namespace control
{
    void cycleModeUp() {
        mode = (lighting_mode)(mode+1)% M_Mode_Count; 
    }

    void cycleSpeedUp() {
        if (step = 1){
            if (pause >= Max_Pause){
                pause = 0;
                step = Max_Step;
            } 
            else pause += 10;
        }
        else
        {
            step--;
        }
        
    }

    void cycleColorUp() {
        switch (G_color)
        {
        case C_WhiteLow:
            G_color = C_Red;
            break;
        case C_Green:
            G_color = C_Blue;
            break;
        case C_Blue:
            G_color = C_WhiteLow;
            break;
        case C_Red:
            G_color = C_Green;
            break;
        default:
            break;
        }
    }

    void cycleBrightnessUp(){
        if (G_brightness > 245)
        {
            G_brightness = Min_Brightness;
        }
        else
        {
            G_brightness += 10;    
        }
    }
} // namespace control

namespace input
{
    // assign functions to buttons
    void setupButtons(){
        buttons[B_CYCLE_UP].action = control::cycleModeUp;
        buttons[B_CYCLE_UP].pin = 51;
        buttons[B_COLOR].action = control::cycleColorUp;
        buttons[B_COLOR].pin = 49;
        buttons[B_Speed].action = control::cycleSpeedUp;
        buttons[B_Speed].pin = 53;
        buttons[B_Brightness].pin = 47;
        buttons[B_Brightness].action = control::cycleBrightnessUp;
    }
    
    boolean handleButtonInput(){
        bool newInput = false;
        for (int i = 0; i < B_BUTTON_COUNT; i++)
        {
            boolean state = !digitalRead(buttons[i].pin);
            if (state != buttons[i].state){
                buttons[i].state = state;
                if (state){
                    buttons[i].action();
                    newInput = true;
                }
            }
        }
        return newInput;
    }

} // namespace input