#include "Triangle.hpp"

Triangle::Triangle(lcd::UTFT *LCD, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, bool fill)
    : GraphicalComponent(LCD, 0, 0, 0, 0, fill), x1(x1), y1(y1), x2(x2), y2(y2), x3(x3), y3(y3)
{
    x = min(x1, min(x2, x3));
    y = min(y1, min(y2, y3));
    width = max(x1, max(x2, x3)) - x;
    height = max(y1, max(y2, y3)) - y;
}

Triangle::~Triangle()
{
}

void Triangle::draw()
{
    if (valid || !visible)
        return;

    LCD->setColor((enable) ? foreground : disableForeground);
    if (fill)
        LCD->fillTriangle(x1, y1, x2, y2, x3, y3);
    else
        LCD->drawTriangle(x1, y1, x2, y2, x3, y3);

    valid = true;
}
