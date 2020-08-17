#pragma once

#include "AbstractButton.hpp"
#include "Shape.hpp"

class Button : public AbstractButton 
{

public:
    Button(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, uint16_t y, uint16_t w, uint16_t h, word pressedColor = VGA_GREEN, word color = VGA_WHITE, uint32_t backcolor = VGA_BLACK);
    Button(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, uint16_t y, uint16_t w, uint16_t h, String text, uint8_t *font, word pressedColor = VGA_GREEN, word color = VGA_WHITE, uint32_t backcolor = VGA_BLACK);
    Button(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, uint16_t y, uint16_t w, uint16_t h, Shape *shape, word pressedColor = VGA_GREEN, word color = VGA_WHITE, uint32_t backcolor = VGA_BLACK);
    ~Button();

    /**
     * Set if the button has borders
     * @param borderless Whether or not the button has borders
     */
    void setBorderless(bool borderless);

    /**
     * Return true if no border
     * @return 
     */
    bool getBorderless();

    void draw() override;

    bool onClick(uint16_t x, uint16_t y) override;

    void setShape(Shape *shape);

private:
    /**
     * The outline color used when the button is pressed
     */
    word pressedColor;

    /**
     * Whether or not the button display a border
     */
    bool borderless = false;

    /**
     * Change the text color when pressed
     */
    bool textHighlight = false;

    Shape *shape = nullptr;
};