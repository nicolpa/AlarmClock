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
    if (valid || !visible)
        return;
    
    for (int i = 0; i < graphics->size(); i++)
        graphics->get(i)->draw();

    valid = true;
}

void GraphicalComponentContainer::clear()
{
    for (int i = 0; i < graphics->size(); i++)
        graphics->get(i)->clear();
    
    invalidate();
}

void GraphicalComponentContainer::add(GraphicalComponent *graphic)
{
    graphic->setParent(this);
    graphics->add(graphic);
}

void GraphicalComponentContainer::remove(int index)
{
    graphics->remove(index);
}

GraphicalComponent *GraphicalComponentContainer::get(int index)
{
    return graphics->get(index);
}

void GraphicalComponentContainer::setForeground(lcd::Color foreground)
{
    for (int i = 0; i < graphics->size(); i++)
        graphics->get(i)->setForeground(foreground);
}

void GraphicalComponentContainer::setDisableForeground(lcd::Color disableForeground)
{
    for (int i = 0; i < graphics->size(); i++)
        graphics->get(i)->setDisableForeground(disableBackground);
}