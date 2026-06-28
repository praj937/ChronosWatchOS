#include "display.h"

#include <Wire.h>

#include "config.h"
#include "layout.h"
#include "version.h"

DisplayManager Display;

void DisplayManager::begin()
{
    Wire.begin(OLED_SDA, OLED_SCL);
    Wire.setClock(OLED_I2C_SPEED);

    oled.begin();

    oled.clearBuffer();
    oled.sendBuffer();
}

void DisplayManager::clear()
{
    oled.clearBuffer();
}

void DisplayManager::present()
{
    oled.sendBuffer();
}

void DisplayManager::drawBluetooth(bool connected)
{
    if (connected)
    {
        oled.drawDisc(Layout::BT_X,
                      Layout::BT_Y,
                      2);
    }
}

void DisplayManager::drawBattery(
    int x,
    int y,
    uint8_t percent)
{
    oled.drawFrame(x,y,14,7);

    oled.drawBox(x+14,y+2,2,3);

    int fill =
        map(percent,0,100,0,12);

    if(fill>0)
        oled.drawBox(x+1,y+1,fill,5);
}

void DisplayManager::drawBootScreen()
{
    clear();

    drawCentered(
        38,
        Font::Huge,
        "BOOT");

    drawCentered(
        58,
        Font::Medium,
        FW_VERSION);

    present();
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

    int w = oled.getStrWidth(text);

    int x = (128 - w)/2;

    oled.drawStr(x,y,text);
}