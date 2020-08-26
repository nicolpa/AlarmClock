#pragma once
#include "Component.hpp"
#include "VirtualKeyboard.hpp"

class TextArea : public Component
{

public:
    TextArea(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, uint16_t y, uint16_t width, uint8_t *font = SmallFont);
    TextArea(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, uint16_t y, uint16_t width, String text, uint8_t *font = SmallFont);
    
    
    ~TextArea();

    void draw() override;
    bool onClick(uint16_t x, uint16_t y) override;

    String getText();

    void update(char character);

private:
    VirtualKeyboard *keyboard = nullptr;
    String text = "";
    uint16_t maxLength;
};