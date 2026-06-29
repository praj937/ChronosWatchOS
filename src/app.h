#pragma once

#include "services/chronos_phone_service.h"
#include "ui/ui_manager.h"

class App
{
public:
    void begin();
    void update();

private:
    ChronosPhoneService phone;
    UiManager ui{phone};
};
