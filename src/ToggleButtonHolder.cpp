#include "ToggleButtonHolder.hpp"

ToggleButtonHolder::ToggleButtonHolder()
    : Container(nullptr, 0, 0, 0, 0)
{
    
}

ToggleButtonHolder::~ToggleButtonHolder() 
{
    
}

bool* ToggleButtonHolder::getSelectedButtons() 
{
    bool* selected = new bool[components->size()];
    for(int i = 0; i < components->size(); i++)
        selected[i] = ((ToggleButton*)(getComponent(i)))->isSelected();

    return selected;
}
