#include <FastLED.h>
#include <FastIR.h>
#include <Snooze.h>
#include <array>
#include "star.h"
#include <stdbool.h>

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

void tree();

void rainbow();

void star();

void setup() {
// pin setups!
    pinMode(13, OUTPUT);

//// fast led?
    FastLED.addLeds<WS2812, LED_PIN>(leds, NUM_LEDS);
    FastLED.setDither(BINARY_DITHER);
    FastLED.setBrightness(50);


// say hello
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
    delay(100);
    digitalWrite(13, HIGH);
    delay(100);
    digitalWrite(13, LOW);
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
    uint8_t hertz = 1;
    uint8_t x = 0;
    uint8_t y = 0;
};

LedState state;

void CaptureInput(void) {
    uint32_t key;

    key = ir.getkeypress();

    if (key > 0) {
        Serial.printf("%u \r\n", key);
        switch (key) {
            case KEY_ONE:
                state.x = 0;
                state.hertz = 1;
                state.y = 0;
                state.program = RAINBOW;
                break;
            case KEY_TWO:
                state.x = 10;
                state.hertz = 30;
                state.y = 10;
                state.program = TREE;
                break;
            case KEY_THREE:
                state.program = CHECKER;
                state.x = 27;
                state.hertz = 2;
                state.y = 0;
                break;
            case KEY_FOUR:
                state.program = STAR;
                state.x = 5;
                state.y = 60;
                state.hertz = 1;
                break;
            case KEY_FIVE:
                state.program = RANDOM;
                state.x = 5;
                state.y = 60;
                state.hertz = 1;
                break;
            case KEY_SIX:
                state.x = 3;
                state.hertz = 2;
                state.y = 32;
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
//            starData = build_star(state.y, state.x);
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
    float centerOfWaveControl = NUM_LEDS * sin(millis() % (state.hertz * 1000) * TWO_PI * 0.00004);
    float wavelength = state.x;
    float lightnessPhase = NUM_LEDS * 3;
    float colorPhase = -10;
    float hueSliceMax = cos(centerOfWaveControl * 0.01) * state.y + M_PI * 0.5;
    float hueSliceMin = cos(centerOfWaveControl * 0.01) * state.y - M_PI * 0.5;

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

        leds[p].setHSV(h, 240, v);
    }

    FastLED.show();
}

static bool flopper = false;

void checker() {
    int c1 = (state.y % 8) * 32;
    int c2 = 0;
    if (flopper == 0) {
        int ct = c1;
        c1 = c2;
        c2 = ct;
    }
    int multiple = floor(NUM_LEDS / state.x);
    for (int i = 0; i < NUM_LEDS; i += multiple) {
        for (int j = 0; j < multiple; ++j) {
            if (i % 2 == 0) {
                leds[i + j].setHSV(c1, 240, 255);
            } else {
                leds[i + j].setHSV(c2, 240, 255);
            }
        }
    }

    FastLED.show();

    flopper = millis() % (state.hertz * 100) < (state.hertz * 100) / 2;
}

void star() {

}

int currentHue = HUE_RED;
int transitionStart = 0;
int transitionLeft = 0;

void solid() {
    int timePast = millis() - lastNow;
    int transitionTime = 100 * state.x;
    int phase = state.y;

    if (timePast > state.hertz * 1000) {
        transitionStart = millis();
        lastNow = millis();
    }

    if (transitionStart > 0) {
        transitionLeft = millis() - transitionStart;
        if (transitionTime > transitionLeft) {
            int hueStep = (float)phase * (float)(millis() - transitionStart) / (float)transitionTime + currentHue;
            fill_solid(leds, NUM_LEDS, CHSV(hueStep, 240, 255));
        } else {
            currentHue = (currentHue + phase) % 255;
            transitionStart = 0;
            fill_solid(leds, NUM_LEDS, CHSV(currentHue, 240, 255));
        }
    }
    FastLED.show();
}

extern "C" int _kill(int pid, int sig) { return 0; }
extern "C" int _getpid(void) { return 1; }

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
                case SOLID:
                    solid();
                    break;
            }
            break;
        case OFF:
            // NO OP
            break;
    }
}


