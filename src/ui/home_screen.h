#pragma once

#include "iscreen.h"

class HomeScreen : public IScreen
{
public:
    void begin() override;
    void update() override;
    void draw() override;
};