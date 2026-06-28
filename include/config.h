#pragma once

#include <Arduino.h>

namespace WatchConfig
{
    constexpr uint16_t DISPLAY_WIDTH = 128;
    constexpr uint16_t DISPLAY_HEIGHT = 64;

    constexpr uint8_t OLED_SDA = 8;
    constexpr uint8_t OLED_SCL = 9;

    constexpr uint32_t I2C_SPEED = 400000;

    constexpr char WATCH_NAME[] = "ChronosWatch";

    constexpr uint32_t CLOCK_REFRESH_MS = 1000;
    constexpr uint32_t BATTERY_REFRESH_MS = 30000;

    constexpr bool DEBUG_MODE = true;
}