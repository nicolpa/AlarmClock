#pragma once

#include "ToggleButton.hpp"

class CheckBox : public ToggleButton
{

public:
    CheckBox(lcd::UTFT* LCD, URTouch* Touch, uint16_t x, uint16_t y, String label, uint8_t* font);
    CheckBox(lcd::UTFT* LCD, URTouch* Touch, HorizontalAlignment horizontalAlignment, VerticalAlignment verticalAlignment, String label, uint8_t* font);
    CheckBox(lcd::UTFT* LCD, URTouch* Touch, uint16_t x, VerticalAlignment verticalAlignment, String label, uint8_t* font);
    CheckBox(lcd::UTFT* LCD, URTouch* Touch, HorizontalAlignment horizontalAlignment, uint16_t y, String label, uint8_t* font);
    ~CheckBox();

    void draw() override;

protected:
    void update() override;
};