#include <Arduino.h>

#include "app.h"
#include "display/display.h"

namespace { App app; }

void setup()
{
    Serial.begin(115200);

    Display.begin();

    app.begin();
}

void loop()
{
    app.update();
    delay(2);
}
