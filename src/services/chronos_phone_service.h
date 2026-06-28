#pragma once

#include <ChronosESP32.h>

#include "iphone_service.h"

class ChronosPhoneService : public IPhoneService
{
public:

    ChronosPhoneService();

    void begin() override;

    void update() override;

    bool connected() override;

    uint8_t phoneBattery() override;

    const char* timeString() override;

    const char* dayString() override;

    NavigationData navigation() override;

    CallData call() override;

private:

    ChronosESP32 watch;

    NavigationData navData;

    CallData callData;

    char timeBuffer[6];

    char dayBuffer[12];
};