#include "Container.hpp"

Container::Container(lcd::UTFT *LCD, uint16_t x, uint16_t y, uint16_t width, uint16_t height)
    : Component(LCD, x, y, width, height)
{
    components = new LinkedPointerList<Component>;
}

Container::Container(lcd::UTFT *LCD, HorizontalAlignment horizontalAlignment, VerticalAlignment verticalAlignment, uint16_t width, uint16_t height)
    : Component(LCD, horizontalAlignment, verticalAlignment, width, height)
{
    components = new LinkedPointerList<Component>;
}

Container::Container(lcd::UTFT *LCD, uint16_t x, VerticalAlignment verticalAlignment, uint16_t width, uint16_t height)
    : Component(LCD, x, verticalAlignment, width, height)
{
    components = new LinkedPointerList<Component>;
}

Container::Container(lcd::UTFT *LCD, HorizontalAlignment horizontalAlignment, uint16_t y, uint16_t width, uint16_t height)
    : Component(LCD, horizontalAlignment, y, width, height)
{
    components = new LinkedPointerList<Component>;
}

Container::~Container()
{
    removeAll();
}

void Container::clear()
{
    for (int i = 0; i < components->size(); i++)
        components->get(i)->clear();
    invalidate();
}

int Container::getComponentsCount()
{
    return components->size();
}

Component *Container::getComponent(uint16_t index)
{
    return components->get(index);
}

void Container::add(Component *component)
{
    if (components->add(component))
        component->setParent(this);
}

void Container::add(Component *component, uint16_t index)
{
    if (components->add(index, component))
        component->setParent(this);
}

void Container::remove(uint16_t index)
{
    if (components->get(index) != nullptr)
    {
        components->get(index)->setParent(nullptr);
        components->remove(index);
    }
}

void Container::remove(Component *component)
{
    for (int i = 0; i < components->size(); i++)
    {
        if (component == components->get(i))
        {
            components->get(i)->setParent(nullptr);
            components->remove(i);
            return;
        }
    }
}

void Container::removeAll()
{
    for (int i = 0; i < components->size(); i++)
    {
        components->get(i)->setParent(nullptr);
        components->get(i)->updateLayout();
    }

    components->clear();
}

void Container::draw()
{
    for (int i = 0; i < components->size(); i++)
    {
        if (components->get(i) != nullptr)
            components->get(i)->draw();
    }

    /* int centerX = getX() + (getWidth() / 2);
    int centerY = getY() + (getHeight() / 2);

    LCD->setColor(VGA_GREEN);
    LCD->drawVLine(centerX, centerY - 5, 10);

    LCD->setColor(VGA_RED);
    LCD->drawHLine(centerX - 5, centerY, 10); */

    valid = true;
}

Component *Container::onClick(uint16_t x, uint16_t y)
{
    for (int i = 0; i < components->size(); i++)
    {
        Component *clickedUpon = components->get(i)->onClick(x, y);
        if (clickedUpon)
            return clickedUpon;
    }

    return Component::onClick(x, y);
}

void Container::updateLayout()
{
    Component::updateLayout();
    for (int i = 0; i < components->size(); i++)
        components->get(i)->updateLayout();
}