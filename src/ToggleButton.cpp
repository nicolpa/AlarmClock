#include "ToggleButton.hpp"

ToggleButton::ToggleButton(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, uint16_t y, String label, uint8_t *font)
    : AbstractButton(LCD, Touch, x, y, 0, 0)
{
    clickable = true;

    LCD->setFont(font);
    width = 20 + (LCD->getFontXsize() * String(label).length());
    height = (LCD->getFontYsize() < 15) ? 15 : LCD->getFontYsize();

    this->font = font;
    text = label;

    updateLayout();
}

ToggleButton::ToggleButton(lcd::UTFT *LCD, URTouch *Touch, HorizontalAlignment horizontalAlignment, VerticalAlignment verticalAlignment, String label, uint8_t *font)
    : AbstractButton(LCD, Touch, horizontalAlignment, verticalAlignment, 0, 0)
{
    clickable = true;

    LCD->setFont(font);
    width = 20 + (LCD->getFontXsize() * String(label).length());
    height = (LCD->getFontYsize() < 15) ? 15 : LCD->getFontYsize();

    this->font = font;
    text = label;

    updateLayout();
}

ToggleButton::ToggleButton(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, VerticalAlignment verticalAlignment, String label, uint8_t *font)
    : AbstractButton(LCD, Touch, x, verticalAlignment, 0, 0)
{
    clickable = true;

    LCD->setFont(font);
    width = 20 + (LCD->getFontXsize() * String(label).length());
    height = (LCD->getFontYsize() < 15) ? 15 : LCD->getFontYsize();

    this->font = font;
    text = label;

    updateLayout();
}

ToggleButton::ToggleButton(lcd::UTFT *LCD, URTouch *Touch, HorizontalAlignment horizontalAlignment, uint16_t y, String label, uint8_t *font)
    : AbstractButton(LCD, Touch, horizontalAlignment, y, 0, 0)
{
    clickable = true;

    LCD->setFont(font);
    width = 20 + (LCD->getFontXsize() * String(label).length());
    height = (LCD->getFontYsize() < 15) ? 15 : LCD->getFontYsize();

    this->font = font;
    text = label;

    updateLayout();
}

ToggleButton::~ToggleButton() {}

Component *ToggleButton::onClick(uint16_t x, uint16_t y)
{
    if (contains(x, y))
    {
        while (Touch->dataAvailable())
            ;
        toggle();
        update();
        return this;
    }

    return nullptr;
}

bool ToggleButton::isSelected()
{
    return selected;
}

void ToggleButton::setChecked(bool selected)
{
    this->selected = selected;
}

void ToggleButton::toggle()
{
    selected = (selected) ? false : true;
}