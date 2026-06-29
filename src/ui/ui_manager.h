#pragma once

#include <Arduino.h>
#include "services/iphone_service.h"

enum class ScreenId : uint8_t { Boot, Connecting, Home, Navigation, Call, Notification, Music, Settings };

class UiManager
{
public:
    explicit UiManager(IPhoneService& phoneService) : phone(phoneService) {}
    void begin();
    void update();

private:
    ScreenId selectScreen() const;
    void render(ScreenId screen);
    void drawBoot();
    void drawConnecting();
    void drawHome();
    void drawNavigation();
    void drawCall();
    void drawNotification();
    void drawMusic();
    void drawSettings();
    void drawBluetooth(int16_t x, int16_t y, bool connected);
    void drawBattery(int16_t x, int16_t y, uint8_t percent);
    void drawAppIcon(const char* app);
    void drawClipped(int16_t x, int16_t y, const char* text, size_t maxChars);

    IPhoneService& phone;
    ScreenId current = ScreenId::Boot;
    uint32_t bootAt = 0;
    uint32_t lastFrameAt = 0;
    uint32_t fingerprint = 0;
    bool dirty = true;
};
