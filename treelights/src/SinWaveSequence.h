//
// Created by Michael Lewis on 8/19/15.
//

#ifndef TREELIGHTS_SINWAVESEQUENCE_H
#define TREELIGHTS_SINWAVESEQUENCE_H

#include <vector>

#include "Control.h"
#include "SequenceBase.h"

#include <math.h>

class SinWaveSequence : public SequenceBase<SinWaveSequence> {


public:
    SinWaveSequence(int stripCount, int stripLength, const Clock &clock)
            : SequenceBase(stripCount, stripLength,
                           clock) { }

    inline CRGB colorForPixel(int strip, int pixel, const Context &context) {
        int v = uint8_t((sinf((pixel + _lightnessPhase.value()) * TWO_PI / _wavelength.value()) + 1) * 0.5 * 255);
        return CHSV(0, 0, v);
    }

    virtual const std::vector<Control *> &controls() {
        return _controls;
    }
private:
    BufferedControl<LinearlyInterpolatedValueControl<float>> _lightnessPhase = BufferedControl<LinearlyInterpolatedValueControl<float>>(4, stripLength()); // This should probably be an accumulator
    BufferedControl<LinearlyInterpolatedValueControl<float>> _wavelength = BufferedControl<LinearlyInterpolatedValueControl<float>>(10, stripLength() * 2); // This should probably be an accumulator
    
    const std::vector<Control *> _controls = {&_lightnessPhase, &_wavelength};
};


#endif //TREELIGHTS_SINWAVESEQUENCE_H
