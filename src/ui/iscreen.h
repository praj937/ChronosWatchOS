#pragma once

class IScreen
{
public:

    virtual ~IScreen() = default;

    virtual void begin() = 0;

    virtual void update() = 0;

    virtual void draw() = 0;

};