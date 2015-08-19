#include <FastLED.h>
#include <burnutils.h>
#include <FastIR.h>

#define LED_PIN 3
#define NUM_LEDS 158       // Change to reflect the number of LEDs you have

#define KEY_LEFT 3133634137
#define KEY_UP 311950593
#define KEY_RIGHT 2040728430
#define KEY_DOWN 3899657665
#define KEY_ENTER 1877724673
#define KEY_SETUP 1185051201
#define KEY_STOP 491731969
#define KEY_DECREASE 760572105
#define KEY_INCREASE 2110867777

CRGB leds[NUM_LEDS];      //naming our LED array
FastIR ir;

void setup() {
// pin setups!
    pinMode(13, OUTPUT);

// let's get some debugs
    Serial.begin(9600);

// fast led?
    FastLED.addLeds<WS2812, LED_PIN>(leds, NUM_LEDS);
    FastLED.setBrightness(125);

// hello and delay to let everything startup
    digitalWrite(13, HIGH);
    delay(200); // power-up safety delay
    digitalWrite(13, LOW);
    delay(200);
}


enum Program {
    RAINBOW,
    GRADIENT
};

enum LedMode {
    RUNNING,
    OFF
};

struct LedState {
    unsigned int delay = 100;
    Program program = RAINBOW;
    LedMode mode = RUNNING;
    int numPresses = 0;
    int ledCycleDelay = 10;
    int timeSinceInputCheck = 0;
    unsigned int startingColor = 0;
};

LedState state;

void CaptureInput(void) {
    uint32_t key;

    key = ir.getkeypress();

    if (key > 0) {
        Serial.printf("%u \r\n", key);
        switch (key) {
            case KEY_INCREASE: // up arrow
                Serial.println("increase");
                leds[state.numPresses % NUM_LEDS].setHSV(0, 128, 255);
                state.numPresses++;
                state.ledCycleDelay = state.numPresses * 10;
                break;
            case KEY_DECREASE: // down arrow
                Serial.println("decrease");
                if (state.numPresses > 0) {
                    state.numPresses--;
                }
                leds[state.numPresses % NUM_LEDS].setHSV(0, 0, 0);
                state.ledCycleDelay = state.numPresses * 10;
                break;
            case KEY_ENTER: //enter
                Serial.println("enter");
                state.mode = LedMode::RUNNING;
                state.numPresses = 0;
                break;
            case KEY_STOP:
                Serial.println("stop");
                state.numPresses = 0;
                state.mode = LedMode::OFF;
                fill_solid(leds, NUM_LEDS, CHSV(0, 0, 0));
                break;
        }

        FastLED.show();
    }
}


void loop() {
    CaptureInput();
    switch (state.mode) {
        case RUNNING:
            switch (state.program) {
                case RAINBOW:
                    state.startingColor = state.startingColor += 5 % 255;
                    fill_rainbow(leds, NUM_LEDS, state.startingColor, 1);

                    FastLED.show();
                    delay(state.ledCycleDelay);
                    break;
            }
            break;
        case OFF:
            // NO OP
            break;
    }
}

