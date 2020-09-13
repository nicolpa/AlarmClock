#include "Button.hpp"

Button::Button(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, uint16_t y, uint16_t width, uint16_t height)
    : AbstractButton(LCD, Touch, x, y, width, height)
{
}

Button::Button(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, uint16_t y, uint16_t width, uint16_t height, String text, uint8_t *font)
    : AbstractButton(LCD, Touch, horizontalAlignment, verticalAlignment, width, height)
{
    this->text = text;
    this->font = font;
}

Button::Button(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, uint16_t y, uint16_t width, uint16_t height, GraphicalComponent *graphics)
    : AbstractButton(LCD, Touch, x, y, width, height), graphics(graphics)
{
    graphics->setParent(this);
    graphics->updateLayout();
}

Button::Button(lcd::UTFT *LCD, URTouch *Touch, HorizontalAlignment horizontalAlignment, VerticalAlignment verticalAlignment, uint16_t width, uint16_t height)
    : AbstractButton(LCD, Touch, horizontalAlignment, verticalAlignment, width, height)
{
}

Button::Button(lcd::UTFT *LCD, URTouch *Touch, HorizontalAlignment horizontalAlignment, VerticalAlignment verticalAlignment, uint16_t width, uint16_t height, String text, uint8_t *font)
    : AbstractButton(LCD, Touch, horizontalAlignment, verticalAlignment, width, height)
{
    this->text = text;
    this->font = font;
}

Button::Button(lcd::UTFT *LCD, URTouch *Touch, HorizontalAlignment horizontalAlignment, VerticalAlignment verticalAlignment, uint16_t width, uint16_t height, GraphicalComponent *graphics)
    : AbstractButton(LCD, Touch, horizontalAlignment, verticalAlignment, width, height), graphics(graphics)
{
    graphics->setParent(this);
    graphics->updateLayout();
}

Button::Button(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, VerticalAlignment verticalAlignment, uint16_t width, uint16_t height)
    : AbstractButton(LCD, Touch, x, verticalAlignment, width, height)
{
}

Button::Button(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, VerticalAlignment verticalAlignment, uint16_t width, uint16_t height, String text, uint8_t *font)
    : AbstractButton(LCD, Touch, x, verticalAlignment, width, height)
{
    this->text = text;
    this->font = font;
}

Button::Button(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, VerticalAlignment verticalAlignment, uint16_t width, uint16_t height, GraphicalComponent *graphics)
    : AbstractButton(LCD, Touch, x, verticalAlignment, width, height), graphics(graphics)
{
    graphics->setParent(this);
    graphics->updateLayout();
}

Button::Button(lcd::UTFT *LCD, URTouch *Touch, HorizontalAlignment horizontalAlignment, uint16_t y, uint16_t width, uint16_t height)
    : AbstractButton(LCD, Touch, horizontalAlignment, y, width, height)
{
}

Button::Button(lcd::UTFT *LCD, URTouch *Touch, HorizontalAlignment horizontalAlignment, uint16_t y, uint16_t width, uint16_t height, String text, uint8_t *font)
    : AbstractButton(LCD, Touch, horizontalAlignment, y, width, height)
{
    this->text = text;
    this->font = font;
}

Button::Button(lcd::UTFT *LCD, URTouch *Touch, HorizontalAlignment horizontalAlignment, uint16_t y, uint16_t width, uint16_t height, GraphicalComponent *graphics)
    : AbstractButton(LCD, Touch, horizontalAlignment, y, width, height), graphics(graphics)
{
    graphics->setParent(this);
    graphics->updateLayout();
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

bool Button::getContentHighlight() 
{
    return contentHighlight;
}

bool Button::getBorderHighlight() 
{
    return borderHighlight;
}

void Button::draw()
{
    if (valid || !visible)
        return;

    if (!enable)
        LCD->setColor(VGA_GRAY);
        
    if (!borderless)
    {
        LCD->setColor(background);
        LCD->fillRect(getX() + 1, getY() + 1, getX() + width - 1, getY() + height - 1);

        LCD->setColor((pressed && borderHighlight) ? pressedColor : foreground);
        LCD->drawRect(getX(), getY(), getX() + width, getY() + height);
    }
    else
    {
        LCD->setColor((enable) ? background : disableBackground);
        LCD->fillRect(getX(), getY(), getX() + width, getY() + height);
    }
    

    if (contentHighlight && pressed)
    {
        LCD->setColor(pressedColor);
        if(graphics != nullptr)
            graphics->setForeground(pressedColor);
    }
    else
    {
        LCD->setColor(foreground);
        if(graphics != nullptr)
            graphics->setForeground(foreground);
    }

    if (text != "")
    {
        LCD->setFont(font);

        int x = ceil(getX() + (width / 2.0f) - (text.length() * LCD->getFontXsize()) / 2.0f);
        int y = ceil(getY() + (height / 2.0f) - LCD->getFontYsize() / 2.0f);

        LCD->print(text, x, y);
    }

    if (graphics != nullptr)
        graphics->draw();

    valid = true;
}

bool Button::onClick(uint16_t x, uint16_t y)
{
    if (enable && contains(x, y))
    {
        pressed = true;
        valid = false;
        draw();

        Touch->saveStartPressTime();
        while (Touch->dataAvailable());
        if (Touch->getElapsedTime() < LONG_PRESS)
        {
            if (normalPressAction != nullptr)
                normalPressAction();
        }
        else
        {
            if (longPressAction != nullptr)
                longPressAction();
        }
        Touch->resetStartPressTime();

        pressed = false;
        valid = false;
        draw();

        return true;
    }

    return false;
}

void Button::setGraphics(GraphicalComponent *graphics)
{
    this->graphics = graphics;
    graphics->setParent(this);
}

void Button::setContentHighlight(bool contentHighlight) 
{
    this->contentHighlight = contentHighlight;
}

void Button::setBorderHighlight(bool borderHighlight) 
{
    this->borderHighlight = borderHighlight;
}