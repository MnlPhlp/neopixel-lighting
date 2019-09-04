// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>

#include "include/modes.h"
#include "include/constants.h"
#include "include/helpers.h"
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        6 // On Trinket or Gemma, suggest changing this to 1

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
boolean power = true;
lighting_mode mode = M_Color;

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  Serial.begin(9600);

  // setup Buttons
  input::setupButtons();
  // setup Button Pins
  for (int i = 0; i < B_BUTTON_COUNT; i++)
  {
    pinMode(buttons[i].pin,INPUT_PULLUP);
  }
}

void loop(){
  loopCount++;
  // read input
  input::handleButtonInput();

  if (power){
    // handle actual lighting
    switch (mode){
      case M_Filling: modes::filling(); break;
      case M_Fade:    modes::fade(); break;
      case M_Breath:  modes::breath(); bereak;
      case M_Color:   myPixels::setAllPixels(G_color); break;
      default: break;
    }
  }
  else{
    if (pixels.getBrightness() != 0){
      pixels.clear();
      pixels.show();
    } 
  }
  delay(20);
}
