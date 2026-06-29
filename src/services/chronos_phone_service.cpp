#include "chronos_phone_service.h"
#include <Arduino.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "config.h"

ChronosPhoneService* ChronosPhoneService::instance = nullptr;

ChronosPhoneService::ChronosPhoneService() : watch(WatchConfig::WATCH_NAME) { instance = this; }

void ChronosPhoneService::begin()
{
    watch.setConnectionCallback(connectionCallback);
    watch.setNotificationCallback(notificationCallback);
    watch.setRingerCallback(ringerCallback);
    watch.begin();
    Serial.printf("LaraOS %s BLE ready as %s\n", "2.0.0", WatchConfig::WATCH_NAME);
}

void ChronosPhoneService::update()
{
    watch.loop();
    const uint32_t now = millis();
    if (callData.active && now - callData.receivedAt >= WatchConfig::CALL_DURATION_MS) callData.active = false;
    if (notificationData.active && now - notificationData.receivedAt >= WatchConfig::NOTIFICATION_DURATION_MS) notificationData.active = false;
}

bool ChronosPhoneService::connected()
{
    return watch.isConnected();
}

uint8_t ChronosPhoneService::phoneBattery()
{
    return watch.getPhoneBattery();
}

void ChronosPhoneService::musicControl(Control command) { watch.musicControl(command); }

void ChronosPhoneService::copy(char* destination, size_t size, const String& source)
{
    if (size == 0) return;
    source.substring(0, size - 1).toCharArray(destination, size);
}

void ChronosPhoneService::connectionCallback(bool state)
{
    Serial.printf("Phone %s\n", state ? "connected" : "disconnected");
}

void ChronosPhoneService::ringerCallback(String caller, bool active)
{
    if (!instance) return;
    instance->callData.active = active;
    instance->callData.receivedAt = millis();
    copy(instance->callData.caller, sizeof(instance->callData.caller), caller);
}

void ChronosPhoneService::notificationCallback(Notification notification)
{
    if (!instance) return;
    NotificationData& data = instance->notificationData;
    data.active = true;
    data.receivedAt = millis();
    data.icon = notification.icon;
    copy(data.app, sizeof(data.app), notification.app);
    copy(data.title, sizeof(data.title), notification.title);
    copy(data.message, sizeof(data.message), notification.message);
}

Maneuver ChronosPhoneService::classify(const char* instruction)
{
    char text[96]{};
    size_t i = 0;
    for (; instruction[i] && i < sizeof(text) - 1; ++i) text[i] = static_cast<char>(tolower(static_cast<unsigned char>(instruction[i])));
    if (strstr(text, "destination") || strstr(text, "arrive")) return Maneuver::Destination;
    if (strstr(text, "roundabout")) return Maneuver::Roundabout;
    if (strstr(text, "u-turn") || strstr(text, "uturn")) return strstr(text, "right") ? Maneuver::UTurnRight : Maneuver::UTurnLeft;
    if (strstr(text, "slight left")) return Maneuver::SlightLeft;
    if (strstr(text, "slight right")) return Maneuver::SlightRight;
    if (strstr(text, "sharp left")) return Maneuver::SharpLeft;
    if (strstr(text, "sharp right")) return Maneuver::SharpRight;
    if (strstr(text, "keep left")) return Maneuver::KeepLeft;
    if (strstr(text, "keep right")) return Maneuver::KeepRight;
    if (strstr(text, "merge")) return Maneuver::Merge;
    if (strstr(text, "exit")) return Maneuver::Exit;
    if (strstr(text, "left")) return Maneuver::Left;
    if (strstr(text, "right")) return Maneuver::Right;
    return Maneuver::Straight;
}

const NavigationData& ChronosPhoneService::navigation()
{
    const Navigation nav = watch.getNavigation();
    navData.active = nav.active && nav.isNavigation;
    copy(navData.distance, sizeof(navData.distance), nav.title.length() ? nav.title : nav.distance);
    copy(navData.road, sizeof(navData.road), nav.directions);
    navData.maneuver = classify(navData.road);
    return navData;
}

const char* ChronosPhoneService::timeString()
{
    snprintf(timeBuffer, sizeof(timeBuffer), "%02d:%02d", watch.getHour(), watch.getMinute());
    return timeBuffer;
}

const char* ChronosPhoneService::dayString()
{
    static const char* const days[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    const uint8_t day = watch.getDayofWeek();
    strncpy(dayBuffer, days[day < 7 ? day : 0], sizeof(dayBuffer) - 1);
    return dayBuffer;
}
