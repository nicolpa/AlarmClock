#include "GraphicalComponent.hpp"

GraphicalComponent::GraphicalComponent(lcd::UTFT *LCD, uint16_t x, uint16_t y, uint16_t width, uint16_t height, bool fill)
    : Component(LCD, x, y, width, height), fill(fill)
{
}

GraphicalComponent::~GraphicalComponent()
{
}

void GraphicalComponent::setFill(bool fill)
{
    this->fill = fill;
}

bool GraphicalComponent::getFill()
{
    return fill;
}