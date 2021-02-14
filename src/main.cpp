#include <Arduino.h>
#include "FastLED.h"
#include "OneDimensional.cpp"
#include "TwoDimensional.cpp"

auto leds = TwoDimensional();
// auto leds = OneDimensional();

void setup() {
    leds.setup();
}

void loop() {
    leds.run();
}
