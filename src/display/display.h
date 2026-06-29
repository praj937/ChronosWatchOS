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
    void setFont(Font font);
    void text(int16_t x, int16_t baseline, const char* value);
    void centered(int16_t baseline, Font font, const char* value);
    void bitmap(int16_t x, int16_t y, uint8_t width, uint8_t height, const uint8_t* data);
    void line(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
    void frame(int16_t x, int16_t y, int16_t width, int16_t height);
    void box(int16_t x, int16_t y, int16_t width, int16_t height);
    void disc(int16_t x, int16_t y, int16_t radius);
    uint16_t textWidth(const char* value);

private:
    U8G2_SSD1306_128X64_NONAME_F_HW_I2C oled{U8G2_R0, U8X8_PIN_NONE};
};

extern DisplayManager Display;
