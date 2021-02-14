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


class TwoDimensional {
    CRGB* leds;
    int minX, minY, maxX, maxY;
    int res = 100;

    Point points[NUM_LEDS] = {
        Point(100, 18),
        Point(85, 48),
        Point(71, 78),
        Point(56, 108),
        Point(29, 141),
        Point(63, 138),
        Point(96, 136),
        Point(129, 134),
        Point(171, 141),
        Point(152, 113),
        Point(133, 86),
        Point(115, 58),
    };


    public:
    TwoDimensional() {
        leds = new CRGB[NUM_LEDS];

        // Initialize min/max x/y
        int mX = points[0].x;
        int mY = points[0].y;
        int MX = points[0].x;
        int MY = points[0].y;
        for (int i = 0; i < NUM_LEDS; i++) {
            Point p = points[i];
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

    void solidRed() {
        while (true) {
            for (int i = 0; i < NUM_LEDS; i++) {
                CHSV color = solidRed(points[i].x, points[i].y);
                leds[i].setHSV(color.h, color.s, color.v);
            }
            FastLED.show();
        }
    }

    void redVerticalFade() {
        while (true) {
            for (int i = 0; i < NUM_LEDS; i++) {
                CHSV color = redVerticalFade(points[i].x, points[i].y);
                leds[i].setHSV(color.h, color.s, color.v);
            }
            FastLED.show();
        }
    }

    private:
    CHSV solidRed(int x, int y) {
        return CHSV(0, 255, 255);
    }

    CHSV redVerticalFade(int x, int y) {
        uint8_t brightness = map(y, minY-10, maxY+10, 0, 255);
        return CHSV(0, 255, brightness);
    }
};