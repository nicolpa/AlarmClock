#include "Container.hpp"

Container::Container(uint16_t x, uint16_t y, uint16_t width, uint16_t height) 
    : Component(nullptr, x, y, width, height)
{
    
}

Container::~Container()
{
    removeAll();
}

void Container::clear() 
{
    Component::clear();
    for(int i = 0; i < nComponents; i++)
        components[i]->invalidate();
}

int Container::getComponentsCount() 
{
    return nComponents;
}

Component* Container::getComponent(uint16_t index) 
{
    if(index < 0 || index > nComponents)
        return nullptr;
    return components[index];
}

void Container::getComponents(Component** components) 
{
    components = this->components;
}

void Container::add(Component* component) 
{
    if(nComponents < N_MAX_COMPONENTS)
    {
        components[nComponents++] = component;
        component->setParent(this);
        component->updateLayout();
    }
}

void Container::add(Component* component, uint16_t index) 
{
    if(nComponents == N_MAX_COMPONENTS)
        return;
    
    component->setParent(this);
    component->updateLayout();

    if(nComponents == index)
        components[index] = component;
    else if(nComponents < index)
        components[nComponents] = component;
    else
    {
        for(uint16_t i = nComponents; i >= index; i--)
        {
            components[i] = components[i - 1];
        }
        components[index] = component;
    }
    nComponents++;
}

void Container::remove(uint16_t index) 
{
    if(index < 0 || index >= nComponents)
        return;
    
    components[index]->setParent(nullptr);
    components[index]->updateLayout();

    if(index != nComponents - 1)
        for(uint16_t i = index; i < nComponents; i++)
            components[i] = components[i + 1];

    nComponents--;
}

void Container::remove(Component* component) 
{
    for(uint16_t i = 0; i < nComponents; i++)
    {
        if(components[i] == component)
        {
            remove(i);
            return;
        }
    }
}

void Container::removeAll() 
{
    for(uint16_t i = 0; i < nComponents; i++)
        delete components[i];
}

void Container::draw() 
{
    for(uint16_t i = 0; i < nComponents; i++)
        components[i]->draw();
}

bool Container::onClick(uint16_t x, uint16_t y) 
{
    for (uint16_t i = 0; i < nComponents; i++)
        if (components[i]->onClick(x, y))
            return true;

    return contains(x, y);
}

void Container::validate() 
{
    for(int i = 0; i < nComponents; i++)
        components[i]->validate();
}

void Container::invalidate() 
{
    for(int i = 0; i < nComponents; i++)
        components[i]->invalidate();
}