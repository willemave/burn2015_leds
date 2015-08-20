//
// Created by Michael Lewis on 8/17/15.
//

#ifndef TREELIGHTS_EXAMPLESEQUENCE_H
#define TREELIGHTS_EXAMPLESEQUENCE_H


#include "SequenceBase.h"
#include "Control.h"

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

class HSVSequence : public SequenceBase<HSVSequence> {
public:
    HSVSequence(int stripCount,
                int stripLength,
                const Clock &clock,
                IdentityValueControl *hControl,
                IdentityValueControl *sControl,
                IdentityValueControl *vControl)
    : SequenceBase<HSVSequence>::SequenceBase(stripCount, stripLength, clock),
    _hControl(hControl), _sControl(sControl), _vControl(vControl) {
    }
    
    inline CRGB colorForPixel(int strip, int pixel, const Context &context) {
        return CHSV(_hControl->value(), _sControl->value(), _vControl->value());
    }
    
private:
    IdentityValueControl *_hControl;
    IdentityValueControl *_sControl;
    IdentityValueControl *_vControl;
};

class RGBSequence : public SequenceBase<RGBSequence> {
public:
    RGBSequence(int stripCount,
                int stripLength,
                const Clock &clock,
                const IdentityValueControl &rControl,
                const IdentityValueControl &gControl,
                const IdentityValueControl &bControl)
    : SequenceBase<RGBSequence>::SequenceBase(stripCount, stripLength, clock),
    _rControl(rControl), _gControl(gControl), _bControl(bControl) {
    }
    
    inline CRGB colorForPixel(int strip, int pixel, const Context &context) {
        return CRGB(_rControl.value(), _gControl.value(), _bControl.value());
    }
    
private:
    const IdentityValueControl &_rControl;
    const IdentityValueControl &_gControl;
    const IdentityValueControl &_bControl;
};


#endif //TREELIGHTS_EXAMPLESEQUENCE_H
