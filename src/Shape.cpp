#include "Shape.hpp"

Shape::Shape(lcd::UTFT *LCD, Segment* segments, uint16_t nSegments, word color) 
    : LCD(LCD), segments(segments), nSegments(nSegments), color(color)
{

}

Shape::~Shape() 
{
    delete segments;
}

void Shape::draw() 
{
    LCD->setColor(color);
    for(uint16_t i = 0; i < nSegments; i++)
        segments[i].draw(LCD, color);
}

void Shape::setColor(word color) 
{
    this->color = color;
}
