#pragma once

#include "types.h"

class ScreenManager
{
public:

    void begin();

    void update();

    void set(Screen screen);

    Screen current() const;

private:

    Screen currentScreen = Screen::Boot;

};

extern ScreenManager Screens;