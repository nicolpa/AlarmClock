#include "Frame.hpp"

Frame::Frame(lcd::UTFT *LCD, word background)
    : Container(LCD, 0, 0, LCD->getDisplayXSize() - 1, LCD->getDisplayYSize() - 1)
{
    this->background = background;
    transparent = true;
}

Frame::~Frame()
{
}

void Frame::clear() 
{
    LCD->clrScr();
    Container::clear();
}

void Frame::draw()
{
    if (valid || !visible)
        return;

    if (!transparent)
    {
        LCD->setColor((enable) ? background : disableBackground);
        LCD->fillRect(getX(), getY(), getX() + getWidth(), getY() + getHeight());
    }

    Container::draw();
}