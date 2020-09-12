#include "CheckBox.hpp"

CheckBox::CheckBox(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, uint16_t y, String label, uint8_t *font)
    : ToggleButton(LCD, Touch, x, y, label, font)
{
}

CheckBox::CheckBox(lcd::UTFT *LCD, URTouch *Touch, HorizontalAlignment horizontalAlignment, VerticalAlignment verticalAlignment, String label, uint8_t *font)
    : ToggleButton(LCD, Touch, horizontalAlignment, verticalAlignment, label, font)
{
}

CheckBox::CheckBox(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, VerticalAlignment verticalAlignment, String label, uint8_t *font)
    : ToggleButton(LCD, Touch, x, verticalAlignment, label, font)
{
}

CheckBox::CheckBox(lcd::UTFT *LCD, URTouch *Touch, HorizontalAlignment horizontalAlignment, uint16_t y, String label, uint8_t *font)
    : ToggleButton(LCD, Touch, horizontalAlignment, y, label, font)
{
}

CheckBox::~CheckBox() {}

void CheckBox::draw()
{
    if (valid || !visible)
        return;

    LCD->setFont(font);
    LCD->setColor(foreground);
    LCD->setBackColor(background);

    LCD->print(text, getX() + 20, getY() + 2);

    LCD->drawRect(getX(), getY(), getX() + 15, getY() + 15);

    update();
    valid = true;
}

void CheckBox::update()
{
    LCD->setColor((selected) ? foreground : background);
    LCD->fillRect(getX() + 3, getY() + 3, getX() + 12, getY() + 12);
}