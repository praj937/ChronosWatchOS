#pragma once

#include <Arduino.h>

#include "iscreen.h"

#include "boot_screen.h"
#include "connecting_screen.h"
#include "home_screen.h"
#include "navigation_screen.h"
#include "call_screen.h"

enum class ScreenState
{
    BOOT,
    CONNECTING,
    HOME,
    NAVIGATION,
    CALL
};

class ScreenManager
{
public:

    void begin();

    void update(bool phoneConnected);

    void showCall();

    void hideCall();

private:

    void change(ScreenState state);

    ScreenState state = ScreenState::BOOT;

    uint32_t bootTime = 0;

    bool callShowing = false;

    BootScreen boot;
    ConnectingScreen connecting;
    HomeScreen home;
    NavigationScreen navigation;

    IScreen* current = nullptr;
};

extern ScreenManager Screens;