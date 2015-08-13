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


enum Program {
    RAINBOW,
    GRADIENT
};

enum LedMode {
    OFF,
    USER_INPUT,
    RUNNING
};

struct LedState {
    int delay = 100;
    Program program = RAINBOW;
    LedMode mode = OFF;
    int numPresses = 0;
    int ledCycleDelay = 10;
    int timeSinceInputCheck = 0;
};

LedState state;

void parse_input(void) {
    if (state.mode == RUNNING) {
        state.timeSinceInputCheck += state.ledCycleDelay;
        if (state.timeSinceInputCheck < 1000) {
            return;
        }
    }
    unsigned char bytecount = 0;
    long incomingByte = 0;
    while (Serial.available() && bytecount < 10) {
        unsigned char input = Serial.read();
        Serial.println(input);
        incomingByte = incomingByte + input;  // will not be -1
        bytecount++;
        delay(10);
    }

    if (incomingByte > 0) {
        // reset for nex

        Serial.print("switching: ");
        Serial.println(incomingByte);
        switch (incomingByte) {
            case 115: // setup
                Serial.println("setup");
                state.numPresses = 0;
                state.mode = LedMode::USER_INPUT;
                fill_solid(leds, 64, CHSV(0, 0, 0));
                incomingByte = 0;
                break;
            case 27 + 91 + 65: // up arrow
                Serial.println("up arrow");
                if (state.mode == LedMode::USER_INPUT) {
                    leds[state.numPresses % 64].setHSV(0, 128, 255);
                    state.numPresses++;
                    state.ledCycleDelay = state.numPresses * 10;
                }
                incomingByte = 0;
                break;
            case 27 + 91 + 66: // down arrow
                Serial.println("down arrow");
                if (state.mode == LedMode::USER_INPUT) {
                    state.numPresses--;
                    leds[state.numPresses % 64].setHSV(0, 0, 0);
                    state.ledCycleDelay = state.numPresses * 10;
                }
                incomingByte = 0;
                break;
            case 13 + 10: //enter
                Serial.println("enter");
                state.mode = LedMode::RUNNING;
                state.numPresses = 0;
                incomingByte = 0;
                break;
        }

        FastLED.show();
    }
}

void loop() {
    parse_input();

    if (state.mode == RUNNING) {
        switch (state.program) {
            case RAINBOW:

                for (int i = 0; i < 255; i += 5) {
                    fill_rainbow(leds, 64, i, 1);
                    FastLED.show();
                    delay(state.ledCycleDelay);
                    parse_input();
                }
                break;
        }
    }

    if (state.mode == OFF) {
        fill_solid(leds, 64, CHSV(0, 0, 0));
    }
}
