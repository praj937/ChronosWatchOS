#pragma once

#include <Arduino.h>
#include <U8g2lib.h>

#include "fonts.h"

class DisplayManager
{
public:

    //------------------------------------------------
    // Display
    //------------------------------------------------

    void begin();

    void clear();

    void present();

    //------------------------------------------------
    // Fonts
    //------------------------------------------------

    void setFont(Font font);

    //------------------------------------------------
    // Text
    //------------------------------------------------

    void drawText(
        int x,
        int y,
        const char* text);

    void drawCentered(
        int y,
        Font font,
        const char* text);

    //------------------------------------------------
    // Bitmap
    //------------------------------------------------

    void drawBitmap(
        int x,
        int y,
        int width,
        int height,
        const uint8_t* bitmap);

    //------------------------------------------------
    // Primitive Drawing
    //------------------------------------------------

    void drawLine(
        int x1,
        int y1,
        int x2,
        int y2);

    void drawBox(
        int x,
        int y,
        int w,
        int h);

    void drawDisc(
        int x,
        int y,
        int r);

    //------------------------------------------------
    // Navigation Arrows
    //------------------------------------------------

    void drawStraightArrow(
        int x,
        int y);

    void drawLeftArrow(
        int x,
        int y);

    void drawRightArrow(
        int x,
        int y);

    void drawSlightLeftArrow(
        int x,
        int y);

    void drawSlightRightArrow(
        int x,
        int y);

    void drawUTurnArrow(
        int x,
        int y);

    //------------------------------------------------
    // Widgets
    //------------------------------------------------

    void drawBluetooth(bool connected);

    void drawBattery(
        int x,
        int y,
        uint8_t percent);

    //------------------------------------------------
    // Boot Screen
    //------------------------------------------------

    void drawBootScreen();

private:

    U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled =
        U8G2_SSD1306_128X64_NONAME_F_HW_I2C(
            U8G2_R0,
            U8X8_PIN_NONE);
};

extern DisplayManager Display;