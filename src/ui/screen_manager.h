#pragma once

#include <Arduino.h>
#include "navigation_screen.h"
#include "boot_screen.h"
#include "connecting_screen.h"
#include "home_screen.h"

enum class ScreenState
{
    BOOT,
    CONNECTING,
    HOME,
    NAVIGATION
};

class ScreenManager
{
public:

    void begin();

    void update(bool phoneConnected);

private:

    void change(ScreenState state);

    ScreenState state = ScreenState::BOOT;

    uint32_t bootTime = 0;

    BootScreen boot;
    ConnectingScreen connecting;
    HomeScreen home;
    NavigationScreen navigation;

    IScreen* current = nullptr;
};

extern ScreenManager Screens;