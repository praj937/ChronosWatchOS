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

    //------------------------------------------------
    // Chronos
    //------------------------------------------------

    ChronosESP32 watch;

    //------------------------------------------------
    // Cached Data
    //------------------------------------------------

    NavigationData navData;

    CallData callData;

    //------------------------------------------------
    // Buffers
    //------------------------------------------------

    char timeBuffer[6];

    char dayBuffer[12];

    //------------------------------------------------
    // Callbacks
    //------------------------------------------------

    static ChronosPhoneService* instance;

    static void ringerCallback(
        String caller,
        bool active);

    static void notificationCallback(
        Notification notification);

    static void connectionCallback(
        bool connected);
};