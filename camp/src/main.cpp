#include <FastLED.h>
#include <IRremote.h>
#include <burnutils.h>

#define LED_PIN 6
#define COLOR_ORDER GBR
#define IR_RECV_PIN 22
#define NUM_LEDS 64       // Change to reflect the number of LEDs you have

CRGB leds[NUM_LEDS];      //naming our LED array
IRrecv irrecv(IR_RECV_PIN);
decode_results ir_results;

BurnUtils bu = BurnUtils(Serial);

void read_ir() {
    if (irrecv.decode(&ir_results)) {
        bu.ir_dump(&ir_results);
        irrecv.resume(); // Receive the next value
    }
}


void setup() {
// pin setups!
    pinMode(13, OUTPUT);
    irrecv.enableIRIn(); // Start the receiver

// let's get some debugs
    Serial.begin(9600);

// fast led?
    FastLED.addLeds<WS2812B, LED_PIN>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(125);

// hello and delay to let everything startup
    digitalWrite(13, HIGH);
    delay(500); // power-up safety delay
    digitalWrite(13, LOW);
    delay(500);
}


void loop() {
    for (int i = 0; i < 255; ++i) {
        fill_rainbow(leds, NUM_LEDS, i, 2);
        FastLED.show();
        delay(10);
    }
}