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
    // String msg = "(" + String(getPosX()) + ", " + String(getPosY()) + ")";
    // Serial.println(msg);

    Container::draw();

    LCD->setColor(foreground);
    int centerX;
    int centerY;

    if (parent != nullptr)
    {
        // LCD->drawRect(getPosX() + parent->getPosX(), getPosX() + parent->getPosY(), getPosX() + parent->getPosX() + getWidth(), getPosX() + parent->getPosY() + getHeight());
        LCD->setColor(background);
        // LCD->drawRect(getPosX() + parent->getPosX(), getPosX() + parent->getPosY(), getPosX() + parent->getPosX() + getWidth(), getPosX() + parent->getPosY() + getHeight());
        // LCD->drawRect(getPosX() + parent->getPosX() + paddingLeft, getPosX() + parent->getPosY() + paddingTop, getPosX() + parent->getPosX() + getWidth() - paddingRight, getPosX() + parent->getPosY() + getHeight() - paddingBottom);
        LCD->setColor(borderColor);
        if (borderTop)
            LCD->drawHLine(getX() + parent->getX(), getY() + parent->getY(), getWidth());
        if (borderBottom)
            LCD->drawHLine(getX() + parent->getX(), getY() + getHeight() + parent->getY(), getWidth());
        if (borderLeft)
            LCD->drawVLine(getX() + parent->getX(), getY() + parent->getY(), getHeight());
        if (borderRight)
            LCD->drawVLine(getX() + getWidth() + parent->getX(), getY() + parent->getY(), getHeight());

        centerX = getX() + parent->getX() + (getWidth() / 2);
        centerY = getY() + parent->getY() + (getHeight() / 2);
    }
    else
    {
        // LCD->drawRect(getPosX(), getPosX(), getPosX() + getWidth(), getPosX() + getHeight());
        LCD->setColor(background);
        // LCD->drawRect(getPosX(), getPosX(), getPosX() + getWidth(), getPosX() + getHeight());
        // LCD->drawRect(getPosX() + paddingLeft, getPosX() + paddingTop, getPosX() + getWidth() - paddingRight, getPosX() + getHeight() - paddingBottom);
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
    }

    // LCD->setColor(VGA_GREEN);
    // LCD->drawVLine(centerX, centerY - 5, 10);

    // LCD->setColor(VGA_RED);
    // LCD->drawHLine(centerX - 5, centerY, 10);
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