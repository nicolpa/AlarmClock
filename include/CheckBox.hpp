#pragma once

#include "ToggleButton.hpp"

class CheckBox : public ToggleButton
{

public:
    CheckBox(lcd::UTFT* LCD, URTouch* Touch, uint16_t x, uint16_t y, String label, uint8_t* font, word color = VGA_WHITE, uint32_t backcolor = VGA_BLACK);
    ~CheckBox();

    void draw() override;

protected:
    void update() override;
};