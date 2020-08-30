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
    Component::clear();
    for (int i = 0; i < components->size(); i++)
        components->get(i)->invalidate();
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
    Serial.println(">> " + String(component->getX()));
    if(components->add(component))
    {
        component->setParent(this);
        component->updateLayout();
        Serial.println(String(component->getX()) + "<<");
    }
}

void Container::add(Component *component, uint16_t index)
{
    if (components->add(index, component))
    {
        component->setParent(this);
        component->updateLayout();
    }
}

void Container::remove(uint16_t index)
{
    if (components->remove(index))
    {
        components->get(index)->setParent(nullptr);
        components->get(index)->updateLayout();
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
    if(valid)
        return;
        
    for (int i = 0; i < components->size(); i++)
        components->get(i)->draw();

    // int centerX = getX() + (getWidth() / 2);
    // int centerY = getY() + (getHeight() / 2);

    // LCD->setColor(VGA_GREEN);
    // LCD->drawVLine(centerX, centerY - 5, 10);

    // LCD->setColor(VGA_RED);
    // LCD->drawHLine(centerX - 5, centerY, 10);
}

bool Container::onClick(uint16_t x, uint16_t y)
{
    for (int i = 0; i < components->size(); i++)
        if (components->get(i)->onClick(x, y))
            return true;

    return Component::onClick(x, y);
}

void Container::updateLayout() 
{
    Component::updateLayout();
    for(int i = 0; i < components->size(); i++)
        components->get(i)->updateLayout();
}