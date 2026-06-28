#pragma once

#include <stdint.h>

class StatusBar
{
public:

    void draw(
        bool connected,
        uint8_t phoneBattery,
        uint8_t watchBattery);
};

extern StatusBar Status;