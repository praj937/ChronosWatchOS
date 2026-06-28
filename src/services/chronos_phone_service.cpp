#include "chronos_phone_service.h"

#include "config.h"
#include <Arduino.h>
#include <cstring>

ChronosPhoneService::ChronosPhoneService()
    : watch(WatchConfig::WATCH_NAME)
{
}

void ChronosPhoneService::begin()
{
    Serial.println("================================");
    Serial.println("Starting Chronos...");
    Serial.print("BLE Name: ");
    Serial.println(WatchConfig::WATCH_NAME);

    watch.begin();

    Serial.println("Chronos started.");
    Serial.println("Waiting for phone...");
}

void ChronosPhoneService::update()
{
    watch.loop();

    static bool previous = false;

    bool current = watch.isConnected();

    if (current != previous)
    {
        Serial.print("BLE Connected = ");
        Serial.println(current);

        previous = current;
    }
}

bool ChronosPhoneService::connected()
{
    return watch.isConnected();
}

uint8_t ChronosPhoneService::phoneBattery()
{
    return watch.getPhoneBattery();
}

NavigationData ChronosPhoneService::navigation()
{
    Navigation nav = watch.getNavigation();

    // ---------- DEBUG ----------
    if (nav.active)
    {
        Serial.println();
        Serial.println("========== NAVIGATION ==========");

        Serial.print("Distance   : ");
        Serial.println(nav.distance);

        Serial.print("Title      : ");
        Serial.println(nav.title);

        Serial.print("Directions : ");
        Serial.println(nav.directions);

        Serial.print("Duration   : ");
        Serial.println(nav.duration);

        Serial.print("ETA        : ");
        Serial.println(nav.eta);

        Serial.print("Has Icon   : ");
        Serial.println(nav.hasIcon);

        Serial.println("===============================");
    }

    navData.active = nav.active;
    navData.hasIcon = nav.hasIcon;

    strncpy(
    navData.distance,
    nav.title.c_str(),
    sizeof(navData.distance) - 1);

    navData.distance[sizeof(navData.distance) - 1] = '\0';

    strncpy(
        navData.remaining,
        nav.duration.c_str(),
        sizeof(navData.remaining) - 1);

    navData.remaining[sizeof(navData.remaining) - 1] = '\0';

    strncpy(
        navData.road,
        nav.directions.c_str(),
        sizeof(navData.road) - 1);

    navData.road[sizeof(navData.road) - 1] = '\0';

    if (nav.hasIcon)
    {
        memcpy(
            navData.icon,
            nav.icon,
            sizeof(navData.icon));
    }

    return navData;
}

CallData ChronosPhoneService::call()
{
    return callData;
}

const char* ChronosPhoneService::timeString()
{
    sprintf(
        timeBuffer,
        "%02d:%02d",
        watch.getHour(),
        watch.getMinute());

    return timeBuffer;
}

const char* ChronosPhoneService::dayString()
{
    static const char* days[] =
    {
        "Sunday",
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday"
    };

    strcpy(dayBuffer, days[watch.getDayofWeek()]);

    return dayBuffer;
}