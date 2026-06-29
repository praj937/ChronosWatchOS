#include "display.h"
#include <Wire.h>
#include "config.h"

DisplayManager Display;

void DisplayManager::begin()
{
    Wire.begin(WatchConfig::OLED_SDA, WatchConfig::OLED_SCL);
    Wire.setClock(WatchConfig::I2C_SPEED);
    oled.begin();
    oled.setContrast(255);
    clear();
    present();
}

void DisplayManager::clear() { oled.clearBuffer(); }
void DisplayManager::present() { oled.sendBuffer(); }

void DisplayManager::setFont(Font font)
{
    switch (font)
    {
        case Font::Tiny: oled.setFont(u8g2_font_4x6_tf); break;
        case Font::Small: oled.setFont(u8g2_font_5x8_tf); break;
        case Font::Medium: oled.setFont(u8g2_font_6x12_tf); break;
        case Font::Large: oled.setFont(u8g2_font_logisoso16_tf); break;
    case Font::Huge:
    oled.setFont(u8g2_font_logisoso20_tf);
    break;
    }
}

void DisplayManager::text(int16_t x, int16_t baseline, const char* value) { oled.drawUTF8(x, baseline, value); }
void DisplayManager::centered(int16_t baseline, Font font, const char* value)
{
    setFont(font);
    text((WatchConfig::DISPLAY_WIDTH - oled.getUTF8Width(value)) / 2, baseline, value);
}
void DisplayManager::bitmap(int16_t x, int16_t y, uint8_t w, uint8_t h, const uint8_t* data) { oled.drawXBMP(x, y, w, h, data); }
void DisplayManager::line(int16_t x0, int16_t y0, int16_t x1, int16_t y1) { oled.drawLine(x0, y0, x1, y1); }
void DisplayManager::frame(int16_t x, int16_t y, int16_t w, int16_t h) { oled.drawFrame(x, y, w, h); }
void DisplayManager::box(int16_t x, int16_t y, int16_t w, int16_t h) { oled.drawBox(x, y, w, h); }
void DisplayManager::disc(int16_t x, int16_t y, int16_t r) { oled.drawDisc(x, y, r); }
uint16_t DisplayManager::textWidth(const char* value)
{
    return oled.getUTF8Width(value);
}