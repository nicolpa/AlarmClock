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
    invalidate();
}

Component *Component::onClick(uint16_t x, uint16_t y)
{
    if (enable && clickable && contains(x, y))
    {
        if(!focus)
        {
            if (Touch != nullptr)
                Touch->saveStartPressTime();

            focus = true;
        }

        return this;
    }

    return nullptr;
}

void Component::onRelease(uint16_t x, uint16_t y) 
{
    if(contains(x, y) && Touch != nullptr)
    {
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
    }

    focus = false;
    Touch->resetStartPressTime();
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

Component *Component::getParent()
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

bool Component::isTransparent()
{
    return transparent;
}

void Component::setParent(Container *parent)
{
    this->parent = parent;
    updateLayout();
}

void Component::setVisible(bool visible)
{
    this->visible = visible;
    clear();
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
    horizontalAlignment = HorizontalAlignment::None;
    updateLayout();
}

void Component::setY(uint16_t y)
{
    this->y = y;
    verticalAlignment = VerticalAlignment::None;
    updateLayout();
}

void Component::setWidth(uint16_t width)
{
    this->width = width;

    updateLayout();
}

void Component::setHeight(uint16_t height)
{
    this->height = height;

    updateLayout();
}

void Component::setLocation(uint16_t x, uint16_t y)
{
    this->x = x;
    this->y = y;

    horizontalAlignment = HorizontalAlignment::None;
    verticalAlignment = VerticalAlignment::None;

    updateLayout();
}

void Component::setSize(uint16_t width, uint16_t height)
{
    this->width = width;
    this->height = height;

    updateLayout();
}

void Component::setBounds(uint16_t x, uint16_t y, uint16_t width, uint16_t height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;

    horizontalAlignment = HorizontalAlignment::None;
    verticalAlignment = VerticalAlignment::None;

    updateLayout();
}

void Component::setFont(uint8_t *font)
{
    this->font = font;

    updateLayout();
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
        this->x = (parent == nullptr) ? LCD->getDisplayXSize() - width - 1 : parent->getWidth() - width - 1;
        break;
    case HorizontalAlignment::Center:
        this->x = (parent == nullptr) ? (LCD->getDisplayXSize() - width) / 2 : ((parent->getWidth() - width) / 2);
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
        this->y = (parent == nullptr) ? LCD->getDisplayYSize() - height : parent->getHeight() - height - 1;
        break;
    case VerticalAlignment::Center:
        this->y = (parent == nullptr) ? (LCD->getDisplayYSize() - height) / 2 : ((parent->getHeight() - height) / 2);
        break;
    case VerticalAlignment::None:
    default:
        break;
    }

    if (getX() >= LCD->getDisplayXSize())
        this->x = LCD->getDisplayXSize() - 1;
    if (getY() >= LCD->getDisplayYSize())
        this->y = LCD->getDisplayYSize() - 1;
    if (getX() + width >= LCD->getDisplayXSize())
        this->width = LCD->getDisplayXSize() - getX() - 1;
    if (getY() + height >= LCD->getDisplayYSize())
        this->height = LCD->getDisplayYSize() - getY() - 1;

    invalidate();
}

void Component::setForeground(lcd::Color foreground)
{
    this->foreground = foreground;
    invalidate();
}

void Component::setBackground(lcd::Color background)
{
    this->background = background;
    invalidate();
}

void Component::setDisableForeground(lcd::Color disableForeground)
{
    this->disableForeground = disableForeground;
    invalidate();
}

void Component::setDisableBackground(lcd::Color disableForeground)
{
    this->disableBackground = disableBackground;
    invalidate();
}

void Component::setTransparent(bool transparent)
{
    this->transparent = transparent;
    invalidate();
}

void Component::validate()
{
    valid = true;
}

void Component::invalidate()
{
    valid = false;

    if (parent != nullptr)
        parent->invalidate();
}

lcd::Color Component::getForeground() 
{
    if(foreground == lcd::TRANSPARENT)
        return (parent == nullptr) ? lcd::BLACK : parent->getForeground();
    return foreground;
}

lcd::Color Component::getBackground() 
{
    if(background == lcd::TRANSPARENT)
        return (parent == nullptr) ? lcd::BLACK : parent->getBackground();
    return background;
}

lcd::Color Component::getDisableForeground() 
{
    if(disableForeground == lcd::TRANSPARENT)
        return (parent == nullptr) ? lcd::BLACK : parent->getDisableForeground();
    return disableForeground;
}

lcd::Color Component::getDisableBackground() 
{
    if(disableBackground == lcd::TRANSPARENT)
        return (parent == nullptr) ? lcd::BLACK : parent->getDisableBackground();
    return disableBackground;
}

lcd::Color Component::getCurrentForeground() 
{
    return (enable) ? getForeground() : getDisableForeground();
}

lcd::Color Component::getCurrentBackground() 
{
    return (enable) ? getBackground() : getDisableBackground();
}

bool Component::contains(uint16_t x, uint16_t y, uint16_t hitboxOffset = 0)
{
    return x >= (getX() - hitboxOffset) && y >= (getY() - hitboxOffset) && x < (getX() + width + hitboxOffset) && y < (getY() + height + hitboxOffset);
}