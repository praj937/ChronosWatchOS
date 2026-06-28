#include "screen_manager.h"

ScreenManager Screens;

void ScreenManager::begin()
{

}

void ScreenManager::update()
{

}

void ScreenManager::set(Screen screen)
{
    currentScreen = screen;
}

Screen ScreenManager::current() const
{
    return currentScreen;
}