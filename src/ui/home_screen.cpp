#include "home_screen.h"

#include "../display/display.h"
#include "../services/chronos_phone_service.h"

// Global phone service from app.cpp
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

    // Bluetooth
    Display.drawBluetooth(Phone.connected());

    // Phone battery
    char text[8];
    sprintf(text, "%d", Phone.phoneBattery());
    Display.drawText(88, 8, text);

    // Watch battery (placeholder)
    Display.drawText(112, 8, "100");

    // Time
    Display.drawCentered(
        38,
        Font::Huge,
        Phone.timeString());

    // Day
    Display.drawCentered(
        60,
        Font::Medium,
        Phone.dayString());

    Display.present();
}