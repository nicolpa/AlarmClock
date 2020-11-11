#include "Panel.hpp"

Panel::Panel(lcd::UTFT *LCD, uint16_t x, uint16_t y, uint16_t width, uint16_t height, lcd::Color borderColor)
    : Container(LCD, x, y, width, height), borderColor(borderColor)
{
}

Panel::Panel(lcd::UTFT *LCD, HorizontalAlignment horizontalAlignment, VerticalAlignment verticalAlignment, uint16_t width, uint16_t height, lcd::Color borderColor)
    : Container(LCD, horizontalAlignment, verticalAlignment, width, height)
{
}

Panel::Panel(lcd::UTFT *LCD, uint16_t x, VerticalAlignment verticalAlignment, uint16_t width, uint16_t height, lcd::Color borderColor)
    : Container(LCD, x, verticalAlignment, width, height)
{
}

Panel::Panel(lcd::UTFT *LCD, HorizontalAlignment horizontalAlignment, uint16_t y, uint16_t width, uint16_t height, lcd::Color borderColor)
    : Container(LCD, horizontalAlignment, y, width, height)
{
}

Panel::~Panel()
{
}

void Panel::clear() 
{
    LCD->setColor(VGA_BLACK);
    LCD->fillRect(getX(), getY(), getX() + width, getY() + height);
    Container::clear();
}

void Panel::draw()
{
    if (valid || !visible)
        return;

    if (!transparent)
    {
        LCD->setColor((enable) ? background : disableBackground);
        LCD->fillRect(getX() + (borderLeft) ? 1 : 0, getY() + (borderTop) ? 1 : 0,
                      getX() + getWidth() - (borderRight) ? 1 : 0, getY() + getHeight() - (borderBottom) ? 1 : 0);
    }

    LCD->setColor((enable) ? foreground : disableBackground);
    if (borderTop)
        LCD->drawHLine(getX(), getY(), getWidth());
    if (borderBottom)
        LCD->drawHLine(getX(), getY() + getHeight(), getWidth());
    if (borderLeft)
        LCD->drawVLine(getX(), getY(), getHeight());
    if (borderRight)
        LCD->drawVLine(getX() + getWidth(), getY(), getHeight());

    Container::draw();
}

void Panel::setBorder(bool top, bool bottom, bool left, bool right)
{
    borderTop = top;
    borderBottom = bottom;
    borderLeft = left;
    borderRight = right;

    valid = false;
}

void Panel::setBorder(bool borders)
{
    borderTop = borders;
    borderBottom = borders;
    borderLeft = borders;
    borderRight = borders;

    valid = false;
}