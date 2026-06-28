#pragma once

#include <Arduino.h>

//=========================
// OLED
//=========================

constexpr uint8_t OLED_SDA = 8;
constexpr uint8_t OLED_SCL = 9;

constexpr uint32_t OLED_I2C_SPEED = 400000;

//=========================
// Display
//=========================

constexpr uint16_t DISPLAY_WIDTH = 128;
constexpr uint16_t DISPLAY_HEIGHT = 64;

//=========================
// BLE
//=========================

constexpr char WATCH_NAME[] = "ChronosWatch";

//=========================
// Refresh
//=========================

constexpr uint16_t CLOCK_REFRESH = 1000;
constexpr uint16_t BATTERY_REFRESH = 30000;

//=========================
// UI
//=========================

constexpr uint8_t STATUSBAR_HEIGHT = 10;