#pragma once

#include "Component.hpp"

class Label : public Component
{

public:
    Label(lcd::UTFT* LCD, uint16_t x, uint16_t y, String text, uint8_t* font, word color = VGA_WHITE, uint32_t backcolor = VGA_BLACK);
    ~Label();

    void draw() override;

    /**
     * Set the text of the label
     * @param text The new text
     */
    void setText(String text);

    /**
     * Get the tetx of the label
     * @return The current text
     */
    String getText();
    
private:
    /**
     * Indicates the alignement of the text within the label
     */ 
    int alignment;

    /**
     * The text displayed in the label
     */
    String text = "";
};