#include "GraphicalComponentContainer.hpp"

GraphicalComponentContainer::GraphicalComponentContainer()
    : GraphicalComponent(nullptr, 0, 0, 0, 0)
{
    graphics = new LinkedPointerList<GraphicalComponent>;
}

GraphicalComponentContainer::~GraphicalComponentContainer()
{
}

LinkedPointerList<GraphicalComponent> *GraphicalComponentContainer::getGraphics() 
{
    return graphics;
}

void GraphicalComponentContainer::draw() 
{
    for(int i = 0; i < graphics->size(); i++)
        graphics->get(i)->draw();
}

void GraphicalComponentContainer::setForeground(word foreground) 
{
    for(int i = 0; i < graphics->size(); i++)
        graphics->get(i)->setForeground(foreground);
}

void GraphicalComponentContainer::setDisableForeground(word disableForeground) 
{
    for(int i = 0; i < graphics->size(); i++)
        graphics->get(i)->setDisableForeground(disableBackground);
}