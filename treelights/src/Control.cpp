//
// Created by Michael Lewis on 8/18/15.
//

#include "Control.h"


template <typename ValueType>
void ValueControl<ValueType>::tick(const Clock &clock) {
    _value = computeNextValue(clock);
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

