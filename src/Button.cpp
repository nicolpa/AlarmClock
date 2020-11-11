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
        if (graphics != nullptr)
            graphics->setForeground(pressedColor);
    }
    else
    {
        LCD->setColor(foreground);
        if (graphics != nullptr)
            graphics->setForeground(foreground);
    }

    if (text != "")
    {
        LCD->setFont(font);

        int x, y;

        switch (contentVerticalAlignment)
        {
        case VerticalAlignment::Down:
            y = getY() + height - LCD->getFontYsize() - 1;
            break;
        case VerticalAlignment::Up:
            y = getY() - 1;
            break;
        case VerticalAlignment::Center:
        case VerticalAlignment::None:
        default:
            y = ceil(getY() + (height / 2.0f) - LCD->getFontYsize() / 2.0f);
            break;
        }

        switch (contentHorizontalAlignment)
        {
        case HorizontalAlignment::Left:
            x = getX() + 1;
            // Serial.println("left");
            break;
        case HorizontalAlignment::Right:
            x = getX() + width - (text.length() * LCD->getFontXsize()) - 1;
            // Serial.println("right");
            break;
        case HorizontalAlignment::Center:
        case HorizontalAlignment::None:
        default:
            // Serial.println("Center");
            x = ceil(getX() + (width / 2.0f) - (text.length() * LCD->getFontXsize()) / 2.0f);
            break;
        }

        LCD->print(text, x, y);
    }

    if (graphics != nullptr)
        graphics->draw();

    valid = true;
}

Component *Button::onClick(uint16_t x, uint16_t y)
{
    if (enable && clickable && contains(x, y))
    {
        if(!focus)
        {
            pressed = true;
            valid = false;
            draw();
            focus = true;

            Touch->saveStartPressTime();
        }


        return this;
    }

    return nullptr;
}

void Button::onRelease(uint16_t x, uint16_t y)
{
    Component::onRelease(x, y);
    pressed = false;
    valid = false;
    draw();
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

void Button::setContentVerticalAlignment(VerticalAlignment contentVerticalAlignment)
{
    this->contentVerticalAlignment = contentVerticalAlignment;
    if(graphics != nullptr)
        graphics->setVerticalAlignment(contentVerticalAlignment);
}

void Button::setContentHorizontalAligment(HorizontalAlignment contentHorizontalAlignment)
{
    this->contentHorizontalAlignment = contentHorizontalAlignment;
    if(graphics != nullptr)
        graphics->setHorizontalAlignment(contentHorizontalAlignment);
}