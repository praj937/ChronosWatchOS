#include "screen_manager.h"

#include <Arduino.h>

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
    if(state == newState)
        return;

    state = newState;

    switch(state)
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
    }

    current->begin();
}

void ScreenManager::update(bool phoneConnected)
{
    if(state == ScreenState::BOOT)
    {
        if(millis() - bootTime > 1000)
        {
            change(ScreenState::CONNECTING);
        }
    }

    if(state == ScreenState::CONNECTING)
    {
        if(phoneConnected)
        {
            change(ScreenState::HOME);
        }
    }

    current->update();

    current->draw();
}