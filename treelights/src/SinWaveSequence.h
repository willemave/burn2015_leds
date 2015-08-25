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

typedef AccumulatorControl<SmoothLinearControl> SmoothAccumulatorControl;

class SinWaveSequence : public SequenceBase<SinWaveSequence> {


public:
    SinWaveSequence(int stripCount, int stripLength, const Clock &clock)
            : SequenceBase(stripCount, stripLength,
                           clock) { }

    virtual void loop(Context *context) {
        
        _hueSliceMin = _hueSlicePhase.value() - _hueSliceSizeControl.value() * .5;
        _hueSliceMax = _hueSlicePhase.value() + _hueSliceSizeControl.value() * .5;
        
        SequenceBase<SinWaveSequence>::loop(context);
        _lightnessPhase.truncate(TWO_PI * _wavelength.value());
        _colorPhase.truncate(TWO_PI);
        _hueSlicePhase.truncate(TWO_PI);
    }
    inline CRGB colorForPixel(int strip, int pixel, const Context &context) {
        float sinOffsetBase = (pixel + _centerOfWaveControl.value()) * TWO_PI / _wavelength.value();

        float sinOffsetV = sinOffsetBase +  _lightnessPhase.value() / _wavelength.value();
        int v = uint8_t((sinf(sinOffsetV) + 1) * 0.5 * 255);

        float sinOffsetH = sinOffsetBase + _colorPhase.value();

        float sinOffsetAdjusted = sinOffsetH / TWO_PI;
        
        // 0 - TWO_PI
        float hueFloat = fmodf(fabsf((roundf(sinOffsetAdjusted) - sinOffsetAdjusted)) *
                                       (_hueSliceMax - _hueSliceMin) + _hueSliceMin + TWO_PI, TWO_PI);
        
        uint8_t h = uint8_t(hueFloat / TWO_PI * 255);
        
        
        return CHSV(h, uint8_t(_saturationControl.value()), v);
    }

    virtual const std::vector<Control *> &controls() {
        return _controls;
    }
private:
    SmoothAccumulatorControl _lightnessPhase = SmoothAccumulatorControl(stripLength() * -6, stripLength() * 6 - 1); // This should probably be an accumulator
    SmoothAccumulatorControl _colorPhase = SmoothAccumulatorControl(-10, 9); // This should probably be an accumulator
    SmoothAccumulatorControl _hueSlicePhase = SmoothAccumulatorControl(0, stripLength() * 0.125); // This should probably be an accumulator
    
    SmoothLinearControl _wavelength = SmoothLinearControl(4, stripLength());
    SmoothLinearControl _centerOfWaveControl = SmoothLinearControl(-stripLength(), 0);
    SmoothLinearControl _hueSliceSizeControl = SmoothLinearControl(0, TWO_PI);
    SmoothLinearControl _saturationControl = SmoothLinearControl(0, 255);
    
    float _hueSliceMin = 0;
    float _hueSliceMax = 0;
    const std::vector<Control *> _controls = {
        &_lightnessPhase,
        &_colorPhase,
        &_hueSlicePhase,
        &_hueSliceSizeControl,
        &_wavelength,
        &_centerOfWaveControl,
        &_saturationControl,
    };
};


#endif //TREELIGHTS_SINWAVESEQUENCE_H
