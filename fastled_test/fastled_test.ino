#include <FastLED.h>

//---LED SETUP STUFF
#define LED_PIN 6
#define COLOR_ORDER GBR

#define NUM_LEDS 60       // Change to reflect the number of LEDs you have

CRGB leds[NUM_LEDS];      //naming our LED array

//------------------SETUP------------------
void setup()  
{
  delay( 2000 ); // power-up safety delay

  FastLED.addLeds<WS2812B, LED_PIN>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( 125 );
 
}

//------------------MAIN LOOP------------------
void loop() {
  fill_solid(leds, NUM_LEDS, CHSV(2, 55, 55));  
  FastLED.show(); 
}  

