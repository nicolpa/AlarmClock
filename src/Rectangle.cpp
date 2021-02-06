#include "Rectangle.hpp"

Rectangle::Rectangle(lcd::UTFT *LCD, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, bool fill)
    : GraphicalComponent(LCD, x1, y1, x2 - x1, y2 - y1, fill)
{
}

Rectangle::Rectangle(lcd::UTFT *LCD, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, lcd::Color color, bool fill) 
    : GraphicalComponent(LCD, x1, y1, x2 - x1, y2 - y1, fill)
{
    this->foreground = color;
}

Rectangle::~Rectangle()
{
}

void Rectangle::clear() 
{
    LCD->setColor(VGA_BLACK);
    if (fill)
        LCD->fillRect(getX(), getY(), getX() + getWidth(), getY() + getHeight());
    else
        LCD->drawRect(getX(), getY(), getX() + getWidth(), getY() + getHeight());

    invalidate();
}

void Rectangle::draw()
{
    if (valid || !visible)
        return;

    LCD->setColor((enable) ? foreground : disableForeground);
    if (fill)
        LCD->fillRect(getX(), getY(), getX() + getWidth(), getY() + getHeight());
    else
        LCD->drawRect(getX(), getY(), getX() + getWidth(), getY() + getHeight());

    valid = true;
}
