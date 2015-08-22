//
// Created by Michael Lewis on 8/19/15.
//

#ifndef TREELIGHTS_SINWAVESEQUENCE_H
#define TREELIGHTS_SINWAVESEQUENCE_H

#include <vector>

#include "Control.h"
#include "SequenceBase.h"

#include <math.h>

typedef BufferedControl<LinearlyInterpolatedValueControl<float>> SmoothLinearControl;

class SinWaveSequence : public SequenceBase<SinWaveSequence> {


public:
    SinWaveSequence(int stripCount, int stripLength, const Clock &clock)
            : SequenceBase(stripCount, stripLength,
                           clock) { }

    inline CRGB colorForPixel(int strip, int pixel, const Context &context) {
        float sinOffset = (pixel + _centerOfWaveControl.value()) * TWO_PI / _wavelength.value();
        sinOffset +=  _lightnessPhase.value();
        
        int v = uint8_t((sinf(sinOffset) + 1) * 0.5 * 255);
        return CHSV(0, 0, v);
    }

    virtual const std::vector<Control *> &controls() {
        return _controls;
    }
private:
    SmoothLinearControl _lightnessPhase = SmoothLinearControl(4, stripLength()); // This should probably be an accumulator
    
    SmoothLinearControl _wavelength = SmoothLinearControl(4, stripLength() * 2);
    SmoothLinearControl _centerOfWaveControl = SmoothLinearControl(-stripLength(), 0);
    
    const std::vector<Control *> _controls = {&_lightnessPhase, &_wavelength, &_centerOfWaveControl};
};


#endif //TREELIGHTS_SINWAVESEQUENCE_H
