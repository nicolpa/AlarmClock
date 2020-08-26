#include "Label.hpp"
#include "Container.hpp"

Label::Label(lcd::UTFT* LCD, uint16_t x, uint16_t y, String text, uint8_t* font)
    : Component(LCD, x, y, 0, 0), text(text)
{
    this->font = font;
    LCD->setFont(font);
    this->width = LCD->getFontXsize() * String(text).length();
	this->height = LCD->getFontYsize();
}

Label::Label(lcd::UTFT *LCD, HorizontalAlignment horizontalAlignment, VerticalAlignment verticalAlignment, String text, uint8_t* font) 
    : Component(LCD, horizontalAlignment, verticalAlignment, 0, 0), text(text)
{
    this->font = font;
    LCD->setFont(font);
    this->width = LCD->getFontXsize() * String(text).length();
	this->height = LCD->getFontYsize();
    updateLayout();
}

Label::Label(lcd::UTFT *LCD, uint16_t x, VerticalAlignment verticalAlignment, String text, uint8_t* font) 
    : Component(LCD, x, verticalAlignment, 0, 0), text(text)
{
    this->font = font;
    LCD->setFont(font);
    this->width = LCD->getFontXsize() * String(text).length();
	this->height = LCD->getFontYsize();
    updateLayout();
}

Label::Label(lcd::UTFT *LCD, HorizontalAlignment horizontalAlignment, uint16_t y, String text, uint8_t* font) 
    : Component(LCD, horizontalAlignment, y, 0, 0), text(text)
{
    this->font = font;
    LCD->setFont(font);
    this->width = LCD->getFontXsize() * String(text).length();
	this->height = LCD->getFontYsize();
    updateLayout();
}

Label::~Label() {}

void Label::draw()
{
    if(valid)
        return;

    LCD->setFont(font);
    LCD->setColor(foreground);
    LCD->setBackColor(textBackground);
    String toDisplay  = text;

    // Crop the text to fit the label width
    if(LCD->getFontXsize() * String(text).length() > getWidth())
    {
        int offset = getWidth() / LCD->getFontXsize();
        toDisplay = text.substring(0, offset);
    }

    LCD->print(toDisplay, getX(), getY());
    valid = true;
}

void Label::setText(String text) 
{
    this->text = text;
    invalidate();
}

String Label::getText() 
{
    return text;
}

void Label::setTextBackground(uint32_t textBackground) 
{
    this->textBackground = textBackground;
    valid = false;
}