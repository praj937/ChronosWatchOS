#pragma once

#include <stdint.h>

struct NavigationData
{
    bool active = false;

    char distance[16] = "";

    char remaining[16] = "";

    char road[64] = "";
};

struct CallData
{
    bool active = false;

    char caller[64] = "";
};

class IPhoneService
{
public:

    virtual ~IPhoneService() = default;

    virtual void begin() = 0;

    virtual void update() = 0;

    virtual bool connected() = 0;

    virtual uint8_t phoneBattery() = 0;

    virtual const char* timeString() = 0;

    virtual const char* dayString() = 0;

    virtual NavigationData navigation() = 0;

    virtual CallData call() = 0;

};