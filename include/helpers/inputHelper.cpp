#include "../constants.h"
#include <IRremote.h>

extern lighting_mode mode;
extern IRrecv recv;
lighting_mode oldMode;

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

    void setColor(uint32_t color){
        G_color = color;
    }

    void turnOff(){
        oldMode = mode;
        mode = M_Off;
    }

    void turnOn(){
        if (oldMode != M_Off) 
            mode = oldMode;
        else 
            mode = M_Color;
    }

    void setMode(lighting_mode m){
        mode = m;
        Serial.println("SET Mode"); //debug
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

    void setupRemote(){
        remote[R_On].code = 0xF7C03F;
        remote[R_On].action = control::turnOn;
        remote[R_Off].code = 0xF740BF;
        remote[R_Off].action = control::turnOff;
        remote[R_Fade].code = 0xF7C837;
        remote[R_Fade].action = []{control::setMode(M_Fade);};
        remote[R_Breath].code = 0xF7E817;
        remote[R_Breath].action = []{control::setMode(M_Breath);};
        remote[R_Red].code = 0xF720DF;
        remote[R_Green].code = 0xF7A05F;
        remote[R_Blue].code = 0xF7609F;
        remote[R_White].code = 0xF7E01F;
        remote[R_Up].code = 0xF7807F;
        remote[R_Down].code = 0xF700FF;
        recv.enableIRIn();
    }

    bool handleRemoteInput(){
        decode_results results;
        bool newInput = false;
        if (recv.decode(&results)){
            Serial.println("---------------");
            Serial.println(results.value,HEX); //debug
            Serial.println("---------------");
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

} // namespace input