#ifndef INCLUDE_CONTEXT_H
#define INCLUDE_CONTEXT_H

#include <OctoWS2811.h>
#include <FastLED.h>
//#include <assert.h>

/// What you use to draw
class Context {
public:
    Context(CRGB *leds, int stripLength, int stripCount) :
    _leds(leds),
    _stripLength(stripLength),
    _stripCount(stripCount) {
    }
    
    inline void setColor(int strip, int pixel, CRGB color) {
//        assert(strip < StripLength );
//        assert(pixel < StripCount);
        _leds[strip * _stripLength + pixel] = color;
    }

    Context() = delete;

private:
    CRGB *_leds;

    int _stripLength;
    int _stripCount;
};

#endif