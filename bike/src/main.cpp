#include <FastLED.h>

#define LED_PIN 22
#define NUM_LEDS 120       // Change to reflect the number of LEDs you have

CRGB leds[NUM_LEDS];      //naming our LED array

void setup() {
// pin setups!
    pinMode(13, OUTPUT);

    Serial.begin(9600);

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


extern "C" int _kill(int pid, int sig) { return 0; }
extern "C" int _getpid(void) { return 1; }

void loop() {
    float centerOfWaveControl = NUM_LEDS * sin(((millis() % 50000) / 50000.0) * TWO_PI);
    float wavelength = 10;
    float lightnessPhase = NUM_LEDS * 3;
    float colorPhase = -3;
    float hueSliceMax = cos(centerOfWaveControl * 0.01) * 10 + M_PI * 0.5;
    float hueSliceMin = cos(centerOfWaveControl * 0.01) * 10 - M_PI * 0.5;

    Serial.printf("%f \r\n", centerOfWaveControl);

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


