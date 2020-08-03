#include "Button.hpp"

Button::Button(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, uint16_t y, uint16_t w, uint16_t h, word pressedColor, word color, uint32_t backcolor)
    : AbstractButton(LCD, Touch, x, y, w, h, color, backcolor), pressedColor(pressedColor)
{
    clickable = true;
}

Button::~Button()
{
}

void Button::setBorderless(bool borderless)
{
    this->borderless = borderless;
}

bool Button::getBorderless()
{
    return borderless;
}

void Button::draw()
{
    if (!enable)
        LCD->setColor(VGA_GRAY);
    if (!borderless)
    {
        LCD->setColor((pressed) ? pressedColor : foreground);
        LCD->setBackColor(background);

        LCD->drawRect(getX(), getY(), getX() + width, getY() + height);
    }

    LCD->setFont(font);

    int x = ceil(getX() + (width / 2.0f) - (text.length() * LCD->getFontXsize()) / 2.0f);
    // ((this->x + width) - (text.length() * LCD->getFontXsize())) / 2;
    int y = ceil(getY() + (height / 2.0f) - LCD->getFontYsize() / 2.0f);
    // ((this->y + height) - LCD->getFontYsize()) / 2;

    LCD->print(text, x, y);
}

bool Button::onClick(uint16_t x, uint16_t y)
{
    if (enable && contains(x, y))
    {
        Touch->saveStartPressTime();
        pressed = true;
        draw();

        while (Touch->dataAvailable());
        
        if (Touch->getElapsedTime() >= 750)
            Serial.println("Long press");
        else
            Serial.println("Normal press");

        Touch->resetStartPressTime();

        pressed = false;
        draw();

        return true;
    }

    return false;
}