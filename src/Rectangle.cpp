#include "Rectangle.hpp"

Rectangle::Rectangle(lcd::UTFT *LCD, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, bool fill)
    : GraphicalComponent(LCD, x1, y1, x2 - x1, y2 - y1, fill)
{
}

Rectangle::~Rectangle()
{
}

void Rectangle::clear() 
{
    LCD->setColor(VGA_BLACK);
    if (fill)
        LCD->fillRect(getX(), getY(), getX() + width, getY() + height);
    else
        LCD->drawRect(getX(), getY(), getX() + width, getY() + height);

    invalidate();
}

void Rectangle::draw()
{
    if (valid || !visible)
        return;

    LCD->setColor((enable) ? foreground : disableForeground);
    if (fill)
        LCD->fillRect(getX(), getY(), getX() + width, getY() + height);
    else
        LCD->drawRect(getX(), getY(), getX() + width, getY() + height);

    valid = true;
}
