#include <Arduino.h>
#include "FastLED.h"

#include "config.h"

struct Point {
    Point(int _x, int _y) {
        x = _x;
        y = _y;
    }
    int x;
    int y;
};

Point POINTS[NUM_LEDS] = {
    Point(0, 11),
    Point(0, 10),
    Point(0, 9),
    Point(0, 8),
    Point(0, 7),
    Point(0, 6),
    Point(0, 5),
    Point(0, 4),
    Point(0, 3),
    Point(0, 2),
    Point(0, 1),
    Point(0, 0),
};

class TwoDimensional {
    CRGB* leds;
    int minX, minY, maxX, maxY;

    public:
    TwoDimensional() {
        leds = new CRGB[NUM_LEDS];

        // Initialize min/max x/y
        int mX = POINTS[0].x;
        int mY = POINTS[0].y;
        int MX = POINTS[0].x;
        int MY = POINTS[0].y;
        for (int i = 0; i < NUM_LEDS; i++) {
            Point p = POINTS[i];
            if (p.x < mX) mX = p.x;
            if (p.y < mY) mY = p.y;
            if (p.x > MX) MX = p.x;
            if (p.y > MY) MY = p.y;
        }

        minX = mX;
        minY = mY;
        maxX = MX;
        maxY = MY;
    }

    void setup() {
        FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
        FastLED.setBrightness(BRIGHTNESS);
    }

    void run() {

    }

    private:
    void solidColor() {
        
    }
};