#include "../constants.h"
extern lighting_mode mode;
extern boolean power;

namespace control
{
    void cycleModeUp() {
        mode = (lighting_mode)(mode+1)% M_Mode_Count; 
    }

    void cycleSpeed() {
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

    void cycleColor() {
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
} // namespace control

namespace input
{
    // assign functions to buttons
    void setupButtons(){
        buttons[B_CYCLE_UP].action = control::cycleModeUp;
        buttons[B_CYCLE_UP].pin = 51;
        buttons[B_COLOR].action = control::cycleColor;
        buttons[B_COLOR].pin = 49;
        buttons[B_POWER].action = control::cycleSpeed;
        buttons[B_POWER].pin = 53;
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