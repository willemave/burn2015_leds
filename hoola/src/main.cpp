#include <FastLED.h>
#include <FastIR.h>
#include <arm_math.h>
#include <Snooze.h>
#include <array>
#include "star.h"

#define LED_PIN 6
#define NUM_LEDS 158       // Change to reflect the number of LEDs you have

#define KEY_LEFT 3133634137
#define KEY_UP 311950593
#define KEY_RIGHT 2057506049
#define KEY_DOWN 3882880046
#define KEY_ENTER 1877724673
#define KEY_SETUP 1185051201
#define KEY_STOP 491731969
#define KEY_DECREASE 760572105
#define KEY_INCREASE 2110867777

#define KEY_ONE 2512531289
#define KEY_TWO 766052185
#define KEY_THREE 945833561
#define KEY_FOUR 1751557505
#define KEY_FIVE 3278554817
#define KEY_SIX 3438347865
#define KEY_SEVEN 185783425
#define KEY_EIGHT 793088073
#define KEY_NINE 1489764929

CRGB leds[NUM_LEDS];      //naming our LED array
FastIR ir;

static int32_t lastNow = 0;
static int frameNum = 0;
std::vector<int> starData;

void tree();

void rainbow();

void star();

void setup() {
// pin setups!
    pinMode(13, OUTPUT);

// let's get some debugs
    Serial.begin(9600);

// fast led?
    FastLED.addLeds<WS2812, LED_PIN>(leds, NUM_LEDS);
    FastLED.setDither(BINARY_DITHER);
    FastLED.setBrightness(50);
}


enum Program {
    RAINBOW = 1,
    TREE = 2,
    CHECKER = 3,
    STAR = 4,
    RANDOM = 5,
    SOLID = 6
};

enum LedMode {
    RUNNING,
    OFF
};

struct LedState {
    Program program = RAINBOW;
    LedMode mode = RUNNING;
    unsigned int hertz = 1;
    unsigned int x = 0;
    unsigned int y = 0;
};

LedState state;

void CaptureInput(void) {
    uint32_t key;

    key = ir.getkeypress();

    if (key > 0) {
        Serial.printf("%u \r\n", key);
        switch (key) {
            case KEY_ONE:
                state.program = RAINBOW;
                break;
            case KEY_TWO:
                state.program = TREE;
                break;
            case KEY_THREE:
                state.program = CHECKER;
                state.x = 27;
                break;
            case KEY_FOUR:
                state.program = STAR;
                state.x = 5;
                state.y = 60;
                break;
            case KEY_FIVE:
                state.program = RANDOM;
                state.x = 3;
                break;
            case KEY_SIX:
                state.program = SOLID;
                break;
            case KEY_INCREASE:
                state.hertz = qadd8(state.hertz, 1);
                break;
            case KEY_DECREASE:
                state.hertz = qsub8(state.hertz, 1);
                break;
            case KEY_UP:
                state.y = qadd8(state.y, 1);
                break;
            case KEY_DOWN:
                state.y = qsub8(state.y, 1);
                break;
            case KEY_LEFT:
                state.x = qsub8(state.x, 1);
                break;
            case KEY_RIGHT:
                state.x = qadd8(state.x, 1);
                break;
            case KEY_ENTER:
                state.mode = LedMode::RUNNING;
                break;
            case KEY_STOP:
                state.mode = LedMode::OFF;
                fill_solid(leds, NUM_LEDS, CHSV(0, 0, 0));
                FastLED.show();
                Snooze.idle();
                break;
        }

        if (state.program == STAR) {
            starData = build_star(state.y, state.x);
        }

        Serial.printf("program:%i, mode:%i, hz:%i, x:%i, y:%i \r\n", state.program, state.mode, state.hertz, state.x,
                      state.y);
    }
}

void rainbow() {
    fill_rainbow(leds, NUM_LEDS, (uint8_t) ((millis() / (10 * state.hertz)) % 255), 1);
    FastLED.show();
}

static const int pixelsPerEdge = 16;
static const int edgeCount = 10;

void tree() {

    float timePast = (millis()) / (state.hertz * 1000.0);

    double period = 1.0;

    double sliceSizeMult = 2.0 / (state.x + 1);
    double sliceSizePhase = fmod(timePast * sliceSizeMult, M_PI * 2);

    float colorSliceSizeMin = 60.0;

    float colorSliceSizeSize = 60.0;

    float colorSliceSize = colorSliceSizeMin + (sin(sliceSizePhase) * 0.5f + 0.5f) * colorSliceSizeSize;

    double sliceSizeMult2 = 2.0 / (state.y + 1);

    double slicePhase = fmod(timePast * sliceSizeMult2, M_PI * 2);
    float colorSliceStart = (sin(slicePhase) * 0.5f + 0.5f) * 360.0f - colorSliceSize * .5f + 360.0f;


    for (int p = 0; p < pixelsPerEdge; p++) {
        float mult = 1.0;

        float phase = fmod(timePast * mult + p / (float) (pixelsPerEdge), period) * M_PI * 2;
        float sliceOffset = sin(phase) * 0.5 + 0.5;

        uint8_t hue = uint32_t(colorSliceStart + sliceOffset * colorSliceSize) % 255;

        float mult2 = 2.0 / (50 + 1);
        float otherPhase = fmod(timePast * mult2 + p / (float) (pixelsPerEdge), period) * M_PI * 2;
        float v = sin(otherPhase) * 0.5 + 0.5;

        CRGB color = CHSV(hue, (uint8_t) (1.0 * 255), (uint8_t) (v * 255));

        for (int edge = 0; edge < edgeCount; edge++) {
            int pos = edge * pixelsPerEdge + p;
            leds[pos] = color;
        }
    }

    FastLED.show();
}

static uint8_t flopper = 0;

void checker() {
    int c1 = (state.y % 8) * 32;
    int c2 = 224 - (state.y % 8) * 32;
    if (flopper == 0) {
        int ct = c1;
        c1 = c2;
        c2 = ct;
    }
    int multiple = floor(NUM_LEDS / state.x);
    for (int i = 0; i < NUM_LEDS; i += multiple) {
        for (int j = 0; j < multiple; ++j) {
            if (i % 2 == 0) {
                leds[i + j].setHSV(c1, 255, 255);
            } else {
                leds[i + j].setHSV(c2, 255, 255);
            }
        }
    }

        FastLED.show();
    ;
    if (millis() % (state.hertz * 100) < (state.hertz * 100) / 2) {
        flopper = 1;
    } else {
        flopper = 0;
    }
    Serial.print(flopper);

}

void star() {

}
extern "C" int _kill(int pid, int sig) {return 0;}
extern "C" int _getpid(void) { return 1;}

void loop() {
    CaptureInput();
    frameNum++;
    switch (state.mode) {
        case RUNNING:
            switch (state.program) {
                case RAINBOW:
                    rainbow();
                    break;
                case TREE:
                    tree();
                    break;
                case CHECKER:
                    checker();
                    break;
                case STAR:
                    star();
                    break;
            }
            break;
        case OFF:
            // NO OP
            break;
    }
}

