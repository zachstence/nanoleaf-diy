#include <Arduino.h>
#include "FastLED.h"

#include "config.h"

struct Point {
    int x;
    int y;

    float getAngle(Point origin) {
        Point vector = {this->x - origin.x, this->y - origin.y};
        return atan2(vector.x, vector.y);
    }
};

class TwoDimensional {
    CRGB* leds;
    int minX, minY, maxX, maxY;

    Point center = Point{100, 100};
    Point points[NUM_LEDS] = {
        Point{100, 18},
        Point{85, 48},
        Point{71, 78},
        Point{56, 108},
        Point{29, 141},
        Point{63, 138},
        Point{96, 136},
        Point{129, 134},
        Point{171, 141},
        Point{152, 113},
        Point{133, 86},
        Point{115, 58},
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
                CHSV color = solidRed(points[i]);
                leds[i].setHSV(color.h, color.s, color.v);
            }
            FastLED.show();
        }
    }

    void redVerticalFade() {
        while (true) {
            for (int i = 0; i < NUM_LEDS; i++) {
                CHSV color = redVerticalFade(points[i]);
                leds[i].setHSV(color.h, color.s, color.v);
            }
            FastLED.show();
        }
    }

    void verticalRainbow(int periodSec) {
        for (uint8_t t = 0; true; t++) {
            for (int i = 0; i < NUM_LEDS; i++) {
                CHSV color = verticalRainbow(points[i], 50, t);
                leds[i].setHSV(color.h, color.s, color.v);
            }
            FastLED.show();
            delay(1000 * ((float)periodSec / 255));
        }
    }
    
    void horizontalRainbow(int periodSec) {
        for (uint8_t t = 0; true; t++) {
            for (int i = 0; i < NUM_LEDS; i++) {
                CHSV color = horizontalRainbow(points[i], 225, t);
                leds[i].setHSV(color.h, color.s, color.v);
            }
            FastLED.show();
            delay(1000 * ((float)periodSec / 255));
        }
    }
    
    void rainbowWheel(int periodSec) {
        for (uint8_t t = 0; true; t++) {
            for (int i = 0; i < NUM_LEDS; i++) {
                CHSV color = rainbowWheel(points[i], center, t);
                leds[i].setHSV(color.h, color.s, color.v);
            }
            FastLED.show();
            delay(1000 * ((float)periodSec / 255));
        }
    }

    private:
    CHSV solidRed(Point p) {
        return CHSV(0, 255, 255);
    }

    CHSV redVerticalFade(Point p) {
        uint8_t brightness = map(p.y, minY, maxY, 0, 255);
        return CHSV(0, 255, brightness);
    }

    CHSV verticalRainbow(Point p, uint8_t hueAngle, uint8_t hueOffset) {
        uint8_t hue = map(p.y, minY, maxY, hueOffset, hueOffset + hueAngle);
        return CHSV(hue, 255, 255);
    }

    CHSV horizontalRainbow(Point p, uint8_t hueAngle, uint8_t hueOffset) {
        uint8_t hue = map(p.x, minX, maxX, hueOffset, hueOffset + hueAngle);
        return CHSV(hue, 255, 255);
    }

    CHSV rainbowWheel(Point p, Point c, uint8_t hueOffset) {
        float angle = c.getAngle(p);
        uint8_t hue = map(angle, -PI, PI, hueOffset, 255+hueOffset);

        return CHSV(hue, 255, 255);
    }
};