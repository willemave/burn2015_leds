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

// Prototypes


// Define variables and constants
#define LED_PIN 13

// Add setup code
void setup()
{
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
}

// Add loop code
void loop()
{
  digitalWrite(LED_PIN, HIGH);
  delay(500);
  Serial.println("hi");
  digitalWrite(LED_PIN, LOW);
  delay(500);
}
