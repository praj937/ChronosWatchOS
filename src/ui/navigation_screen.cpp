#include "navigation_screen.h"
#include "navigation_icons.h"

#include "../display/display.h"
#include "../services/chronos_phone_service.h"

#include <Arduino.h>
#include <cstdio>
#include <cstring>

extern ChronosPhoneService Phone;

void NavigationScreen::begin()
{
}

void NavigationScreen::update()
{
}

void NavigationScreen::draw()
{
    NavigationData nav = Phone.navigation();

    Display.clear();

    //--------------------------------------------------
    // Top Status Bar
    //--------------------------------------------------

    Display.drawBluetooth(Phone.connected());

    char battery[8];
    sprintf(battery, "%d", Phone.phoneBattery());

    Display.setFont(Font::Small);
    Display.drawText(90, 8, battery);
    Display.drawText(112, 8, "100");

    //--------------------------------------------------
// LEFT : LaraOS Arrow
//--------------------------------------------------

#include "navigation_icons.h"

String road = String(nav.road);
road.toLowerCase();

const uint8_t* icon = ICON_STRAIGHT;

if (road.indexOf("slight left") >= 0)
{
    icon = ICON_SLIGHT_LEFT;
}
else if (road.indexOf("slight right") >= 0)
{
    icon = ICON_SLIGHT_RIGHT;
}
else if (road.indexOf("sharp left") >= 0)
{
    icon = ICON_SHARP_LEFT;
}
else if (road.indexOf("sharp right") >= 0)
{
    icon = ICON_SHARP_RIGHT;
}
else if (road.indexOf("u-turn") >= 0)
{
    icon = ICON_UTURN;
}
else if (road.indexOf("roundabout") >= 0)
{
    icon = ICON_ROUNDABOUT;
}
else if (road.indexOf("left") >= 0)
{
    icon = ICON_LEFT;
}
else if (road.indexOf("right") >= 0)
{
    icon = ICON_RIGHT;
}

Display.drawBitmap(
    0,
    8,
    48,
    48,
    icon);

    //--------------------------------------------------
    // RIGHT : Distance
    //--------------------------------------------------

    char value[10] = "";
    char unit[6] = "";

    sscanf(
        nav.distance,
        "%9s %5s",
        value,
        unit);

    Display.setFont(Font::Huge);

    // Big turn distance
    Display.drawText(
        60,
        34,
        value);

    Display.setFont(Font::Medium);

    Display.drawText(
        64,
        51,
        unit);

    //--------------------------------------------------
    // Bottom : Road Name
    //--------------------------------------------------

    char road[22];

    strncpy(
        road,
        nav.road,
        sizeof(road) - 1);

    road[sizeof(road) - 1] = '\0';

    // Remove leading spaces
    while (road[0] == ' ')
    {
        memmove(
            road,
            road + 1,
            strlen(road));
    }

    // Shorten long names
    if (strlen(road) > 20)
    {
        road[20] = '\0';
    }

    Display.drawCentered(
        63,
        Font::Small,
        road);

    Display.present();
}