#pragma once

#include <Arduino.h>

class Logger
{
public:

    static void begin();

    static void info(const String &msg);

    static void warn(const String &msg);

    static void error(const String &msg);

};