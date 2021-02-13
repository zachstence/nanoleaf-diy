#include <Arduino.h>
#include "FastLED.h"

#include "OneDimensional.cpp";

auto leds = OneDimensional(12);

void setup() {
    leds.setup();
}

void loop() {
    leds.run();
}
