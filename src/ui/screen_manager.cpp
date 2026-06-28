#include "screen_manager.h"

#include <Arduino.h>

#include "../services/chronos_phone_service.h"

// Global phone service
extern ChronosPhoneService Phone;

ScreenManager Screens;

void ScreenManager::begin()
{
    bootTime = millis();

    state = ScreenState::BOOT;

    current = &boot;

    current->begin();
}

void ScreenManager::change(ScreenState newState)
{
    if (state == newState)
        return;

    state = newState;

    switch (state)
    {
    case ScreenState::BOOT:
        current = &boot;
        break;

    case ScreenState::CONNECTING:
        current = &connecting;
        break;

    case ScreenState::HOME:
        current = &home;
        break;

    case ScreenState::NAVIGATION:
        current = &navigation;
        break;
    }

    current->begin();
}

void ScreenManager::update(bool phoneConnected)
{
    if (state == ScreenState::BOOT)
    {
        if (millis() - bootTime > 1000)
        {
            change(ScreenState::CONNECTING);
        }
    }

    else if (state == ScreenState::CONNECTING)
    {
        if (phoneConnected)
        {
            change(ScreenState::HOME);
        }
    }

    else
    {
        NavigationData nav = Phone.navigation();

        if (nav.active)
        {
            change(ScreenState::NAVIGATION);
        }
        else
        {
            change(ScreenState::HOME);
        }
    }

    current->update();
    current->draw();
}