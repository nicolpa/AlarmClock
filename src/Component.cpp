#include "Component.hpp"
#include "Container.hpp"

Component::Component(lcd::UTFT *LCD, uint16_t x, uint16_t y, uint16_t width, uint16_t height)
    : LCD(LCD), x(x), y(y), width(width), height(height)
{
    updateLayout();
}

Component::Component(lcd::UTFT *LCD, HorizontalAlignment horizontalAlignment, VerticalAlignment verticalAlignment, uint16_t width, uint16_t height)
    : LCD(LCD), horizontalAlignment(horizontalAlignment), verticalAlignment(verticalAlignment), width(width), height(height)
{
    updateLayout();
}

Component::Component(lcd::UTFT *LCD, uint16_t x, VerticalAlignment verticalAlignment, uint16_t width, uint16_t height)
    : LCD(LCD), x(x), verticalAlignment(verticalAlignment), width(width), height(height)
{
    updateLayout();
}

Component::Component(lcd::UTFT *LCD, HorizontalAlignment horizontalAlignment, uint16_t y, uint16_t width, uint16_t height)
    : LCD(LCD), horizontalAlignment(horizontalAlignment), y(y), width(width), height(height)
{
    updateLayout();
}

Component::Component(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, uint16_t y, uint16_t width, uint16_t height)
    : LCD(LCD), Touch(Touch), x(x), y(y), width(width), height(height)
{
    updateLayout();
}

Component::Component(lcd::UTFT *LCD, URTouch *Touch, HorizontalAlignment horizontalAlignment, VerticalAlignment verticalAlignment, uint16_t width, uint16_t height)
    : LCD(LCD), Touch(Touch), horizontalAlignment(horizontalAlignment), verticalAlignment(verticalAlignment), width(width), height(height)
{
    updateLayout();
}

Component::Component(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, VerticalAlignment verticalAlignment, uint16_t width, uint16_t height)
    : LCD(LCD), Touch(Touch), x(x), verticalAlignment(verticalAlignment), width(width), height(height)
{
    updateLayout();
}

Component::Component(lcd::UTFT *LCD, URTouch *Touch, HorizontalAlignment horizontalAlignment, uint16_t y, uint16_t width, uint16_t height)
    : LCD(LCD), Touch(Touch), horizontalAlignment(horizontalAlignment), y(y), width(width), height(height)
{
    updateLayout();
}

Component::~Component()
{
    clear();
}

void Component::clear()
{
    LCD->setColor(VGA_BLACK);
    LCD->fillRect(getX(), getY(), getX() + width, getY() + height);
    valid = false;
}

bool Component::onClick(uint16_t x, uint16_t y)
{
    if (enable && contains(x, y))
    {
        focus = true;
        if (Touch != nullptr)
        {
            Touch->saveStartPressTime();
            while (Touch->dataAvailable())
                ;
            if (Touch->getElapsedTime() < LONG_PRESS)
                if (normalPressAction != nullptr)
                    normalPressAction();
                else if (longPressAction != nullptr)
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

Container *Component::getParent()
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

uint8_t *Component::getFont()
{
    return font;
}

void Component::setParent(Container *parent)
{
    this->parent = parent;
    valid = false;
}

void Component::setVisible(bool visible)
{
    this->visible = visible;
    clear();
    valid = false;
}

void Component::setClickable(bool clickable)
{
    this->clickable = clickable;
}

void Component::setEnable(bool enable)
{
    this->enable = enable;

    valid = false;
}

void Component::setX(uint16_t x)
{
    this->x = x;

    valid = false;
}

void Component::setY(uint16_t y)
{
    this->y = y;

    valid = false;
}

void Component::setWidth(uint16_t width)
{
    this->width = width;

    valid = false;
}

void Component::setHeight(uint16_t height)
{
    this->height = height;

    valid = false;
}

void Component::setLocation(uint16_t x, uint16_t y)
{
    this->x = x;
    this->y = y;

    valid = false;
}

void Component::setSize(uint16_t width, uint16_t height)
{
    this->width = width;
    this->height = height;

    valid = false;
}

void Component::setBounds(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;

    valid = false;
}

void Component::setFont(uint8_t *font)
{
    this->font = font;

    valid = false;
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

void Component::setHorizontalAlignment(HorizontalAlignment horizontalAlignment)
{
    this->horizontalAlignment = horizontalAlignment;

    updateLayout();
}

void Component::setVerticalAlignment(VerticalAlignment verticalAlignment)
{
    this->verticalAlignment = verticalAlignment;

    updateLayout();
}

HorizontalAlignment Component::getHorizontalAlignment()
{
    return horizontalAlignment;
}

VerticalAlignment Component::getVerticalAlignment()
{
    return verticalAlignment;
}

void Component::updateLayout()
{
    switch (horizontalAlignment)
    {
    case HorizontalAlignment::Left:
        this->x = 0;
        break;
    case HorizontalAlignment::Right:
        this->x = (parent == nullptr) ? LCD->getDisplayXSize() - width - 1: parent->getX() + parent->getWidth() - width;
        break;
    case HorizontalAlignment::Center:
        this->x = (parent == nullptr) ? (LCD->getDisplayXSize() - width) / 2 : parent->getX() + ((parent->getWidth() - width) / 2);
        break;
    case HorizontalAlignment::None:
    default:
        break;
    }

    switch (verticalAlignment)
    {
    case VerticalAlignment::Up:
        this->y = 0;
        break;
    case VerticalAlignment::Down:
        this->y = (parent == nullptr) ? LCD->getDisplayYSize() - height : parent->getY() + parent->getHeight() - height;
        break;
    case VerticalAlignment::Center:
        this->y = (parent == nullptr) ? (LCD->getDisplayYSize() - height) / 2 : parent->getY() + ((parent->getHeight() - height) / 2);
        break;
    case VerticalAlignment::None:
    default:
        break;
    }

    if(getX() >= LCD->getDisplayXSize())
        this->x = LCD->getDisplayXSize() - 1;
    if(getY() >= LCD->getDisplayYSize())
        this->y = LCD->getDisplayYSize() - 1;
    if(getX() + width >= LCD->getDisplayXSize())
        this->width = LCD->getDisplayXSize() - getX() - 1;
    if(getY() + height >= LCD->getDisplayYSize())
        this->height = LCD->getDisplayYSize() - getY() - 1;

    valid = false;
}

void Component::setForeground(word foreground) 
{
    this->foreground = foreground;
    valid = false;
}

void Component::setBackground(word background) 
{
    this->background = background;
    valid = false;
}

void Component::setDisableForeground(word disableForeground) 
{
    this->disableForeground = disableForeground;
    valid = false;
}

void Component::setDisableBackground(word disableForeground) 
{
    this->disableBackground = disableBackground;
    valid = false;
}

void Component::validate() 
{
    valid = true;
}

void Component::invalidate() 
{
    valid = false;
}

bool Component::contains(uint16_t x, uint16_t y, uint16_t hitboxOffset = 0)
{
    return x >= (getX() - hitboxOffset) && y >= (getY() - hitboxOffset) && x < (getX() + width + hitboxOffset) && y < (getY() + height + hitboxOffset);
}