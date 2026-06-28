#include "home_screen.h"

#include "../display/display.h"

void HomeScreen::begin()
{
}

void HomeScreen::update()
{
}

void HomeScreen::draw()
{
    Display.clear();

    Display.drawBluetooth(true);

    Display.drawCentered(
        30,
        Font::Large,
        "CONNECTED");

    Display.drawCentered(
        50,
        Font::Small,
        "Chronos Ready");

    Display.present();
}