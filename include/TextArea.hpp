#pragma once
#include "Component.hpp"
#include "VirtualKeyboard.hpp"

class TextArea : public Component
{

public:
    TextArea(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, uint16_t y, uint16_t width, uint8_t *font = SmallFont, word foreground = VGA_WHITE, uint32_t background = VGA_BLACK, word disableForeground = VGA_GRAY, uint32_t disableBackground = VGA_GRAY);
    TextArea(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, uint16_t y, uint16_t width, String text, uint8_t *font = SmallFont, word foreground = VGA_WHITE, uint32_t background = VGA_BLACK, word disableForeground = VGA_GRAY, uint32_t disableBackground = VGA_GRAY);
    
    
    ~TextArea();

    void draw() override;
    bool onClick(uint16_t x, uint16_t y) override;

    String getText();

    void update(char character);

private:
    VirtualKeyboard *keyboard = nullptr;
    String text = "";
    int maxLength;
};