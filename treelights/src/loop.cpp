#define USE_OCTOWS2811

#if 0


#include <OctoWS2811.h>
#include <FastLED.h>

#include "SequenceBase.h"



#include "clock.h"
#include "ExampleSequence.h"

#endif

#import "Context.h"
#include "clock.h"
#include "ExampleSequence.h"
#include "Control.h"

static const int stripCount = 8;
static const int dmxChannels = 16;

/// 16 channels of DMX values
uint8_t dmxValues[dmxChannels] = {0};


uint8_t &brightnessDmxValue = dmxValues[0];

uint8_t &mult1DmxValue = dmxValues[1];
uint8_t &mult2DmxValue = dmxValues[2];
uint8_t &mult3DmxValue = dmxValues[3];

/// < 128 on channel 8 disables dithering
uint8_t &ditherMode = dmxValues[7];

// Pin layouts on the teensy 3:
// OctoWS2811: 2,14,7,8,6,20,21,5

static const int edgeCount = 4;
static const int pixelsPerEdge = 16;
static const int numLeds = edgeCount * pixelsPerEdge;

CRGB leds[stripCount * numLeds];

static int frameNum = 0;

void setupDMX();
void loopDMX();

void setup() {
    LEDS.addLeds<OCTOWS2811>(leds, numLeds);
    LEDS.setDither(BINARY_DITHER);

	setupDMX();
}

static const int TARGET_FRAME_LENGTH_MICROS = 1000000 / 400;

static const int stripLength = 64;
static int32_t lastNow = 0;


uint8_t lastDitherMode = BINARY_DITHER;

Clock sharedClock;
Context context(leds, stripLength, stripCount);

ExampleSequence exampleSequence(stripCount, stripLength, sharedClock, CHSV(255, 0, 255));
ExampleSequence exampleSequence2(stripCount, stripLength, sharedClock, CHSV(127, 127, 127));

Sequence *sequences[] = {
        &exampleSequence,
        &exampleSequence2,
};

const int SequenceBasesCount = sizeof(sequences)/sizeof(decltype(*sequences));

//
//static Context context(leds, stripLength, stripCount);
//
int currentSequenceIndex = -1;
Sequence *currentSequence = nullptr;

IdentityValueControl brightnessControl([]{return dmxValues[0];});

LinearlyInterpolatedValueControl<int> visualizationControl([]{return dmxValues[7];}, 0, SequenceBasesCount);


Control *controls[] = {
    &brightnessControl,
    &visualizationControl,
};

// shims


extern "C" int _kill(int pid, int sig) {return 0;}
extern "C" int _getpid(void) { return 1;}


void loop() {

    loopDMX();
    
    sharedClock.tick();

    for (auto c : controls) {
        c->tick(sharedClock);
    }
    
    LEDS.setBrightness(brightnessControl.value());
    
    int newSequenceIndex = visualizationControl.value();
    if (newSequenceIndex != currentSequenceIndex) {
        currentSequenceIndex = newSequenceIndex;
        currentSequence = sequences[currentSequenceIndex];
        currentSequence->initialize();
    }
    
    currentSequence->loop(&context);
    
//    exampleSequence.loop(&context);

    /*
	uint8_t newDitherMode = ditherMode < 128 ?  DISABLE_DITHER : BINARY_DITHER;

	if (newDitherMode != lastDitherMode) {
		LEDS.setDither(newDitherMode);
		lastDitherMode = newDitherMode;

		Serial.printf("DITHERING SET TO %d\n", newDitherMode);
	}

    LEDS.setBrightness(brightnessDmxValue);
	
    frameNum++;

    float timePast = (millis()) / 2000.0;

    double period = 1.0;

    double sliceSizeMult = 2.0 / (mult1DmxValue + 1);
    double sliceSizePhase = fmod(timePast * sliceSizeMult, M_PI * 2);

    float colorSliceSizeMin = 60.0;
	
    float colorSliceSizeSize = 60.0;

    float colorSliceSize = colorSliceSizeMin + (sin(sliceSizePhase) * 0.5f + 0.5f) * colorSliceSizeSize;

    double sliceSizeMult2 = 2.0 / (mult2DmxValue + 1);

    double slicePhase = fmod(timePast * sliceSizeMult2, M_PI * 2);
    float colorSliceStart = (sin(slicePhase) * 0.5f + 0.5f) * 360.0f - colorSliceSize * .5f + 360.0f;


    for (int p = 0; p < pixelsPerEdge; p++) {
        float mult = 1.0;

        float phase = fmod(timePast * mult + p / (float) (pixelsPerEdge), period) * M_PI * 2;
        float sliceOffset = sin(phase) * 0.5 + 0.5;

        uint8_t hue = uint32_t(colorSliceStart + sliceOffset * colorSliceSize) % 255;

        float mult2 = 2.0 / (mult3DmxValue + 1);
        float otherPhase = fmod(timePast * mult2 + p / (float) (pixelsPerEdge), period) * M_PI * 2;
        float v = sin(otherPhase) * 0.5 + 0.5;

        CRGB color = CHSV(hue, (uint8_t) (1.0 * 255), (uint8_t) (v * 255));

        for (int edge = 0; edge < edgeCount; edge++) {
            int pos = edge * pixelsPerEdge + p;
            int mappedPos = pos;
            for (int strip = 0; strip < stripCount; strip++) {
                leds[mappedPos + (strip * numLeds)] = color;
            }
        }
    }

    uint32_t now = micros();

    uint32_t targetNow = lastNow + TARGET_FRAME_LENGTH_MICROS;
    lastNow = now;

    if (now < targetNow){
        Serial.print("delaying");
        Serial.println(targetNow - now);
        delayMicroseconds(targetNow - now);
    }
     */

    LEDS.show();
    LEDS.countFPS();
    if (frameNum % 3000 == 0) {
        Serial.print("FPS:");
        Serial.println(LEDS.getFPS());
    }
}


uint16_t dmxStartAddress = 65;



#include <DmxReceiver.h>

DmxReceiver dmx;
IntervalTimer dmxTimer;

void dmxTimerISR(void)
{
        dmx.bufferService();
}

void setupDMX() {
        /* USB serial */
        Serial.begin(115200);

        /* DMX */
        dmx.begin();

        /* Use a timer to service DMX buffers every 1ms */
        dmxTimer.begin(dmxTimerISR, 1000);

        pinMode(LED_BUILTIN, OUTPUT);
}

int led = 0;
elapsedMillis elapsed;

void loopDMX()
{
        /* Toggle LED on every new frame */
        if (dmx.newFrame())
        {
                led = !led;
                digitalWrite(LED_BUILTIN, led);
        }

		/* Display all nonzero DMX values */
		for (int i = dmxStartAddress; i < dmxStartAddress + dmxChannels; i++) {
			dmxValues[i - dmxStartAddress] = dmx.getDimmer(i);
			
		}

        /* Dump DMX data every 10 second */
        if (elapsed > 10000) {
                elapsed -= 10000;

				for (int i = 0; i < dmxChannels; i++) {
						Serial.printf(" %d(%d):%d", i + dmxStartAddress, i, (int)dmxValues[i]);
				}
                Serial.printf("\n");
        }

}

