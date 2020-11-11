#include "ToggleButtonHolder.hpp"

ToggleButtonHolder::ToggleButtonHolder(lcd::UTFT *LCD, uint16_t x, uint16_t y, uint16_t width, uint16_t height, lcd::Color borderColor)
    : Panel(LCD, x, y, width, height, borderColor)
{
}

ToggleButtonHolder::ToggleButtonHolder(lcd::UTFT *LCD, HorizontalAlignment horizontalAlignment, VerticalAlignment verticalAlignment, uint16_t width, uint16_t height, lcd::Color borderColor)
    : Panel(LCD, horizontalAlignment, verticalAlignment, width, height, borderColor)
{
}

ToggleButtonHolder::ToggleButtonHolder(lcd::UTFT *LCD, uint16_t x, VerticalAlignment verticalAlignment, uint16_t width, uint16_t height, lcd::Color borderColor)
    : Panel(LCD, x, verticalAlignment, width, height, borderColor)
{
}

ToggleButtonHolder::ToggleButtonHolder(lcd::UTFT *LCD, HorizontalAlignment horizontalAlignment, uint16_t y, uint16_t width, uint16_t height, lcd::Color borderColor)
    : Panel(LCD, horizontalAlignment, y, width, height, borderColor)
{
}

ToggleButtonHolder::~ToggleButtonHolder()
{
}

bool *ToggleButtonHolder::getSelectedButtons()
{
    bool *selected = new bool[components->size()];
    for (int i = 0; i < components->size(); i++)
        selected[i] = ((ToggleButton *)(getComponent(i)))->isSelected();

    return selected;
}