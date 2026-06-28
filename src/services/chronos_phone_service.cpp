#include "chronos_phone_service.h"

#include "config.h"
#include <Arduino.h>

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
