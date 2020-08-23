#include "Button.hpp"

Button::Button(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, uint16_t y, uint16_t w, uint16_t h, word pressedColor, word color, uint32_t backcolor)
    : AbstractButton(LCD, Touch, x, y, w, h, color, backcolor), pressedColor(pressedColor)
{
    clickable = true;
}

Button::Button(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, uint16_t y, uint16_t w, uint16_t h, String text, uint8_t *font, word pressedColor, word color, uint32_t backcolor) 
    : AbstractButton(LCD, Touch, x, y, w, h, color, backcolor), pressedColor(pressedColor)
{
    setText(text);
    setFont(font);
}

Button::Button(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, uint16_t y, uint16_t w, uint16_t h, Shape *shape, word pressedColor, word color, uint32_t backcolor) 
    : AbstractButton(LCD, Touch, x, y, w, h, color, backcolor), pressedColor(pressedColor), shape(shape)
{
    
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
        LCD->setColor(background);
        LCD->fillRect(getX() + 1, getY() + 1, getX() + width - 1, getY() + height - 1);
     
        LCD->setColor((pressed) ? pressedColor : foreground);
        LCD->drawRect(getX(), getY(), getX() + width, getY() + height);
    }

    LCD->setFont(font);

    int x = ceil(getX() + (width / 2.0f) - (text.length() * LCD->getFontXsize()) / 2.0f);
    int y = ceil(getY() + (height / 2.0f) - LCD->getFontYsize() / 2.0f);

    if(!textHighlight)
        LCD->setColor(foreground);
    if(text != "")
        LCD->print(text, x, y);
    else if(shape != nullptr)
        shape->draw();
}

bool Button::onClick(uint16_t x, uint16_t y)
{
    if (enable && contains(x, y))
    {
        pressed = true;
        draw();

        Touch->saveStartPressTime();
        while(Touch->dataAvailable());
        if(Touch->getElapsedTime() < LONG_PRESS)
        {
            if(normalPressAction != nullptr)
                normalPressAction();
        }
        else
        {
            if(longPressAction != nullptr)
                longPressAction();
        }
        Touch->resetStartPressTime();

        pressed = false;
        draw();

        return true;
    }

    return false;
}

void Button::setShape(Shape *shape) 
{
    this->shape = shape;
}