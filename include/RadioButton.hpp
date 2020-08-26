#pragma once

#include "ToggleButton.hpp"

class RadioButton : public ToggleButton
{

public:
    RadioButton(lcd::UTFT* LCD, URTouch* Touch, uint16_t x, uint16_t y, String label, uint8_t* font);
    RadioButton(lcd::UTFT* LCD, URTouch* Touch, HorizontalAlignment horizontalAlignment, VerticalAlignment verticalAlignment, String label, uint8_t* font);
    RadioButton(lcd::UTFT* LCD, URTouch* Touch, uint16_t x, VerticalAlignment verticalAlignment, String label, uint8_t* font);
    RadioButton(lcd::UTFT* LCD, URTouch* Touch, HorizontalAlignment horizontalAlignment, uint16_t y, String label, uint8_t* font);
    ~RadioButton();

    void draw() override;

    bool onClick(uint16_t x, uint16_t y) override;

protected:
    void update() override;
};