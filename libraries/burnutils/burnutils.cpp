//
// Created by Willem Ave on 8/11/15.
//

#include <burnutils.h>

BurnUtils::BurnUtils(usb_serial_class& serial) {
    s = serial;
}

void BurnUtils::heartbeat() {
    digitalWrite(13, HIGH);
    delay(500); // power-up safety delay
    digitalWrite(13, LOW);
    delay(500);
}

void BurnUtils::ir_dump(decode_results *results) {
    int count = results->rawlen;
    if (results->decode_type == UNKNOWN) {
        s.print("Unknown encoding: ");
    }
    else if (results->decode_type == NEC) {
        s.print("Decoded NEC: ");
    }
    else if (results->decode_type == SONY) {
        s.print("Decoded SONY: ");
    }
    else if (results->decode_type == RC5) {
        s.print("Decoded RC5: ");
    }
    else if (results->decode_type == RC6) {
        s.print("Decoded RC6: ");
    }
    else if (results->decode_type == PANASONIC) {
        s.print("Decoded PANASONIC - Address: ");
        s.print(results->panasonicAddress, HEX);
        s.print(" Value: ");
    }
    else if (results->decode_type == JVC) {
        s.print("Decoded JVC: ");
    }
    s.print(results->value, HEX);
    s.print(" (");
    s.print(results->bits, DEC);
    s.println(" bits)");
    s.print("Raw (");
    s.print(count, DEC);
    s.print("): ");

    for (int i = 0; i < count; i++) {
        if ((i % 2) == 1) {
            s.print(results->rawbuf[i] * USECPERTICK, DEC);
        }
        else {
            s.print(-(int) results->rawbuf[i] * USECPERTICK, DEC);
        }
        s.print(" ");
    }
    s.println("");
}
