#pragma once

#include <Arduino.h>

namespace Config
{
    // Display
    constexpr uint16_t DISPLAY_WIDTH  = 128;
    constexpr uint16_t DISPLAY_HEIGHT = 64;

    // OLED Pins
    constexpr uint8_t OLED_SDA = 8;
    constexpr uint8_t OLED_SCL = 9;

    // I2C
    constexpr uint32_t I2C_SPEED = 400000;

    // BLE
    constexpr char WATCH_NAME[] = "ChronosWatch";

    // Refresh
    constexpr uint32_t CLOCK_REFRESH_MS   = 1000;
    constexpr uint32_t BATTERY_REFRESH_MS = 30000;
}