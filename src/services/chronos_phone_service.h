#pragma once

#include <ChronosESP32.h>
#include "iphone_service.h"

class ChronosPhoneService final : public IPhoneService
{
public:
    ChronosPhoneService();
    void begin() override;
    void update() override;
    bool connected() override;
    uint8_t phoneBattery() override;
    const char* timeString() override;
    const char* dayString() override;
    const char* dateString() override;
    const NavigationData& navigation() override;
    const CallData& call() const override { return callData; }
    const NotificationData& notification() const override { return notificationData; }
    const MusicData& music() const override { return musicData; }
    void musicControl(Control command);

private:
    static ChronosPhoneService* instance;
    static void ringerCallback(String caller, bool active);
    static void notificationCallback(Notification notification);
    static void connectionCallback(bool connected);
    static void copy(char* destination, size_t size, const String& source);
    static Maneuver classify(const char* instruction);

    ChronosESP32 watch;
    NavigationData navData{};
    CallData callData{};
    NotificationData notificationData{};
    MusicData musicData{};
    char timeBuffer[6]{};
    char dayBuffer[12]{};
    char dateBuffer[20]{};
};
