#include <FastLED.h>

//---LED SETUP STUFF
#define LED_PIN 6
#define COLOR_ORDER GBR

#define NUM_LEDS 60       // Change to reflect the number of LEDs you have

CRGB leds[NUM_LEDS];      //naming our LED array

//------------------SETUP------------------
void setup()  
{
    pinMode(13, OUTPUT);
//  digitalWriteFast(13, HIGH);
//  delay( 2000 ); // power-up safety delay
//  Serial.print("HI");
//  FastLED.addLeds<WS2812B, LED_PIN>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
//  FastLED.setBrightness( 125 );
//  digitalWriteFast(13, LOW);
}

//------------------MAIN LOOP------------------
void loop() {
//  fill_solid(leds, NUM_LEDS, CHSV(2, 55, 55));  
//  FastLED.show(); 

  digitalWrite(13, HIGH);
  delay( 100 ); // power-up safety delay
  digitalWrite(13, LOW);
  delay( 100 );
}  
