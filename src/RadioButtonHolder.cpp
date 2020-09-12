#include "RadioButtonHolder.hpp"

RadioButtonHolder::RadioButtonHolder(lcd::UTFT *LCD, uint16_t x, uint16_t y, uint16_t width, uint16_t height, word borderColor)
    : ToggleButtonHolder(LCD, x, y, width, height, borderColor)
{
}

RadioButtonHolder::RadioButtonHolder(lcd::UTFT *LCD, HorizontalAlignment horizontalAlignment, VerticalAlignment verticalAlignment, uint16_t width, uint16_t height, word borderColor)
    : ToggleButtonHolder(LCD, horizontalAlignment, verticalAlignment, width, height, borderColor)
{
}

RadioButtonHolder::RadioButtonHolder(lcd::UTFT *LCD, uint16_t x, VerticalAlignment verticalAlignment, uint16_t width, uint16_t height, word borderColor)
    : ToggleButtonHolder(LCD, x, verticalAlignment, width, height, borderColor)
{
}

RadioButtonHolder::RadioButtonHolder(lcd::UTFT *LCD, HorizontalAlignment horizontalAlignment, uint16_t y, uint16_t width, uint16_t height, word borderColor)
    : ToggleButtonHolder(LCD, horizontalAlignment, y, width, height, borderColor)
{
}

RadioButtonHolder::~RadioButtonHolder()
{
}

bool RadioButtonHolder::onClick(uint16_t x, uint16_t y)
{
    for (int i = 0; i < components->size(); i++)
    {
        if (getComponent(i)->onClick(x, y))
        {
            for (int j = 0; j < components->size(); j++)
            {
                if (i != j)
                {
                    if (((RadioButton *)(getComponent(j)))->isSelected())
                    {
                        ((RadioButton *)(getComponent(j)))->setChecked(false);
                        ((RadioButton *)(getComponent(j)))->draw();
                        return true;
                    }
                }
            }
            return true;
        }
    }

    return false;
}