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
// See         ReadMe.txt for references
//

// Core library for code-sense - IDE-based

#include <Arduino.h>

// Include application, user and local libraries

#include <FastLED.h>
#include <SFE_LSM9DS0.h>
#include "dof.hpp"

// Define variables and constants
#define LED_PIN 13

// Add setup code
void setup()
{
  analogReference(EXTERNAL);
  analogReadResolution(12);
  setupdof();
}

// Add loop code
void loop()
{
  loopy();
}

/*
 // be sure to set the ADC to use the external reference, put the following in your setup():
 analogReadAveraging(32); // this one is optional.
 */
uint32_t getInputVoltage(){ // for Teensy 3.1, only valid between 2.0V and 3.5V. Returns in millivolts.
  uint32_t x = analogRead(39);
  return (178*x*x + 2688743864 - 1182047 * x) / 371794;
}