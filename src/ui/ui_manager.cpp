#include "ui_manager.h"
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "config.h"
#include "display/display.h"
#include "navigation_icons.h"
#include "version.h"

namespace
{
uint32_t hashText(uint32_t hash, const char* text)
{
    while (*text) { hash = (hash ^ static_cast<uint8_t>(*text++)) * 16777619UL; }
    return hash;
}
}

void UiManager::begin()
{
    bootAt = millis();
    current = ScreenId::Boot;
    dirty = true;
}
ScreenId UiManager::selectScreen() const
{
    const uint32_t now = millis();

    if (now - bootAt < WatchConfig::BOOT_DURATION_MS)
        return ScreenId::Boot;

    // -----------------------------
    // CALL (Highest Priority)
    // -----------------------------
    if (phone.call().active)
    {
        const_cast<UiManager*>(this)->callUntil =
            now + WatchConfig::CALL_DURATION_MS;
    }

    if (now < callUntil)
        return ScreenId::Call;

    // -----------------------------
    // NOTIFICATION
    // -----------------------------
    if (phone.notification().active)
    {
        const_cast<UiManager*>(this)->notificationUntil =
            now + WatchConfig::NOTIFICATION_DURATION_MS;
    }

    if (now < notificationUntil)
        return ScreenId::Notification;

    // -----------------------------
    // NAVIGATION
    // -----------------------------
    if (phone.navigation().active)
        return ScreenId::Navigation;

    // -----------------------------
    // MUSIC
    // -----------------------------
    if (phone.music().active)
        return ScreenId::Music;

    // -----------------------------
    // HOME / CONNECTING
    // -----------------------------
    return phone.connected()
           ? ScreenId::Home
           : ScreenId::Connecting;
}

void UiManager::update()
{
    const ScreenId wanted = selectScreen();
    if (wanted != current) { current = wanted; dirty = true; }
    const uint32_t now = millis();
    if (!dirty && now - lastFrameAt < WatchConfig::FRAME_INTERVAL_MS) return;

    uint32_t next = 2166136261UL;
    next = (next ^ static_cast<uint8_t>(current)) * 16777619UL;
    next = hashText(next, phone.timeString());
    next = hashText(next, phone.navigation().distance);
    next = hashText(next, phone.navigation().road);
    next = hashText(next, phone.notification().title);
    next = hashText(next, phone.notification().message);
    next = hashText(next, phone.call().caller);
    next ^= phone.phoneBattery();
    if (current != ScreenId::Navigation)
{
    if (!dirty && next == fingerprint)
        return;
}
     fingerprint = next;
    render(current);
    dirty = false;
    lastFrameAt = now;
}

void UiManager::render(ScreenId screen)
{
    Display.clear();
    switch (screen)
    {
        case ScreenId::Boot: drawBoot(); break;
        case ScreenId::Connecting: drawConnecting(); break;
        case ScreenId::Home: drawHome(); break;
        case ScreenId::Navigation: drawNavigation(); break;
        case ScreenId::Call: drawCall(); break;
        case ScreenId::Notification: drawNotification(); break;
        case ScreenId::Music: drawMusic(); break;
        case ScreenId::Settings: drawSettings(); break;
    }
    Display.present();
}

void UiManager::drawBluetooth(int16_t x, int16_t y, bool connected)
{
    Display.line(x + 3, y, x + 3, y + 10); Display.line(x + 3, y, x + 7, y + 3);
    Display.line(x + 7, y + 3, x, y + 8); Display.line(x, y + 2, x + 7, y + 8);
    Display.line(x + 7, y + 8, x + 3, y + 10);
    if (!connected) Display.line(x - 1, y, x + 8, y + 10);
}

void UiManager::drawBattery(int16_t x, int16_t y, uint8_t percent)
{
    Display.frame(x, y, 16, 8); Display.box(x + 16, y + 2, 2, 4);
    const uint8_t fill = static_cast<uint8_t>((percent > 100 ? 100 : percent) * 14 / 100);
    if (fill) Display.box(x + 1, y + 1, fill, 6);
}

void UiManager::drawBoot()
{
    Display.frame(10, 7, 108, 42);
    Display.centered(34, Font::Huge, "LaraOS");
    char version[18]{}; snprintf(version, sizeof(version), "version %s", Version::NUMBER);
    Display.centered(61, Font::Small, version);
}

void UiManager::drawConnecting()
{
    drawBluetooth(58, 6, true);
    Display.centered(39, Font::Large, "Bluetooth");
    Display.centered(57, Font::Medium, "Waiting for Phone");
}

