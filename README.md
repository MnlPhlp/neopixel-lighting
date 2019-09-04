# neopixel-lighting
A Project for controlling neopixel led-strips with an arduino. It includes some lighting modes and inputhandling.

If You want to build this project yourself please support it by using the affiliate links in the Hardware-Section.

## Hardware
I used an <a target="_blank" href="https://www.amazon.de/gp/product/B01MA5BLQI/ref=as_li_tl?ie=UTF8&camp=1638&creative=6742&creativeASIN=B01MA5BLQI&linkCode=as2&tag=1606003112902-21&linkId=92289d6004bcd07606fce47f3d0eaa1e">Arduino Mega</a><img src="//ir-de.amazon-adsystem.com/e/ir?t=1606003112902-21&l=am2&o=3&a=B01MA5BLQI" width="1" height="1" border="0" alt="" style="border:none !important; margin:0px !important;"/> and two 5m LED strips with 300 LEDs each.
For projects with less LEDs a smaller microcontroller with less ram will also work fine.

You can basically use any arduino or comparable microcontroller and any LED-strip compatible with the Adafruit Neopixel library. The Strip I used consists of 'WS2812B' LEDs.
If you are not using a really tiny LED-strip you should power it directly with a powersupply and not with the arduino.

You also nedd three Buttons or other types of Input to control the lighting. 
One side of each Button has to be connected to ground and the other side to an IO Pin.
The Buttons are used for power,cycling the mode and cycling the color.

### Item-List
 - [Arduino Mega](https://amzn.to/2Ll3lbZ) / [Arduino Uno](https://amzn.to/2NPBand)
 - [Buttons](https://amzn.to/2PIxXIr)
 - [LED-Strip](https://amzn.to/2PIyxpB)
 - [Powersupply](https://amzn.to/2LkXDXu) (calculate about 1A per 15 LEDs depending on LED-Strip)

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
 
