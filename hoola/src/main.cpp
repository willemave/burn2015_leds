#include <FastLED.h>
#include <IRremote.h>
#include <burnutils.h>

#define LED_PIN 6
#define COLOR_ORDER GBR
#define IR_RECV_PIN 22
#define NUM_LEDS 60       // Change to reflect the number of LEDs you have

CRGB leds[NUM_LEDS];      //naming our LED array
IRrecv irrecv(IR_RECV_PIN);
decode_results ir_results;

BurnUtils bu = BurnUtils(Serial) ;

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


}


void loop() {
//
    bu.heartbeat();
//  fill_solid(leds, NUM_LEDS, CHSV(2, 55, 55));
//  FastLED.show();

}