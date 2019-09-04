# neopixel-lighting
A Project for controlling neopixel led-strips with an arduino. It includes some lighting modes and inputhandling

## Hardware
I used an arduino Mega and two 5m LED strips with 300 LEDs each.

You can basically use any arduino or comparable microcontroller and any LED-strip compatible with the Adafruit Neopixel library.
If you are not using a really tiny LED-strip you should power it directly with a powersupply and not with the arduino.

You also nedd three Buttons or other types of Input to control the lighting. 
One side of each Button has to be connected to ground and the other side to an IO Pin.
The Buttons are used for power,cycling the mode and cycling the color.

### Pins
| Pin (Arduino Mega) | Connected Component |
| :------------------: | ------------------- |
| 49 | power-button |
| 51 | mode-button |
| 53 | color-button |
| 6 | LED-Strip control |
| GND | ground of powersuply |
| 5V | 5V connection of powersuply |

## Modes
current Modes are:
 - single color
 - fade
 - filling
 
 **always open for new mode ideas as [Issue](https://github.com/MnlPhlp/neopixel-lighting/issues) or modes as [PR](https://github.com/MnlPhlp/neopixel-lighting/pulls)**
 
 Switching the color works in all Modes except fade.
 
