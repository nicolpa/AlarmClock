#pragma once

#include "ToggleButtonHolder.hpp"

class RadioButtonHolder : public ToggleButtonHolder
{

public:
    RadioButtonHolder();
    ~RadioButtonHolder();

    bool onClick(uint16_t x, uint16_t y) override;
};