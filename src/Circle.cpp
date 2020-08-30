#include "Circle.hpp"

Circle::Circle(lcd::UTFT *LCD, uint16_t x, uint16_t y, uint16_t radius, bool fill) 
    : GraphicalComponent(LCD, x, y, radius, radius, fill)
{
    
}

Circle::~Circle() {

}

void Circle::draw() 
{
    LCD->setColor((enable) ? foreground : disableForeground);
    if(fill)
        LCD->fillCircle(getX(), getY(), width);
    else
        LCD->drawCircle(getX(), getY(), width);
}
