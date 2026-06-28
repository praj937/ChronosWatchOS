#pragma once

#include <Arduino.h>
#include <U8g2lib.h>
#include "fonts.h"

class DisplayManager
{
public:

    void begin();

    void clear();

    void present();

    //-------------------------
    // Font
    //-------------------------

    void setFont(Font font);

    //-------------------------
    // Text
    //-------------------------

    void drawText(
        int x,
        int y,
        const char* text);
    void drawBitmap(
    int x,
    int y,
    int width,
    int height,
    const uint8_t* bitmap);

    void drawCentered(
        int y,
        Font font,
        const char* text);

    //-------------------------
    // Widgets
    //-------------------------

    void drawBluetooth(bool connected);

    void drawBattery(
        int x,
        int y,
        uint8_t percent);

    //-------------------------
    // Screens
    //-------------------------

    void drawBootScreen();

private:

    U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled =
        U8G2_SSD1306_128X64_NONAME_F_HW_I2C(
            U8G2_R0,
            U8X8_PIN_NONE);
};

extern DisplayManager Display;