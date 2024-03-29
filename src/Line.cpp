#include "Line.hpp"

Line::Line(lcd::UTFT *LCD, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
    : GraphicalComponent(LCD, x1, y1, x2 - x1, y2 - y1)
{
}

Line::Line(lcd::UTFT *LCD, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, lcd::Color color) 
    : GraphicalComponent(LCD, x1, y1, x2 - x1, y2 - y1)
{
    this->foreground = color;
}

Line::~Line()
{
}

void Line::clear() 
{
    LCD->setColor(VGA_BLACK);
    LCD->drawLine(getX(), getY(), getX() + getWidth(), getY() + getHeight());

    invalidate();
}

void Line::draw()
{
    if (valid || !visible)
        return;

    LCD->setColor((enable) ? foreground : disableForeground);
    LCD->drawLine(getX(), getY(), getX() + getWidth(), getY() + getHeight());

    valid = true;
}