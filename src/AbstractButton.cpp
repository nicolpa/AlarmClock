#include "AbstractButton.hpp"

AbstractButton::AbstractButton(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, uint16_t y, uint16_t width, uint16_t height)
    : Component(LCD, Touch, x, y, width, height)
{
    clickable = true;
}

AbstractButton::AbstractButton(lcd::UTFT *LCD, URTouch *Touch, HorizontalAlignment horizontalAlignment, VerticalAlignment verticalAlignment, uint16_t width, uint16_t height)
    : Component(LCD, Touch, horizontalAlignment, verticalAlignment, width, height)
{
    clickable = true;
}

AbstractButton::AbstractButton(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, VerticalAlignment verticalAlignment, uint16_t width, uint16_t height)
    : Component(LCD, Touch, x, verticalAlignment, width, height)
{
    clickable = true;
}

AbstractButton::AbstractButton(lcd::UTFT *LCD, URTouch *Touch, HorizontalAlignment horizontalAlignment, uint16_t y, uint16_t width, uint16_t height)
    : Component(LCD, Touch, horizontalAlignment, y, width, height)
{
    clickable = true;
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