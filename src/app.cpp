#include "app.h"

#include "services/chronos_phone_service.h"
#include "ui/screen_manager.h"

ChronosPhoneService Phone;

void App::begin()
{
    Phone.begin();

    Screens.begin();

    Screens.set(Screen::Boot);
}

void App::update()
{
    Phone.update();

    Screens.update();
}