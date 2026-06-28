#include "screen_manager.h"

ScreenManager Screens;

void ScreenManager::begin()
{
    current = &boot;

    current->begin();
}

void ScreenManager::update()
{
    if(current == nullptr)
        return;

    current->update();

    current->draw();
}