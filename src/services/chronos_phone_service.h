#pragma once

#include "iphone_service.h"

class ChronosPhoneService : public IPhoneService
{
public:

    void begin() override;

    void update() override;

    bool connected() override;

    uint8_t phoneBattery() override;

    NavigationData navigation() override;

    CallData call() override;

private:

    uint8_t battery = 100;

    bool isConnected = false;

    NavigationData nav;

    CallData callInfo;

};