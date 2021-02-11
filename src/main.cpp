#include <Arduino.h>
#include "FastLED.h"

#define NUM_LEDS 12
#define DATA_PIN 6
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

#define BRIGHTNESS 100

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}

void setColor(uint8_t r, uint8_t g, uint8_t b) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].setRGB(r, g, b);
  }
  FastLED.show();
}

void chase(int r, int g, int b) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].setRGB(r, g, b);
    FastLED.show();
    delay(50);
    leds[i].setRGB(0, 0, 0);
  }
}

void rainbowCycle() {
  for (int j = 0; j < 255; j++) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i].setHue(j);
    }
    FastLED.show();
    delay(50);
  }
}

void rainbowTheater(int dH, int dT) {
  int hue = 0;
  int i = 0;
  while (true) {
    leds[i].setHue(hue);
    hue -= dH;
    FastLED.show();
    delay(dT);

    i = (i + 1) % NUM_LEDS;
  }
}

void rainbowSpin(int dH) {
  // init hue array
  int hues[NUM_LEDS];
  int hue = 0;
  for (int i = 0; i < NUM_LEDS; i++) {
    hues[i] = hue;
    hue -= dH;
  }

  // rainbow spin
  while (true) {
    // update hues
    for (int i = 0; i < NUM_LEDS; i++) {
      hues[i] -= dH;
    }

    // set leds
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i].setHue(hues[i]);
    }
    FastLED.show();

    delay(50);
  }
}

void rainbowSpin2(int dH, int dT) {
  
  for (int hue = 0; true; hue += dH) {
    fill_rainbow(leds, NUM_LEDS, hue, 255 / NUM_LEDS);
    FastLED.show();
    delay(dT);
  }

  //  fill_rainbow(leds, NUM_LEDS, x, 255 / NUM_LEDS);
  //  FastLED.show();
  //
  //  EVERY_N_MILLISECONDS(50) {
  //    x++;
  //  }
}


void breathe(uint8_t r, uint8_t g, uint8_t b, int cycleTime) {
  CHSV hsv = rgb2hsv_approximate(CRGB(r, g, b));
  uint8_t maxBrightness = hsv.value;

  while (true) {
    // Dim all LEDs
    for (uint8_t brightness = maxBrightness; brightness > 0; brightness--) {
      fill_solid(leds, NUM_LEDS, CHSV(hsv.h, hsv.s, brightness));
      FastLED.show();
      delay((cycleTime * 1000)/255);
    }

    // Brighten LEDs back to maxBrightness
    for (uint8_t brightness = 0; brightness < maxBrightness; brightness++) {
      fill_solid(leds, NUM_LEDS, CHSV(hsv.h, hsv.s, brightness));
      FastLED.show();
      delay((cycleTime * 1000)/255);
    }
  }
}


/////////////////////////////////////////////////




/////////////////////////////////////////////////

void loop() {
//  rainbowSpin(28.333);
  // rainbowSpin2(5, 50);
//  rainbowTheater(5, 50);
//  setColor(255, 0, 0);
  breathe(255, 0, 0, 2);
  // chase(0, 255, 229);
}
