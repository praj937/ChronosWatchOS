#include "screen_manager.h"

#include <Arduino.h>

#include "../services/chronos_phone_service.h"

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

        default:
            current = &home;
            break;
    }

    current->begin();
}

void ScreenManager::update(bool phoneConnected)
{
    NavigationData nav = Phone.navigation();

    //--------------------------------------------------
    // Boot
    //--------------------------------------------------

    if (state == ScreenState::BOOT)
    {
        if (millis() - bootTime >= 1000)
        {
            change(ScreenState::CONNECTING);
        }
    }

    //--------------------------------------------------
    // Connecting
    //--------------------------------------------------

    else if (state == ScreenState::CONNECTING)
    {
        if (phoneConnected)
        {
            if (nav.active)
                change(ScreenState::NAVIGATION);
            else
                change(ScreenState::HOME);
        }
    }

    //--------------------------------------------------
    // Runtime
    //--------------------------------------------------

    else
    {
        if (!phoneConnected)
        {
            change(ScreenState::CONNECTING);
        }
        else
        {
            if (nav.active)
            {
                if (state != ScreenState::NAVIGATION)
                {
                    change(ScreenState::NAVIGATION);
                }
            }
            else
            {
                if (state != ScreenState::HOME)
                {
                    change(ScreenState::HOME);
                }
            }
        }
    }

    //--------------------------------------------------
    // Draw Current Screen
    //--------------------------------------------------

    if (current != nullptr)
    {
        current->update();
        current->draw();
    }
}