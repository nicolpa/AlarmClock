#pragma once

#include "Component.hpp"

class AbstractButton : public Component
{

public:
    AbstractButton(lcd::UTFT* LCD, URTouch* Touch, uint16_t x, uint16_t y, uint16_t w, uint16_t h, word color = VGA_WHITE, uint32_t backcolor = VGA_BLACK);
    ~AbstractButton();

    /**
     * Sets the text of the button
     * @param text The new text of the button
     */
    void setText(String text);

    /**
     * Get the current text of the button
     * @return The text
     */
    String getText();

    /**
     * Set the state of the button
     * @param pressed True if the button is clicked upon
     */
    void setPressed(bool pressed);

    /**
     * Return the state of the button
     * @return True if pressed
     */
    bool getPressed();

protected:
    /**
     * The text displayed by the button
     */
    String text = "";

    /**
     * Whether or not the button is currently being click on
     */
    bool pressed = false;
};