#pragma once

#include "AbstractButton.hpp"
#include "GraphicalComponent.hpp"

class Button : public AbstractButton 
{

public:
    Button(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, uint16_t y, uint16_t width, uint16_t height);
    Button(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, uint16_t y, uint16_t width, uint16_t height, String text, uint8_t *font);
    Button(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, uint16_t y, uint16_t width, uint16_t height, GraphicalComponent *graphics);

    Button(lcd::UTFT *LCD, URTouch *Touch, HorizontalAlignment horizontalAlignment, VerticalAlignment verticalAlignment, uint16_t width, uint16_t height);
    Button(lcd::UTFT *LCD, URTouch *Touch, HorizontalAlignment horizontalAlignment, VerticalAlignment verticalAlignment, uint16_t width, uint16_t height, String text, uint8_t *font);
    Button(lcd::UTFT *LCD, URTouch *Touch, HorizontalAlignment horizontalAlignment, VerticalAlignment verticalAlignment, uint16_t width, uint16_t height, GraphicalComponent *graphics);

    Button(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, VerticalAlignment verticalAlignment, uint16_t width, uint16_t height);
    Button(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, VerticalAlignment verticalAlignment, uint16_t width, uint16_t height, String text, uint8_t *font);
    Button(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, VerticalAlignment verticalAlignment, uint16_t width, uint16_t height, GraphicalComponent *graphics);

    Button(lcd::UTFT *LCD, URTouch *Touch, HorizontalAlignment horizontalAlignment, uint16_t y, uint16_t width, uint16_t height);
    Button(lcd::UTFT *LCD, URTouch *Touch, HorizontalAlignment horizontalAlignment, uint16_t y, uint16_t width, uint16_t height, String text, uint8_t *font);
    Button(lcd::UTFT *LCD, URTouch *Touch, HorizontalAlignment horizontalAlignment, uint16_t y, uint16_t width, uint16_t height, GraphicalComponent *graphics);

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

    bool getContentHighlight();

    bool getBorderHighlight();

    void draw() override;

    bool onClick(uint16_t x, uint16_t y) override;

    void setGraphics(GraphicalComponent *graphics);

    void setContentHighlight(bool contentHighlight);

    void setBorderHighlight(bool borderHighlight);

private:
    /**
     * The outline color used when the button is pressed
     */
    lcd::Color pressedColor = lcd::GREEN;

    /**
     * Whether or not the button display a border
     */
    bool borderless = false;

    /**
     * Change the text color when pressed
     */
    bool contentHighlight = false;

    bool borderHighlight = true;

    GraphicalComponent *graphics = nullptr;
};