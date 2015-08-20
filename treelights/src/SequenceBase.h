#ifndef INCLUDE_SEQUENCE_BASE_H
#define INCLUDE_SEQUENCE_BASE_H

//#include <time.h>
#include "Context.h"
#include "clock.h"

class Sequence {
public:
    virtual void loop(Context *context) = 0;

    virtual void initialize() {
    }
};

// See ExampleSequence.cpp for exampple
template<class T>
class SequenceBase : public Sequence {
public:
    SequenceBase(int stripCount, int stripLength, const Clock &clock)
            :  _clock(clock), _stripCount(stripCount), _stripLength(stripLength) {
                
    }

    virtual void loop(Context *context) {
        for (int strip = 0; strip < _stripCount; ++strip) {
            for (int pixel = 0; pixel < _stripLength; ++pixel) {
                CRGB c = static_cast<T *>(this)->colorForPixel(strip, pixel, *context);
                context->setColor(strip, pixel, c);
            }
        }
    };
    
    int stripCount() {
        return _stripCount;
    }
    
    int stripLength() {
        return _stripLength;
    }
    
private:
    const Clock &_clock;
    const int _stripCount;
    const int _stripLength;
};

#endif