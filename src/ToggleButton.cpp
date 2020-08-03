#include "ToggleButton.hpp"

ToggleButton::ToggleButton(lcd::UTFT* LCD, URTouch* Touch, uint16_t x, uint16_t y, String label, uint8_t* font, word color, uint32_t backcolor)
    : AbstractButton(LCD, Touch, x, y, 0, 0, color, backcolor)
{
    clickable = true;

    LCD->setFont(font);
    width  = 20 + (LCD->getFontXsize() * String(label).length());
    height = (LCD->getFontYsize() < 15) ? 15 : LCD->getFontYsize();
}

ToggleButton::~ToggleButton() {}

bool ToggleButton::isSelected() 
{
    return selected;
}

void ToggleButton::setChecked(bool selected) 
{
    this->selected = selected;
}

void ToggleButton::toggle() 
{
    selected = (selected) ? false : true;
}