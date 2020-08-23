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
    // if(background != VGA_TRANSPARENT)
    //     LCD->fillScr(background);
    Container::draw();
}