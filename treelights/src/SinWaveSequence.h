//
// Created by Michael Lewis on 8/19/15.
//

#ifndef TREELIGHTS_SINWAVESEQUENCE_H
#define TREELIGHTS_SINWAVESEQUENCE_H


#include "Control.h"
#include "SequenceBase.h"

#include <math.h>

class SinWaveSequence : public SequenceBase<SinWaveSequence> {


public:
    SinWaveSequence(int stripCount, int stripLength, const Clock &clock,
                    const ValueControl<float> &_lightnessPhase,
                        const ValueControl<float> &_wavelength)
            : SequenceBase(stripCount, stripLength,
                           clock),
              _lightnessPhase(_lightnessPhase), _wavelength(_wavelength) { }

    inline CRGB colorForPixel(int strip, int pixel, const Context &context) {
        int v = uint8_t((sinf((pixel + _lightnessPhase.value()) * TWO_PI / _wavelength.value()) + 1) * 0.5 * 255);
        return CHSV(0, 0, v);
    }

private:
    const ValueControl<float> &_lightnessPhase; // This should probably be an accumulator
    const ValueControl<float> &_wavelength; // This should probably be an accumulator
};


#endif //TREELIGHTS_SINWAVESEQUENCE_H
