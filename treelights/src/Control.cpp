//
// Created by Michael Lewis on 8/18/15.
//

#include "Control.h"
template <typename ValueType>
void ValueControl<ValueType>::tick(const Clock &clock) {
    auto newValue = computeNextValue(clock);
    _didChange = _value != newValue;
    if (_didChange) {
        _value = newValue;
    }
}

bool BooleanValueControl::computeNextValue(const Clock &clock) {
    return dmxValue() > 127;
}

uint8_t IdentityValueControl::computeNextValue(const Clock &clock) {
    return dmxValue();
}

template <typename ValueType>
ValueType LinearlyInterpolatedValueControl<ValueType>::computeNextValue(const Clock &clock) {
    return this->dmxValue() * (_max - _min) / 255  + _min;
}

