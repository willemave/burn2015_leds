//
// Created by Willem Ave on 8/11/15.
//
#include <FastLED.h>

class BurnUtils {
    usb_serial_class s;
public:

    BurnUtils (usb_serial_class& s);
    void heartbeat();
};
