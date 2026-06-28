#pragma once

#include "iscreen.h"

class ConnectingScreen : public IScreen
{
public:
    void begin() override;
    void update() override;
    void draw() override;
};