#include "Component.hpp"
#include "Container.hpp"


Component::Component(lcd::UTFT *LCD, uint16_t x, uint16_t y, uint16_t width, uint16_t height,
              word foreground, uint32_t background, word disableForeground, uint32_t disableBackground)
    : LCD(LCD), x(x), y(y), width(width), height(height), foreground(foreground),background(background), disableForeground(disableForeground), disableBackground(disableBackground) 
{
    
}

Component::Component(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, uint16_t y, uint16_t width, uint16_t height,
              word foreground, uint32_t background, word disableForeground, uint32_t disableBackground) 
    : LCD(LCD), Touch(Touch), x(x), y(y), width(width), height(height), foreground(foreground),background(background), disableForeground(disableForeground), disableBackground(disableBackground) 
{
    
}

Component::~Component() 
{
    LCD->setColor(VGA_BLACK);
    LCD->fillRect(getX(), getY(), getX() + width, getY() + height);
    if(parent != nullptr)
        delete parent;
}

void Component::clear() 
{
    LCD->setColor(VGA_BLACK);
    LCD->fillRect(getX(), getY(), getX() + width, getY() + height);
}

bool Component::onClick(uint16_t x, uint16_t y) 
{
    if(enable && contains(x, y))
    {
        focus = true;
        if(Touch != nullptr)
        {
            Touch->saveStartPressTime();
            while(Touch->dataAvailable());
            if(Touch->getElapsedTime() < LONG_PRESS)
                if(normalPressAction != nullptr)
                    normalPressAction();
            else
                if(longPressAction != nullptr)
                    longPressAction();
            Touch->resetStartPressTime();
        }

        return true;
    }
    else
    {
        focus = false;
        return false;
    }
}

bool Component::isShowing() 
{
    return visible;
}

bool Component::isClickable() 
{
    return clickable;
}

bool Component::isEnable() 
{
    return enable;
}

Container* Component::getParent() 
{
    return parent;
}

uint16_t Component::getX(bool useScreenSpace) 
{
    return (parent != nullptr && useScreenSpace) ? x + parent->getX() : x;
}

uint16_t Component::getY(bool useScreenSpace) 
{
    return (parent != nullptr && useScreenSpace) ? y + parent->getY() : y;
}

uint16_t Component::getWidth() 
{
    return width;
}

uint16_t Component::getHeight() 
{
    return height;
}

uint8_t* Component::getFont() 
{
    return font;
}

void Component::setParent(Container *parent) 
{
    this->parent = parent;
}

void Component::setVisible(bool visible) 
{
    this->visible = visible;
}

void Component::setClickable(bool clickable) 
{
    this->clickable = clickable;
}

void Component::setEnable(bool enable) 
{
    this->enable = enable;
}

void Component::setX(uint16_t x) 
{
    this->x = x;
}

void Component::setY(uint16_t y) 
{
    this->y = y;
}

void Component::setWidth(uint16_t width) 
{
    this->width = width;
}

void Component::setHeight(uint16_t height) 
{
    this->height = height;
}

void Component::setLocation(uint16_t x, uint16_t y) 
{
    this->x = x;
    this->y = y;
}

void Component::setSize(uint16_t width, uint16_t height) 
{
    this->width = width;
    this->height = height;
}

void Component::setBounds(uint16_t x, uint16_t y, uint16_t width, uint16_t height) 
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

void Component::setFont(uint8_t *font) 
{
    this->font = font;
}

void Component::setNormalPressAction(void (*normalPressAction)(void)) 
{
    this->normalPressAction = normalPressAction;
}

void Component::setLongPressAction(void (*longPressAction)(void)) 
{
    this->longPressAction = longPressAction;
}

void Component::removeNormalPressAction() 
{
    normalPressAction = nullptr;
}

void Component::removeLongPressAction() 
{
    longPressAction = nullptr;
}

bool Component::contains(uint16_t x, uint16_t y, uint16_t hitboxOffset = 0) 
{
    return x >= (getX() - hitboxOffset) && y >= (getY() - hitboxOffset) && x < (getX() + width + hitboxOffset) && y < (getY() + height + hitboxOffset);
}
