#include "home_screen.h"

#include "../display/display.h"
#include "../services/chronos_phone_service.h"

#include <Arduino.h>
#include <cstdio>

extern ChronosPhoneService Phone;

void HomeScreen::begin()
{
}

void HomeScreen::update()
{
}

void HomeScreen::draw()
{
    Display.clear();

    //--------------------------------------------------
    // Status Bar
    //--------------------------------------------------

    Display.drawBluetooth(Phone.connected());

    char battery[8];
    sprintf(
        battery,
        "%d",
        Phone.phoneBattery());

    Display.setFont(Font::Small);

    Display.drawText(
        90,
        8,
        battery);

    Display.drawText(
        112,
        8,
        "100");

    //--------------------------------------------------
    // Time
    //--------------------------------------------------

    Display.drawCentered(
        34,
        Font::Huge,
        Phone.timeString());

    //--------------------------------------------------
    // Day
    //--------------------------------------------------

    Display.drawCentered(
        50,
        Font::Medium,
        Phone.dayString());

    //--------------------------------------------------
    // Status
    //--------------------------------------------------

    if (Phone.connected())
    {
        Display.drawCentered(
            63,
            Font::Small,
            "LaraOS Connected");
    }
    else
    {
        Display.drawCentered(
            63,
            Font::Small,
            "Waiting for Phone...");
    }

    Display.present();
}