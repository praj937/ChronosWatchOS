#pragma once

#include "iscreen.h"

class BootScreen : public IScreen
{
public:

    void begin() override;

    void update() override;

    void draw() override;
};