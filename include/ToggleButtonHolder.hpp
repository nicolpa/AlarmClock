#pragma once

#include "Panel.hpp"
#include "RadioButton.hpp"
#include "CheckBox.hpp"

class ToggleButtonHolder : public Panel
{

public:
    ToggleButtonHolder(lcd::UTFT* LCD, uint16_t x, uint16_t y, uint16_t width, uint16_t height, lcd::Color borderColor = lcd::WHITE);
    ToggleButtonHolder(lcd::UTFT* LCD, HorizontalAlignment horizontalAlignment, VerticalAlignment verticalAlignment, uint16_t width, uint16_t height, lcd::Color borderColor = lcd::WHITE);
    ToggleButtonHolder(lcd::UTFT* LCD, uint16_t x, VerticalAlignment verticalAlignment, uint16_t width, uint16_t height, lcd::Color borderColor = lcd::WHITE);
    ToggleButtonHolder(lcd::UTFT* LCD, HorizontalAlignment horizontalAlignment, uint16_t y, uint16_t width, uint16_t height, lcd::Color borderColor = lcd::WHITE);
    ~ToggleButtonHolder();

    bool* getSelectedButtons();
};