#include "../constants.h"

namespace control
{
    void cycleModeUp() {
        G_mode = (G_mode+1)% M_Mode_Count; 
    }
} // namespace control

namespace input
{
    // assign functions to buttons
    void setupButtons(){
        buttons[B_CYCLE_UP].action = control::cycleModeUp;
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