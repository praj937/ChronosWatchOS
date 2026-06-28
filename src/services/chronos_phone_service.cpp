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