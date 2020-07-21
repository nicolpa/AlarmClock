#include "Panel.hpp"

Panel::Panel(lcd::UTFT *LCD, uint16_t x, uint16_t y, uint16_t w, uint16_t h, word color, uint32_t backcolor, word borderColor)
    : Container(LCD, x, y, w, h), borderColor(borderColor)
{
}

Panel::~Panel()
{
}

bool Panel::onClick(uint16_t x, uint16_t y)
{
    for (uint16_t i = 0; i < nComponents; i++)
    {
        if (components[i]->onClick(x, y))
            return true;
    }

    return Component::onClick(x, y);
}

void Panel::draw()
{
    if(!visible) return;

    Container::draw();

    LCD->setColor(background);
    LCD->fillRect(getX(), getY(), getX() + width, getY() + height);
    
    int centerX;
    int centerY;

    LCD->setColor(borderColor);
    if (borderTop)
        LCD->drawHLine(getX(), getY(), getWidth());
    if (borderBottom)
        LCD->drawHLine(getX(), getY() + getHeight(), getWidth());
    if (borderLeft)
        LCD->drawVLine(getX(), getY(), getHeight());
    if (borderRight)
        LCD->drawVLine(getX() + getWidth(), getY(), getHeight());

    centerX = getX() + (getWidth() / 2);
    centerY = getY() + (getHeight() / 2);

    LCD->setColor(VGA_GREEN);
    LCD->drawVLine(centerX, centerY - 5, 10);

    LCD->setColor(VGA_RED);
    LCD->drawHLine(centerX - 5, centerY, 10);
}

void Panel::setBorder(bool top, bool bottom, bool left, bool right)
{
    borderTop = top;
    borderBottom = bottom;
    borderLeft = left;
    borderRight = right;
}

void Panel::setBorder(bool borders)
{
    borderTop = borders;
    borderBottom = borders;
    borderLeft = borders;
    borderRight = borders;
}