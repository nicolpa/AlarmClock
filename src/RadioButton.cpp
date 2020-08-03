#include "RadioButton.hpp"

RadioButton::RadioButton(lcd::UTFT* LCD, URTouch* Touch, uint16_t x, uint16_t y, String label, uint8_t* font, word color, uint32_t backcolor) 
    : ToggleButton(LCD, Touch, x, y, label, font, color, backcolor)
{
}

RadioButton::~RadioButton() {}

void RadioButton::draw() 
{
    LCD->setFont(font);
    LCD->setColor(foreground);
    LCD->setBackColor(background);

    LCD->print(text, getX() + 20, getY() + 2);

    LCD->drawCircle(getX() + 7, getY() + 7, 7);

    update();
}

bool RadioButton::onClick(uint16_t x, uint16_t y) 
{
    if(!selected)
        return ToggleButton::onClick(x, y);
    
    return false;
}

void RadioButton::update() 
{
    LCD->setColor((selected) ? foreground : background);
    LCD->fillCircle(getX() + 7, getY() + 7, 4);  
}