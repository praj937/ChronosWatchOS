#include "status_bar.h"

#include "../display/display.h"

StatusBar Status;

void StatusBar::draw(
    bool connected,
    uint8_t phoneBattery,
    uint8_t watchBattery)
{
    Display.drawBluetooth(connected);

    char text[6];

    sprintf(text,"%d",phoneBattery);
    Display.drawText(88,8,text);

    sprintf(text,"%d",watchBattery);
    Display.drawText(112,8,text);
}