void UiManager::drawHome()
{
    drawBluetooth(3, 1, phone.connected());

    drawBattery(109,1, phone.phoneBattery());


    // Clock
    Display.centered(34, Font::Huge, phone.timeString());

    // Day
    Display.centered(51, Font::Medium, phone.dayString());

    // Bottom Left - Date
    Display.setFont(Font::Tiny);
    Display.text(2, 63, phone.dateString());

    // Bottom Right - LaraOS
    int width = Display.textWidth("LaraOS");
    Display.text(126 - width, 63, "LaraOS");
}

void UiManager::drawClipped(int16_t x, int16_t y, const char* text, size_t maxChars)
{
    char clipped[65]{};
    const size_t count = strlen(text) < maxChars ? strlen(text) : maxChars;
    memcpy(clipped, text, count);
    if (text[count] && count > 2) { clipped[count - 2] = '.'; clipped[count - 1] = '.'; }
    Display.text(x, y, clipped);
}

void UiManager::drawNavigation()
{
    const NavigationData& nav = phone.navigation();

    //------------------------------------------
    // Navigation Icon (48x48)
    //------------------------------------------

    Display.bitmap(
        2,
        2,
        48,
        48,
        NavigationIcons::get(nav.maneuver));

    //------------------------------------------
    // Split distance
    //------------------------------------------

    char value[12] = "";
    char unit[8] = "";

    if (sscanf(nav.distance, "%11s %7s", value, unit) < 2)
    {
        strncpy(value, nav.distance, sizeof(value) - 1);
        value[sizeof(value) - 1] = '\0';
    }

    //------------------------------------------
    // Distance
    //------------------------------------------

    Display.setFont(Font::Huge);

    int valueWidth = Display.textWidth(value);

    Display.text(
        124 - valueWidth,
        28,
        value);

    //------------------------------------------
    // Unit
    //------------------------------------------

    Display.setFont(Font::Medium);

    int unitWidth = Display.textWidth(unit);

    Display.text(
        124 - unitWidth,
        45,
        unit);

    //------------------------------------------
    // Divider
    //------------------------------------------

    Display.line(2, 51, 125, 51);

    //------------------------------------------
    // Road Name
    //------------------------------------------

    Display.setFont(Font::Small);

    int width = Display.textWidth(nav.road);

    if (width <= 122)
    {
        // Short road names stay centered
        Display.centered(
            63,
            Font::Small,
            nav.road);

        roadOffset = 0;
    }
    else
    {
        // Scroll only long names
        if (millis() - roadScrollTimer > 70)
        {
            roadScrollTimer = millis();

            roadOffset++;

            if (roadOffset > width + 30)
                roadOffset = 0;
        }

        Display.text(
            124 - roadOffset,
            63,
            nav.road);

        Display.text(
            124 - roadOffset + width + 30,
            63,
            nav.road);
    }
}

void UiManager::drawCall()
{
    Display.centered(9, Font::Small, "INCOMING CALL");
    Display.centered(34, Font::Large, phone.call().caller[0] ? phone.call().caller : "Unknown caller");
    Display.disc(25, 53, 9); Display.setFont(Font::Medium); Display.text(20, 57, "+");
    Display.disc(103, 53, 9); Display.setFont(Font::Medium); Display.text(99, 57, "x");
    Display.setFont(Font::Small); Display.text(38, 57, "answer     reject");
}

void UiManager::drawAppIcon(const char* app)
{
    char letter[2] = {'N', 0};
    if (app && app[0]) letter[0] = static_cast<char>(toupper(static_cast<unsigned char>(app[0])));
    Display.frame(2, 2, 22, 22); Display.setFont(Font::Large); Display.text(7, 21, letter);
}

void UiManager::drawNotification()
{
    const NotificationData& note = phone.notification();
    drawAppIcon(note.app);
    Display.setFont(Font::Small); drawClipped(29, 8, note.app, 19);
    Display.setFont(Font::Medium); drawClipped(29, 23, note.title, 16);
    Display.line(0, 29, 127, 29);
    Display.setFont(Font::Small); drawClipped(2, 42, note.message, 25);
    if (strlen(note.message) > 25) drawClipped(2, 54, note.message + 25, 25);
}

void UiManager::drawMusic()
{
    const MusicData& music = phone.music();
    Display.setFont(Font::Medium); drawClipped(2, 13, music.song, 20);
    Display.setFont(Font::Small); drawClipped(2, 25, music.artist, 25);
    Display.setFont(Font::Large); Display.text(17, 49, "<"); Display.text(57, 49, music.playing ? "||" : ">"); Display.text(103, 49, ">");
    Display.frame(4, 57, 120, 5); Display.box(5, 58, static_cast<int16_t>(118 * music.progress / 100), 3);
}

void UiManager::drawSettings()
{
    Display.centered(23, Font::Large, "SETTINGS");
    Display.centered(45, Font::Medium, "LaraOS 2.0");
    Display.centered(61, Font::Small, "No options available");
}
