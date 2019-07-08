// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        6 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 600 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 1 // Time (in milliseconds) to pause between pixels


int space = 2;
int pause = 0;
int counting = -1;
  
void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  Serial.begin(9600);
}

void loop() {
  Serial.println("space: "+String(space));  
  int i = 0;
  int count = 0;
  int movingDots = 0;
  space++; // without this i had to add 1 every time i use the variable
  int maxJ = NUMPIXELS/2*space-1;
  
  pixels.clear(); // Set all pixel colors to 'off'
  if (space==1){
    for(int i=0; i<NUMPIXELS/2; i++){
      pixels.setPixelColor(i,0,125,0);
      pixels.setPixelColor(NUMPIXELS-i,0,125,0);
      pixels.show();
      delay(pause);
    }
    for(int i=NUMPIXELS/2; i>0; i--){
      pixels.setPixelColor(i,0,0,0);
      pixels.setPixelColor(NUMPIXELS-i,0,0,0);
      pixels.show();
      delay(pause);
    }

    counting = -counting;
    return;
  }
  
  for(int j=0; j<maxJ;j++) {
    if(j%space == 0 && movingDots < NUMPIXELS/2) movingDots ++;
    
    for(int k=0; k < movingDots; k++ ){
       if ((j-k*space) < (NUMPIXELS/2)-count){
         pixels.setPixelColor(j-k*space,0,125,0);
         pixels.setPixelColor(j-k*space-1,0,0,0);

         pixels.setPixelColor(NUMPIXELS-(j-k*space)-1,0,125,0);
         pixels.setPixelColor(NUMPIXELS-(j-k*space),0,0,0);
       }
    }
    if(j>NUMPIXELS/2-1) i++;
    if(i == space-1){
      i=0;
      count++;
    }
    pixels.show();
    delay(pause);
  }
  
  i=0;
  movingDots=0;
  
  for(int j = 0; j<maxJ; j++){
    if(j%(space-1) == 0 && movingDots < NUMPIXELS/2) movingDots ++;
   
    for(int k = 0; k<movingDots; k++){
      pixels.setPixelColor(k*space-j,0,0,0);
      pixels.setPixelColor(k*space-j-1,0,125,0);

      pixels.setPixelColor(NUMPIXELS-(k*space-j)-1,0,0,0);
      pixels.setPixelColor(NUMPIXELS-(k*space-j),0,125,0);
    }
    
    pixels.show();
    delay(pause);
  }
  
  Serial.println(String(counting));
  if (space == 11) counting = -counting;
  space += counting-1;
  if (space<0) space = 0;
  
}
