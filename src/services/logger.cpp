#include "logger.h"

void Logger::begin()
{
    Serial.begin(115200);

    delay(100);

    Serial.println();
    Serial.println("==============================");
    Serial.println("ChronosWatchOS Booting");
    Serial.println("==============================");
}

void Logger::info(const String &msg)
{
    Serial.print("[INFO] ");
    Serial.println(msg);
}

void Logger::warn(const String &msg)
{
    Serial.print("[WARN] ");
    Serial.println(msg);
}

void Logger::error(const String &msg)
{
    Serial.print("[ERROR] ");
    Serial.println(msg);
}