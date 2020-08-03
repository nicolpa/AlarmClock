#include "ToggleButtonHolder.hpp"

ToggleButtonHolder::ToggleButtonHolder()
    : Container(0, 0, 0, 0)
{
    
}

ToggleButtonHolder::~ToggleButtonHolder() 
{
    
}

bool* ToggleButtonHolder::getSelectedButtons() 
{
    bool* selected = new bool[nComponents];
    for(uint16_t i = 0; i < nComponents; i++)
        selected[i] = ((ToggleButton*)(getComponent(i)))->isSelected();

    return selected;
}
