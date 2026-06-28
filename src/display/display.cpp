#include "display.h"

#include <Wire.h>

#include "config.h"
#include "version.h"

DisplayManager Display;

void DisplayManager::begin()
{
    Wire.begin(WatchConfig::OLED_SDA, WatchConfig::OLED_SCL);
    Wire.setClock(WatchConfig::I2C_SPEED);

    oled.begin();

    clear();
    present();
}

void DisplayManager::clear()
{
    oled.clearBuffer();
}

void DisplayManager::present()
{
    oled.sendBuffer();
}

void DisplayManager::setFont(Font font)
{
    switch(font)
    {
        case Font::Tiny:
            oled.setFont(u8g2_font_4x6_tf);
            break;

        case Font::Small:
            oled.setFont(u8g2_font_5x8_tf);
            break;

        case Font::Medium:
            oled.setFont(u8g2_font_6x12_tf);
            break;

        case Font::Large:
            oled.setFont(u8g2_font_logisoso16_tf);
            break;

        case Font::Huge:
            oled.setFont(u8g2_font_logisoso24_tf);
            break;
    }
}

void DisplayManager::drawText(
    int x,
    int y,
    const char* text)
{
    oled.drawStr(x,y,text);
}

void DisplayManager::drawCentered(
    int y,
    Font font,
    const char* text)
{
    setFont(font);

    int width = oled.getStrWidth(text);
    

    int x = (WatchConfig::DISPLAY_WIDTH - width) / 2;

    oled.drawStr(x,y,text);
}

void DisplayManager::drawBluetooth(bool connected)
{
    if(connected)
        oled.drawDisc(3,4,2);
}

void DisplayManager::drawBattery(
    int x,
    int y,
    uint8_t percent)
{
    oled.drawFrame(x,y,14,7);

    oled.drawBox(x+14,y+2,2,3);

    int fill = map(percent,0,100,0,12);

    if(fill>0)
        oled.drawBox(x+1,y+1,fill,5);
}

void DisplayManager::drawBootScreen()
{
    clear();

    drawCentered(
        36,
        Font::Huge,
        "BOOT");

    drawCentered(
        56,
        Font::Medium,
        Version::NUMBER);

    present();
}