#include "Frame.hpp"

Frame::Frame(lcd::UTFT *LCD, word background) 
    : Container(0, 0, LCD->getDisplayXSize() - 1, LCD->getDisplayYSize() - 1)
{
    this->LCD = LCD;
    this->background = background;
}

Frame::~Frame() {

}

void Frame::draw() 
{
    if(valid)
        return;

    // if(background != VGA_TRANSPARENT)
    //     LCD->fillScr(background);
        
    Container::draw();

    int centerX = getX() + (getWidth() / 2);
    int centerY = getY() + (getHeight() / 2);

    LCD->setColor(VGA_GREEN);
    LCD->drawVLine(centerX, centerY - 5, 10);

    LCD->setColor(VGA_RED);
    LCD->drawHLine(centerX - 5, centerY, 10);

    valid = true;
}