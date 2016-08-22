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
  // pin setups!
  pinMode(13, OUTPUT);
  
  //// fast led?
//  FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS);
  FastLED.addLeds<APA102, DATA_PIN,CLOCK_PIN, GRB, DATA_RATE_MHZ(10)>(leds, NUM_LEDS);
  FastLED.setDither(BINARY_DITHER);
  FastLED.setBrightness(10);

  // say hello
  digitalWrite(13, HIGH);
  delay(200);
  digitalWrite(13, LOW);
  delay(200);
  
  setupDof();
  
}

void blink();
uint32_t hue = 0;
// Add loop code
// Add loop code
uint32_t loopTimer = 0;
void loop()
{
  Position *p = loopDof();
  int sum =(int) fabsf(p->yaw) + fabsf(p->yaw) + fabsf(p->yaw);
  if (millis() - loopTimer > 50) {
    
    loopTimer = millis();
    Serial.print("yaw = "); Serial.print(p->yaw);
    Serial.print(" pitch = "); Serial.print(p->pitch);
    Serial.print(" roll = "); Serial.print(p->roll);
    Serial.print(" sum = "); Serial.print(sum);
    Serial.print(" q0 = "); Serial.print(p->q[0]);
    Serial.print(" q1 = "); Serial.print(p->q[1]);
    Serial.print(" q2 = "); Serial.print(p->q[2]);
    Serial.print(" q3 = "); Serial.print(p->q[3]);
    Serial.println();
  }
  fill_rainbow(leds, NUM_LEDS, sum);
  FastLED.show();
}


/*
 // be sure to set the ADC to use the external reference, put the following in your setup():
 analogReadAveraging(32); // this one is optional.
 */
uint32_t getInputVoltage(){ // for Teensy 3.1, only valid between 2.0V and 3.5V. Returns in millivolts.
  uint32_t x = analogRead(39);
  return (178*x*x + 2688743864 - 1182047 * x) / 371794;
}