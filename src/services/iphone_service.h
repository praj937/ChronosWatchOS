#pragma once

#include <stdint.h>

enum class Maneuver : uint8_t
{
    Straight, Left, Right, SlightLeft, SlightRight, SharpLeft, SharpRight,
    UTurnLeft, UTurnRight, Roundabout, Destination, Merge, Exit, KeepLeft, KeepRight
};

struct NavigationData
{
    bool active = false;
    char distance[16]{};
    char road[64]{};
    Maneuver maneuver = Maneuver::Straight;
};

struct CallData { bool active = false; uint32_t receivedAt = 0; char caller[64]{}; };
struct NotificationData
{
    bool active = false;
    uint32_t receivedAt = 0;
    int icon = 0;
    char app[20]{};
    char title[48]{};
    char message[96]{};
};
struct MusicData
{
    bool active = false;
    bool playing = false;
    uint8_t progress = 0;
    char song[48]{};
    char artist[40]{};
};

class IPhoneService
{
public:
    virtual ~IPhoneService() = default;
    virtual void begin() = 0;
    virtual void update() = 0;
    virtual bool connected() = 0;
    virtual uint8_t phoneBattery() = 0;
    virtual const char* timeString() = 0;
    virtual const char* dayString() = 0;
    virtual const NavigationData& navigation() = 0;
    virtual const CallData& call() const = 0;
    virtual const NotificationData& notification() const = 0;
    virtual const MusicData& music() const = 0;
};
