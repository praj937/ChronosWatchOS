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

    // Reset previous data
    memset(&navData, 0, sizeof(navData));

    navData.active = nav.active;

    if (!nav.active)
    {
        return navData;
    }

    navData.hasIcon = nav.hasIcon;

    //--------------------------------------------------
    // Distance to next turn
    //--------------------------------------------------

    strncpy(
        navData.distance,
        nav.title.c_str(),
        sizeof(navData.distance) - 1);

    navData.distance[sizeof(navData.distance) - 1] = '\0';

    //--------------------------------------------------
    // Remaining time (kept for future use)
    //--------------------------------------------------

    strncpy(
        navData.remaining,
        nav.duration.c_str(),
        sizeof(navData.remaining) - 1);

    navData.remaining[sizeof(navData.remaining) - 1] = '\0';

    //--------------------------------------------------
    // Road name
    //--------------------------------------------------

    strncpy(
        navData.road,
        nav.directions.c_str(),
        sizeof(navData.road) - 1);

    navData.road[sizeof(navData.road) - 1] = '\0';

    //--------------------------------------------------
    // Navigation icon
    //--------------------------------------------------

    if (nav.hasIcon && nav.icon != nullptr)
    {
        memcpy(
            navData.icon,
            nav.icon,
            sizeof(navData.icon));
    }

#ifdef DEBUG_NAVIGATION
    Serial.println();
    Serial.println("========== NAVIGATION ==========");
    Serial.print("Distance : ");
    Serial.println(navData.distance);
    Serial.print("Road     : ");
    Serial.println(navData.road);
    Serial.print("Duration : ");
    Serial.println(navData.remaining);
    Serial.print("Icon     : ");
    Serial.println(navData.hasIcon);
    Serial.println("================================");
#endif

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