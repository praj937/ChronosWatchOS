#include "navigation_screen.h"

#include "../display/display.h"
#include "../services/chronos_phone_service.h"

#include <cstring>
#include <cstdio>

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
    // Status Bar
    //--------------------------------------------------

    Display.drawBluetooth(Phone.connected());

    char battery[8];
    sprintf(battery, "%d", Phone.phoneBattery());

    Display.setFont(Font::Small);

    Display.drawText(92, 8, battery);
    Display.drawText(114, 8, "100");

    //--------------------------------------------------
    // Arrow
    //--------------------------------------------------

    if(nav.hasIcon)
    {
        Display.drawBitmap(
            0,
            14,
            48,
            48,
            nav.icon);
    }

    //--------------------------------------------------
    // Parse "2.6 km"
    //--------------------------------------------------

    char number[10] = "";
    char unit[6] = "";

    sscanf(
        nav.distance,
        "%9s %5s",
        number,
        unit);

    //--------------------------------------------------
    // Distance
    //--------------------------------------------------

    Display.setFont(Font::Huge);

    Display.drawText(
        58,
        34,
        number);

    Display.setFont(Font::Medium);

    Display.drawText(
        60,
        48,
        unit);

    //--------------------------------------------------
    // Road Name
    //--------------------------------------------------

    char road[17];

    strncpy(
        road,
        nav.road,
        sizeof(road)-1);

    road[sizeof(road)-1] = '\0';

    Display.drawCentered(
        63,
        Font::Small,
        road);

    Display.present();
}