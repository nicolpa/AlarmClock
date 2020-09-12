#pragma once

#include "ToggleButtonHolder.hpp"

class RadioButtonHolder : public ToggleButtonHolder
{

public:
    RadioButtonHolder(lcd::UTFT* LCD, uint16_t x, uint16_t y, uint16_t width, uint16_t height, word borderColor = VGA_WHITE);
    RadioButtonHolder(lcd::UTFT* LCD, HorizontalAlignment horizontalAlignment, VerticalAlignment verticalAlignment, uint16_t width, uint16_t height, word borderColor = VGA_WHITE);
    RadioButtonHolder(lcd::UTFT* LCD, uint16_t x, VerticalAlignment verticalAlignment, uint16_t width, uint16_t height, word borderColor = VGA_WHITE);
    RadioButtonHolder(lcd::UTFT* LCD, HorizontalAlignment horizontalAlignment, uint16_t y, uint16_t width, uint16_t height, word borderColor = VGA_WHITE);
    ~RadioButtonHolder();

    bool onClick(uint16_t x, uint16_t y) override;
};