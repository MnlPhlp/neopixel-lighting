#include "../constants.h"
#if IR_Remote
    #include <IRremote.h>
#endif

extern lighting_mode mode;
extern IRrecv recv;
lighting_mode oldMode = M_Color;

namespace control
{
    void cycleModeUp() {
        mode = (lighting_mode)(mode+1)% M_Mode_Count; 
    }

    void cycleSpeedDown() {
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

    void cycleSpeedUp() {
        if (step == Max_Step){
            step = 1;
            pause = Max_Pause;
        }
        else
        {
            if (pause > 0){
                if (pause<10)
                    pause = 0;
                else
                    pause -= 10;
            }
            else
            {
                step ++;
            }
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

    void cycleBrightnessDown(){
        if (G_brightness < Min_Brightness)
        {
            G_brightness = 255;
        }
        else
        {
            G_brightness -= 10;    
        }
    }   

    void setColor(uint32_t color){
        // switch to color mode if in fade or if clicked twice
        if (mode == M_Fade || G_color == color) 
            mode = M_Color;
        G_color = color;
    }

    void turnOff(){
        if (mode == M_Off) 
            // don't do anything if already off
            return;
        oldMode = mode;
        mode = M_Off;
    }

    void turnOn(){
        if (mode != M_Off)
            // don't do anything if already on
            return;
        if (oldMode == M_Off) 
            // if switched to off by cycleMode old Mode could be off
            // use color as standard mode
            mode = M_Color;
        else 
            mode = oldMode ;
    }

    void setMode(lighting_mode m){
        mode = m;
    }

    void contextUp(){
        if (mode == M_Color || mode == M_Filling)
            cycleBrightnessUp();
        else
            cycleSpeedUp();
    }

    void contextDown(){
        if (mode == M_Color)
            cycleBrightnessDown();
        else
            cycleSpeedDown();
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
        for (int i = 0; i < B_BUTTON_COUNT; i++)
        {
            pinMode(buttons[i].pin,INPUT_PULLUP);
        }
        
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
#if IR_Remote
    void setupRemote(){
        remote[R_On].code = 0xF7C03F;
        remote[R_On].action = control::turnOn;
        remote[R_Off].code = 0xF740BF;
        remote[R_Off].action = control::turnOff;
        remote[R_Fade].code = 0xF7C837;
        remote[R_Fade].action = []{control::setMode(M_Fade);};
        remote[R_Breath].code = 0xF7E817;
        remote[R_Breath].action = []{control::setMode(M_Breath);};
        remote[R_Filling].code = 0xF7F00F;
        remote[R_Filling].action = []{control::setMode(M_Filling);};
        remote[R_Red].code = 0xF720DF;
        remote[R_Red].action = []{control::setColor(C_Red);};
        remote[R_Green].code = 0xF7A05F;
        remote[R_Green].action = []{control::setColor(C_Green);};
        remote[R_Blue].code = 0xF7609F;
        remote[R_Blue].action = []{control::setColor(C_Blue);};
        remote[R_White].code = 0xF7E01F;
        remote[R_White].action = []{control::setColor(C_WhiteLow);};
        remote[R_Up].code = 0xF700FF;
        remote[R_Up].action = control::contextUp;
        remote[R_Down].code = 0xF7807F;
        remote[R_Down].action = control::contextDown;
        recv.enableIRIn();
    }

    bool handleRemoteInput(){
        decode_results results;
        bool newInput = false;
        if (recv.decode(&results)){
            for (int i = 0; i < R_Remote_Count; i++)
            {
                if (results.value == remote[i].code){
                    remote[i].action();
                }
                newInput = true;
            }
            recv.resume();
        }
        return newInput;
    }
#endif //IR_Remote
} // namespace input