#pragma once

#include "boot_screen.h"

class ScreenManager
{
public:

    void begin();

    void update();

private:

    BootScreen boot;

    IScreen* current = nullptr;
};

extern ScreenManager Screens;