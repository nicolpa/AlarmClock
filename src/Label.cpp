#include "Label.hpp"
#include "Container.hpp"

Label::Label(lcd::UTFT* LCD, uint16_t x, uint16_t y, String text, uint8_t* font, word color, uint32_t backcolor)
    : Component(LCD, x, y, 0, 0, color, backcolor), text(text)
{
    this->font = font;
    LCD->setFont(font);
    this->width = LCD->getFontXsize() * String(text).length();
	this->height = LCD->getFontYsize();
}

Label::~Label() {}

void Label::draw()
{
    LCD->setFont(font);
    LCD->setColor(foreground);
    LCD->setBackColor(background);
    String toDisplay  = text;

    // Crop the text to fit the label width
    if(LCD->getFontXsize() * String(text).length() > getWidth())
    {
        int offset = getWidth() / LCD->getFontXsize();
        toDisplay = text.substring(0, offset);
    }

    LCD->print(toDisplay, getX(), getY());
}