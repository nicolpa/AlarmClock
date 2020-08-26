#pragma once

#include "AbstractButton.hpp"
#include "Shape.hpp"

class Button : public AbstractButton 
{

public:
    Button(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, uint16_t y, uint16_t width, uint16_t height);
    Button(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, uint16_t y, uint16_t width, uint16_t height, String text, uint8_t *font);
    Button(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, uint16_t y, uint16_t width, uint16_t height, Shape *shape);

    Button(lcd::UTFT *LCD, URTouch *Touch, HorizontalAlignment horizontalAlignment, VerticalAlignment verticalAlignment, uint16_t width, uint16_t height);
    Button(lcd::UTFT *LCD, URTouch *Touch, HorizontalAlignment horizontalAlignment, VerticalAlignment verticalAlignment, uint16_t width, uint16_t height, String text, uint8_t *font);
    Button(lcd::UTFT *LCD, URTouch *Touch, HorizontalAlignment horizontalAlignment, VerticalAlignment verticalAlignment, uint16_t width, uint16_t height, Shape *shape);

    Button(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, VerticalAlignment verticalAlignment, uint16_t width, uint16_t height);
    Button(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, VerticalAlignment verticalAlignment, uint16_t width, uint16_t height, String text, uint8_t *font);
    Button(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, VerticalAlignment verticalAlignment, uint16_t width, uint16_t height, Shape *shape);

    Button(lcd::UTFT *LCD, URTouch *Touch, HorizontalAlignment horizontalAlignment, uint16_t y, uint16_t width, uint16_t height);
    Button(lcd::UTFT *LCD, URTouch *Touch, HorizontalAlignment horizontalAlignment, uint16_t y, uint16_t width, uint16_t height, String text, uint8_t *font);
    Button(lcd::UTFT *LCD, URTouch *Touch, HorizontalAlignment horizontalAlignment, uint16_t y, uint16_t width, uint16_t height, Shape *shape);

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

    bool getTextHighlight();

    void draw() override;

    bool onClick(uint16_t x, uint16_t y) override;

    void setShape(Shape *shape);

    void setTextHighlight(bool textHightlight);

private:
    /**
     * The outline color used when the button is pressed
     */
    word pressedColor = VGA_GREEN;

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