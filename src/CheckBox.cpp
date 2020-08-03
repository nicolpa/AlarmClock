#include "CheckBox.hpp"

CheckBox::CheckBox(lcd::UTFT* LCD, URTouch* Touch, uint16_t x, uint16_t y, String label, uint8_t* font, word color, uint32_t backcolor)
    : ToggleButton(LCD, Touch, x, y, label, font, color, backcolor)
{

}

CheckBox::~CheckBox() {}

void CheckBox::draw() 
{
    LCD->setFont(font);
    LCD->setColor(foreground);
    LCD->setBackColor(background);

    LCD->print(text, getX() + 20, getY() + 2);

    LCD->drawRect(getX(), getY(), getX() + 15, getY() + 15);

    update();
}

void CheckBox::update() 
{
    LCD->setColor((selected) ? foreground : background);
    LCD->fillRect(getX() + 3, getY() + 3, getX() + 12, getY() + 12);
}