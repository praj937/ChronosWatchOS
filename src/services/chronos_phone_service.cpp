#include "chronos_phone_service.h"

void ChronosPhoneService::begin()
{

}

void ChronosPhoneService::update()
{

}

bool ChronosPhoneService::connected()
{
    return isConnected;
}

uint8_t ChronosPhoneService::phoneBattery()
{
    return battery;
}

NavigationData ChronosPhoneService::navigation()
{
    return nav;
}

CallData ChronosPhoneService::call()
{
    return callInfo;
}