#include "RadioButtonHolder.hpp"

RadioButtonHolder::RadioButtonHolder()
    : ToggleButtonHolder()
{
}

RadioButtonHolder::~RadioButtonHolder()
{
}

bool RadioButtonHolder::onClick(uint16_t x, uint16_t y)
{
    for(int i = 0; i < components->size(); i++)
    {
        if(getComponent(i)->onClick(x, y))
        {
            for(int j = 0; j < components->size(); j++)
            {
                if(i != j)
                {
                    if(((RadioButton*)(getComponent(j)))->isSelected())
                    {
                        ((RadioButton*)(getComponent(j)))->setChecked(false);
                        ((RadioButton*)(getComponent(j)))->draw();
                        return true;
                    }
                }
            }
            return true;
        }
    }

    return false;
}