#include "chronos_phone_service.h"

#include "config.h"

ChronosPhoneService::ChronosPhoneService()
    : watch(WatchConfig::WATCH_NAME)
{
}

void ChronosPhoneService::begin()
{
    watch.begin();
}

void ChronosPhoneService::update()
{
    watch.loop();
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