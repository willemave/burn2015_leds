//
// hoop
//
// Description of the project
// Developed with [embedXcode](http://embedXcode.weebly.com)
//
// Author 		Willem Ave
// 				Willem Ave
//
// Date			1/24/16 8:19 PM
// Version		version
//
// Copyright	© Willem Ave, 2016
// Licence		<#licence#>
//

#include <Arduino.h>

#include <FastLED.h>
#include "dof.h"


#define LED_PIN 6
#define LED_PIN 13
#define DATA_PIN 7
#define CLOCK_PIN 14
#define NUM_LEDS 205
bool lowVoltage;
uint32_t voltageTimer;

CRGB leds[NUM_LEDS];

void setup() {
  pinMode(13, OUTPUT);
  
  FastLED.addLeds<APA102, DATA_PIN,CLOCK_PIN, GRB, DATA_RATE_MHZ(10)>(leds, NUM_LEDS);
  FastLED.setDither(BINARY_DITHER);
  FastLED.setBrightness(200);
  
  digitalWrite(13, HIGH);
  delay(200);
  digitalWrite(13, LOW);
  delay(200);
  
  setupDof();
}

void blink();
uint32_t hue = 0;
uint32_t loopTimer = 0;
float lastRoll = 0.0;
float lastYaw = 0.0;
float lastPitch = 0.0;
float deltaSum = 0.0;
int flip = 0;

void loop()
{
  Position *p = loopDof();
  
  if (millis() - loopTimer > 50) {
    lastYaw = p->yaw;
    lastRoll = p->roll;
    lastPitch = p->pitch;
    loopTimer = millis();
  }
  Serial.println( (int)lastYaw);
  if(millis() % 50000 < 10000) {
    fill_rainbow(leds, NUM_LEDS, abs((int)lastYaw) * 5);
    FastLED.show();
  } else {
    float centerOfWaveControl = sin(p->yaw / 5.0) * M_PI * 2;
    float wavelength = 30;
    float lightnessPhase = NUM_LEDS * 3;
    float colorPhase = -3;
    float hueSliceMax = sin(p->pitch / 5.0) + M_PI * 0.5;
    float hueSliceMin = sin(p->pitch / 5.0) - M_PI * 0.5;
    
    for (int p = 0; p < NUM_LEDS; p++) {
      float sinOffsetBase = (p + centerOfWaveControl) * TWO_PI / wavelength;
      
      float sinOffsetV = sinOffsetBase + lightnessPhase / wavelength;
      int v = uint8_t((sinf(sinOffsetV) + 1) * 0.5 * 255);
      float sinOffsetH = sinOffsetBase + colorPhase;
      float sinOffsetAdjusted = sinOffsetH / TWO_PI;
      float hueFloat = fmodf(
                             fabsf((roundf(sinOffsetAdjusted) - sinOffsetAdjusted)) * (hueSliceMax - hueSliceMin) + hueSliceMin +
                             TWO_PI, TWO_PI);
      
      uint8_t h = uint8_t(hueFloat / TWO_PI * 255);
      
      leds[p].setHSV(h, 255, v);
    }
    
    FastLED.show();
  }
  
}

/*
 // be sure to set the ADC to use the external reference, put the following in your setup():
 analogReadAveraging(32); // this one is optional.
 */
uint32_t getInputVoltage(){ // for Teensy 3.1, only valid between 2.0V and 3.5V. Returns in millivolts.
  uint32_t x = analogRead(39);
  return (178*x*x + 2688743864 - 1182047 * x) / 371794;
}