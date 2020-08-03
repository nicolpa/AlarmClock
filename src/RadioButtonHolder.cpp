#include "RadioButtonHolder.hpp"

RadioButtonHolder::RadioButtonHolder()
{
}

RadioButtonHolder::~RadioButtonHolder()
{
}

bool RadioButtonHolder::onClick(uint16_t x, uint16_t y)
{
    for(uint16_t i = 0; i < nComponents; i++)
    {
        if(getComponent(i)->onClick(x, y))
        {
            for(uint16_t j = 0; j < nComponents; j++)
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