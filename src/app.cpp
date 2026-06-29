#include "app.h"

void App::begin()
{
    phone.begin();
    ui.begin();
}

void App::update()
{
    phone.update();
    ui.update();
}
