#pragma once

#include "iscreen.h"

class NavigationScreen : public IScreen
{
public:

    void begin() override;

    void update() override;

    void draw() override;
};