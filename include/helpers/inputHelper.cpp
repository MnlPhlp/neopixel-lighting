#include "../constants.h"
extern lighting_mode mode;
extern boolean power;

namespace control
{
    void cycleModeUp() {
        mode = (mode+1)% M_Mode_Count; 
    }

    void cyclePower() {
        power = !power;
    }

    void cycleColor() {
        switch (G_color)
        {
        case C_Red:
            G_color = C_Green;
            break;
        case C_Green:
            G_color = C_Blue;
            break;
        case C_Blue:
            G_color = C_Red;
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
        buttons[B_POWER].action = control::cyclePower;
        buttons[B_POWER].pin = 53;
    }
    
    void handleButtonInput(){
        for (int i = 0; i < B_BUTTON_COUNT; i++)
        {
            boolean state = !digitalRead(buttons[i].pin);
            if (state != buttons[i].state){
                buttons[i].state = state;
                if (state){
                    buttons[i].action();
                }
            }
        }
        
    }

} // namespace input