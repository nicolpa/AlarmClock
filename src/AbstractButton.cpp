#include "AbstractButton.hpp"

AbstractButton::AbstractButton(lcd::UTFT* LCD, URTouch* Touch, uint16_t x, uint16_t y, uint16_t w, uint16_t h, word color, uint32_t backcolor) 
    :Component(LCD, Touch, x, y, w, h, color, backcolor)
{

}

AbstractButton::~AbstractButton() 
{

}


void AbstractButton::setText(String text) 
{
    this->text = text;
}


String AbstractButton::getText() 
{
    return text;
}

void AbstractButton::setPressed(bool pressed) 
{
    this->pressed = pressed;
}

bool AbstractButton::getPressed() 
{
    return pressed;
}