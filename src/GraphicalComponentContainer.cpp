#include "GraphicalComponentContainer.hpp"

GraphicalComponentContainer::GraphicalComponentContainer()
    : GraphicalComponent(nullptr, 0, 0, 0, 0)
{
    graphics = new LinkedPointerList<GraphicalComponent>;
}

GraphicalComponentContainer::~GraphicalComponentContainer()
{
}

void GraphicalComponentContainer::draw()
{
    // Serial.println("\\_ graphical holder _/");
    if (valid || !visible)
    {
        // Serial.println("# && #");
        return;
    }

    for (int i = 0; i < graphics->size(); i++)
        graphics->get(i)->draw();

    valid = true;
}

void GraphicalComponentContainer::clear()
{
    for (int i = 0; i < graphics->size(); i++)
        graphics->get(i)->clear();
}

void GraphicalComponentContainer::add(GraphicalComponent *graphic)
{
    graphics->add(graphic);
    graphic->setParent(this);
}

void GraphicalComponentContainer::remove(int index)
{
    graphics->remove(index);
}

GraphicalComponent *GraphicalComponentContainer::get(int index)
{
    return graphics->get(index);
}

void GraphicalComponentContainer::setForeground(word foreground)
{
    for (int i = 0; i < graphics->size(); i++)
        graphics->get(i)->setForeground(foreground);
}

void GraphicalComponentContainer::setDisableForeground(word disableForeground)
{
    for (int i = 0; i < graphics->size(); i++)
        graphics->get(i)->setDisableForeground(disableBackground);
}