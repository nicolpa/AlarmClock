#include "RadioButton.hpp"

RadioButton::RadioButton(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, uint16_t y, String label, uint8_t *font)
    : ToggleButton(LCD, Touch, x, y, label, font)
{
}

RadioButton::RadioButton(lcd::UTFT *LCD, URTouch *Touch, HorizontalAlignment horizontalAlignment, VerticalAlignment verticalAlignment, String label, uint8_t *font)
    : ToggleButton(LCD, Touch, horizontalAlignment, verticalAlignment, label, font)
{
}

RadioButton::RadioButton(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, VerticalAlignment verticalAlignment, String label, uint8_t *font)
    : ToggleButton(LCD, Touch, x, verticalAlignment, label, font)
{
}

RadioButton::RadioButton(lcd::UTFT *LCD, URTouch *Touch, HorizontalAlignment horizontalAlignment, uint16_t y, String label, uint8_t *font)
    : ToggleButton(LCD, Touch, horizontalAlignment, y, label, font)
{
}

RadioButton::~RadioButton() {}

void RadioButton::draw()
{
    if (valid || !visible)
        return;

    LCD->setFont(font);
    LCD->setColor(foreground);
    LCD->setBackColor(background);

    LCD->print(text, getX() + 20, getY() + 2);

    LCD->drawCircle(getX() + 7, getY() + 7, 7);

    update();
    valid = true;
}

Component *RadioButton::onClick(uint16_t x, uint16_t y)
{
    if (!selected)
        return ToggleButton::onClick(x, y);

    return nullptr;
}

void RadioButton::update()
{
    LCD->setColor((selected) ? foreground : background);
    LCD->fillCircle(getX() + 7, getY() + 7, 4);
}