//
// Created by Michael Lewis on 8/17/15.
//

#ifndef TREELIGHTS_EXAMPLESEQUENCE_H
#define TREELIGHTS_EXAMPLESEQUENCE_H


#include "SequenceBase.h"

/// Just copy the next 2 lines and replace the words "ExampleSequence"

class ExampleSequence : public SequenceBase<ExampleSequence> {
public:
    ExampleSequence(int stripCount, int stripLength, const Clock &clock, CRGB color) : SequenceBase<ExampleSequence>::SequenceBase(stripCount, stripLength, clock), _color(color) {
    }
    inline CRGB colorForPixel(int strip, int pixel, const Context &context) {
        return _color;
    }
    
private:
    const CRGB _color;
};


#endif //TREELIGHTS_EXAMPLESEQUENCE_H
