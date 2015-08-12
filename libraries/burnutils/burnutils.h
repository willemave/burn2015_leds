//
// Created by Willem Ave on 8/11/15.
//
#include <IRremote.h>
#include <FastLED.h>


class BurnUtils {
    usb_serial_class s;
public:

    BurnUtils (usb_serial_class& s);
    void heartbeat();

    void ir_dump(decode_results *results);
};
