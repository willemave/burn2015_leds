#include <FastLED.h>
#include <IRremote.h>

# ALL THE DEFINES
#define LED_PIN 6
#define COLOR_ORDER GBR
#define IR_RECV_PIN 22
#define NUM_LEDS 60       // Change to reflect the number of LEDs you have

# VARs
CRGB leds[NUM_LEDS];      //naming our LED array
IRrecv irrecv(IR_RECV_PIN);
decode_results ir_results;

void setup() {
# pin setups!
    pinMode(13, OUTPUT);
    irrecv.enableIRIn(); // Start the receiver

# let's get some debugs
    Serial.begin(9600);

# fast led?
    FastLED.addLeds<WS2812B, LED_PIN>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness( 125 );
}


void loop() {
    heartbeat();
    read_ir();

//  fill_solid(leds, NUM_LEDS, CHSV(2, 55, 55));  
//  FastLED.show();

}

void read_ir() {
    if (irrecv.decode(&ir_results)) {
        dump(&results);
        irrecv.resume(); // Receive the next value
    }
}
void heartbeat() {
    digitalWrite(13, HIGH);
    delay(100); // power-up safety delay
    digitalWrite(13, LOW);
    delay(100);
}

void dump(decode_results *ir_results) {
    int count = results->rawlen;
    if (results->decode_type == UNKNOWN) {
        Serial.print("Unknown encoding: ");
    }
    else if (results->decode_type == NEC) {
        Serial.print("Decoded NEC: ");
    }
    else if (results->decode_type == SONY) {
        Serial.print("Decoded SONY: ");
    }
    else if (results->decode_type == RC5) {
        Serial.print("Decoded RC5: ");
    }
    else if (results->decode_type == RC6) {
        Serial.print("Decoded RC6: ");
    }
    else if (results->decode_type == PANASONIC) {
        Serial.print("Decoded PANASONIC - Address: ");
        Serial.print(results->panasonicAddress, HEX);
        Serial.print(" Value: ");
    }
    else if (results->decode_type == JVC) {
        Serial.print("Decoded JVC: ");
    }
    Serial.print(results->value, HEX);
    Serial.print(" (");
    Serial.print(results->bits, DEC);
    Serial.println(" bits)");
    Serial.print("Raw (");
    Serial.print(count, DEC);
    Serial.print("): ");

    for (int i = 0; i < count; i++) {
        if ((i % 2) == 1) {
            Serial.print(results->rawbuf[i] * USECPERTICK, DEC);
        }
        else {
            Serial.print(-(int) results->rawbuf[i] * USECPERTICK, DEC);
        }
        Serial.print(" ");
    }
    Serial.println("");
}