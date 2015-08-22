//
// Created by Michael Lewis on 8/18/15.
//

#include "Control.h"
template <typename ValueType>
void ValueControl<ValueType>::tick(const Clock &clock, uint8_t dmxValue) {
    auto newValue = computeNextValue(clock, dmxValue);
    _didChange = _value != newValue;
    if (_didChange) {
        _value = newValue;
    }
}

bool BooleanValueControl::computeNextValue(const Clock &clock, uint8_t dmxValue) {
    return dmxValue > 127;
}

uint8_t IdentityValueControl::computeNextValue(const Clock &clock, uint8_t dmxValue) {
    return dmxValue;
}

template <typename ValueType>
ValueType LinearlyInterpolatedValueControl<ValueType>::computeNextValue(const Clock &clock, uint8_t dmxValue) {
    return dmxValue * (_maxVal - _minVal) / 255  + _minVal;
}

