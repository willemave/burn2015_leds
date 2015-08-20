//
// Created by Michael Lewis on 8/18/15.
//

#ifndef TREELIGHTS_CONTROL_H
#define TREELIGHTS_CONTROL_H


#include <stdint.h>
#include "clock.h"
#include <functional>

/**
 * Controls take a DMX input and a clock and compute a new value. They can store state how they want.
 */
class Control {
public:
    // Called before each frame. A control should calculate its new value based on this
    virtual void tick(const Clock &clock) = 0;
};

// Control that has a value
template<typename ValueType>
class ValueControl : public Control {
public:

    ValueControl(std::function<uint8_t()>  dmxValueProvider) {
        _dmxValueProvider = dmxValueProvider;
    }

    ValueControl() = delete;

    virtual void tick(const Clock &clock);

    inline const ValueType &value() const {
        return _value;
    }
    
    inline uint8_t dmxValue() {
        return _dmxValueProvider();
    }
    
    inline bool didChange() {
        return _didChange;
    }

protected:
    virtual ValueType computeNextValue(const Clock &clock) = 0;

private:
    ValueType _value;
    uint8_t *_valueSource;
    bool _didChange = false;
    std::function<uint8_t()> _dmxValueProvider;
};


/**
 * Takes <127 = 0,
 */
class BooleanValueControl : public ValueControl<bool> {
protected:
    virtual bool computeNextValue(const Clock &clock);
};


// Just a passthrough
class IdentityValueControl : public ValueControl<uint8_t> {
public:
    IdentityValueControl(std::function<uint8_t()>  dmxValueProvider) : ValueControl<uint8_t>::ValueControl(dmxValueProvider) {
    }

protected:
    
    virtual uint8_t computeNextValue(const Clock &clock);
};


// Just a passthrough
template<typename ValueType>
class LinearlyInterpolatedValueControl : public ValueControl<ValueType> {
protected:
    virtual ValueType computeNextValue(const Clock &clock);

public:
    LinearlyInterpolatedValueControl() = delete;
    LinearlyInterpolatedValueControl(std::function<uint8_t()>  dmxValueProvider, ValueType min, ValueType max) : ValueControl<ValueType>::ValueControl(dmxValueProvider), _min(min), _max(max) { }

private:
    ValueType _min;
    ValueType _max;
};

template class LinearlyInterpolatedValueControl<int>;
template class LinearlyInterpolatedValueControl<float>;

#endif //TREELIGHTS_CONTROL_H
