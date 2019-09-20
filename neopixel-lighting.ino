// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#include <IRremote.h>
#include "include/modes.h"
#include "include/constants.h"
#include "include/helpers.h"
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define LED_PIN        6 // On Trinket or Gemma, suggest changing this to 1
// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel neoPixels(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);
IRrecv recv(RECV_PIN);
lighting_mode mode = M_Color;
unsigned long oldMillis = millis();

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.
  neoPixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  #if NL_DEBUG
    Serial.begin(115200);
  #endif

  // setup Inputs
  input::setupButtons();
  input::setupRemote();
}

void loop(){
  lighting_mode oldMode = mode;
 // read input
  bool newInput=input::handleButtonInput();
  newInput = newInput || input::handleRemoteInput();
  // reset loopCount if mode changed
  if (oldMode != mode) loopCount = 0;
  // handle actual lighting
  if (newInput || ((millis()-oldMillis) > (pause*10) && mode != M_Off && mode != M_Color)){
    switch (mode){
      case M_Filling: modes::filling(); break;
      case M_Fade:    modes::fade(); break;
      case M_Breath:  modes::breath(); break;
      case M_Color:   myPixels::setAllPixels(G_color); break;
      case M_Off:     myPixels::turnOff(); break;
      default: break;
    }
    oldMillis = millis();
    loopCount += step;
    newInput = false;
    // Debug Output
   #if NL_DEBUG
      Serial.println("Mode: "+modeName[mode]);
      Serial.println("Color: "+String((uint8_t)(G_color >> 16))+", "+String((uint8_t)(G_color >> 8))+", "+String((uint8_t)G_color));
      Serial.println("Brightness: "+String(G_brightness));
      Serial.println("Steps: "+String(step));
      Serial.println("Pause: "+String(pause));
      for (int i = 0; i < NUMPIXELS; i++)
      {
        Serial.print(neoPixels.getPixelColor(i) == 0 ? "[ ]" : "[X]");
      }
      Serial.println();
      delay(200);
    #endif
  }
}
