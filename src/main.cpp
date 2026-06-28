#include <Arduino.h>

#include "display/display.h"

void setup()
{
    Display.begin();

    Display.drawBootScreen();
}

void loop()
{

}