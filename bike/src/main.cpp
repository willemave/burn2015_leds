#include <FastLED.h>

#define LED_PIN 16
#define NUM_LEDS 196       // Change to reflect the number of LEDs you have

void toBlack(int, int);
void nightRider(int);
void pulse();

CRGB leds[NUM_LEDS];      //naming our LED array
int stripLength = 49;
int numStrips = 4;
int counter = 0;
int fadeDelay = 500;

void setup() {
  // pin setups!
  pinMode(13, OUTPUT);
  
  Serial.begin(9600);
  
  //// fast led?
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setDither(BINARY_DITHER);
  FastLED.setBrightness(100);
}

void loop() {
  for(int i = 0; i < 255; i+=32) {
    nightRider(i);
  }
  rainbow();
}

void nightRider(int hue) {
  for(int i = 0; i < 50; i++) {
    int timer = millis();
    int step = millis() - timer;
    int strip = i % numStrips;
    while(step < fadeDelay) {
      for(int j = 0; j < 49; j++) {
        int val = (int)((255.0f / fadeDelay) * step);
        leds[strip * stripLength + j].setHSV( hue, 255, val);
        
      }
      step = millis() - timer;
      FastLED.show();
    }
    toBlack(strip, hue);
  }
}

void rainbow() {
  int hue = 0;
  int timer = millis();
  int step = millis() - timer;
  int strip = i % numStrips;
  for(int iter = 0; iter < 100; i++) {
    while(step < 100) {
      fill_rainbow(&leds[0],49,hue);
      fill_rainbow(&leds[48],49,hue);
      fill_rainbow(&leds[97],49,hue);
      fill_rainbow(&leds[146],49,hue);
    }
  }
}

void toBlack(int strip, int hue) {
  int timer = millis();
  int step = millis() - timer;
  while(step < fadeDelay) {
    for(int i = strip * stripLength; i < strip * stripLength + stripLength; i++) {
      int val = 255 - (int)((255.0f / fadeDelay) * step);
      leds[i].setHSV(hue, 255, val);
    }
    step = millis() - timer;
    FastLED.show();
  }
  
  for(int i = strip * stripLength; i < strip * stripLength + stripLength; i++) {
    leds[i].setHSV(hue, 255, 0);
  }
  FastLED.show();
}

//void loop() {
//    float centerOfWaveControl = NUM_LEDS * sin(((millis() % 50000) / 50000.0) * TWO_PI);
//    float wavelength = 10;
//    float lightnessPhase = NUM_LEDS * 3;
//    float colorPhase = -3;
//    float hueSliceMax = cos(centerOfWaveControl * 0.01) * 10 + M_PI * 0.5;
//    float hueSliceMin = cos(centerOfWaveControl * 0.01) * 10 - M_PI * 0.5;
//
//    Serial.printf("%f \r\n", centerOfWaveControl);
//
//    for (int p = 0; p < NUM_LEDS; p++) {
//        float sinOffsetBase = (p + centerOfWaveControl) * TWO_PI / wavelength;
//
//        float sinOffsetV = sinOffsetBase + lightnessPhase / wavelength;
//        int v = uint8_t((sinf(sinOffsetV) + 1) * 0.5 * 255);
//        float sinOffsetH = sinOffsetBase + colorPhase;
//        float sinOffsetAdjusted = sinOffsetH / TWO_PI;
//        float hueFloat = fmodf(
//                fabsf((roundf(sinOffsetAdjusted) - sinOffsetAdjusted)) * (hueSliceMax - hueSliceMin) + hueSliceMin +
//                TWO_PI, TWO_PI);
//
//        uint8_t h = uint8_t(hueFloat / TWO_PI * 255);
//
//        leds[p].setHSV(h, 240, v);
//    }
//
//    FastLED.show();
//}
//

