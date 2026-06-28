#include "connecting_screen.h"

#include "../display/display.h"

void ConnectingScreen::begin()
{
}

void ConnectingScreen::update()
{
}

void ConnectingScreen::draw()
{
    Display.clear();

    Display.drawCentered(
        28,
        Font::Large,
        "WAIT");

    Display.drawCentered(
        50,
        Font::Small,
        "Open Chronos");

    Display.present();
}