#include "TextArea.hpp"

TextArea::~TextArea() {

}
TextArea::TextArea(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, uint16_t y, uint16_t width, uint8_t *font) 
    : Component(LCD, x, y, width, 0)
{
    this->Touch = Touch;
    this->font = font;
    LCD->setFont(font);
    maxLength = (width - 10) / LCD->getFontXsize();
    height = LCD->getFontYsize() + 10;
    keyboard = new VirtualKeyboard(LCD, Touch);
    keyboard->subscribeComponent(this);
}

TextArea::TextArea(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, uint16_t y, uint16_t width, String text, uint8_t *font)
    : Component(LCD, x, y, width, 0), text(text)
{
    this->Touch = Touch;
    this->font = font;
    LCD->setFont(font);
    maxLength = width / LCD->getFontXsize();
    height = LCD->getFontYsize() + 10;
    keyboard = new VirtualKeyboard(LCD, Touch);
    keyboard->subscribeComponent(this);
}

void TextArea::draw() 
{
    LCD->setColor(VGA_BLACK);
    LCD->fillRect(getX() + 1, getY() + 1, getX() + width - 1, getY() + height - 1);
    LCD->setColor(foreground);
    LCD->drawRect(getX(), getY(), getX() + width, getY() + height);

    LCD->setFont(font);
    LCD->print(text, getX() + 5, getY() + 5);
}

bool TextArea::onClick(uint16_t x, uint16_t y) 
{
    while(Touch->dataAvailable());
    if(contains(x, y))
    {
        if(!focus)
            keyboard->draw();
        else
            keyboard->clear();

        focus = (focus) ? false : true;

        return true;
    }

    if(focus)
    {
        if(keyboard->onClick(x, y))
            return true;
        else
            keyboard->clear();

        focus = false;
    }

    return false;
}

String TextArea::getText() 
{
    return text;
}

void TextArea::update(char character) 
{
    LCD->setFont(font);
    
    if(character == '\0')
    {
        text.remove(text.length() - 1);
        int x = getX() + text.length() * LCD->getFontXsize() + 5;
        LCD->setColor(VGA_BLACK);
        LCD->fillRect(x, getY() + 5, x + LCD->getFontXsize(), getY() + 5 + LCD->getFontYsize());
    }
    else if(character == '\n')
    {
        focus = false;
        keyboard->clear();
    }
    else
    {
        if(text.length() <= maxLength)
        {
            LCD->setColor(VGA_WHITE);
            text += character;
            LCD->print(text, getX() + 5, getY() + 5);
        }
    }
}
