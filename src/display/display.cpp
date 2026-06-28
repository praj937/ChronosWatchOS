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
void DisplayManager::drawBitmap(
    int x,
    int y,
    int width,
    int height,
    const uint8_t* bitmap)
{
    oled.drawXBM(
        x,
        y,
        width,
        height,
        bitmap);
}

void DisplayManager::drawNavigationBitmap(
    int x,
    int y,
    const uint8_t* bitmap)
{
    // Find bounding box of non-empty pixels

    int minX = 48;
    int minY = 48;
    int maxX = 0;
    int maxY = 0;

    for(int yy = 0; yy < 48; yy++)
    {
        for(int xx = 0; xx < 48; xx++)
        {
            int byteIndex = xx + (yy / 8) * 48;

            bool pixel =
                bitmap[byteIndex] &
                (1 << (yy & 7));

            if(pixel)
            {
                if(xx < minX) minX = xx;
                if(xx > maxX) maxX = xx;

                if(yy < minY) minY = yy;
                if(yy > maxY) maxY = yy;
            }
        }
    }

    int cropWidth  = maxX - minX + 1;
    int cropHeight = maxY - minY + 1;

    int offsetX = (48 - cropWidth) / 2;
    int offsetY = (48 - cropHeight) / 2;

    for(int yy = minY; yy <= maxY; yy++)
    {
        for(int xx = minX; xx <= maxX; xx++)
        {
            int byteIndex = xx + (yy / 8) * 48;

            bool pixel =
                bitmap[byteIndex] &
                (1 << (yy & 7));

            if(pixel)
            {
                oled.drawPixel(
                    x + offsetX + xx - minX,
                    y + offsetY + yy - minY);
            }
        }
    }
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