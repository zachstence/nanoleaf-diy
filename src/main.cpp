#include <Arduino.h>
#include "FastLED.h"
#include "OneDimensional.cpp"
#include "TwoDimensional.cpp"

// auto leds = OneDimensional();
auto leds = TwoDimensional();

void setup() {
    leds.setup();
}

void loop() {
    //  rainbowSpin(28.333);
    // rainbowSpin2(5, 50);
    // leds.rainbowTheater(5, 50);
    //  setColor(255, 0, 0);
    // breathe(255, 0, 0, 2);
    // chase(0, 255, 229);

    // leds.solidRed();
    leds.redVerticalFade();
}
