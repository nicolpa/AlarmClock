#pragma once

#include "Component.hpp"

class Label : public Component
{

public:
    Label(lcd::UTFT* LCD, uint16_t x, uint16_t y, String text, uint8_t* font, word color = VGA_WHITE, uint32_t backcolor = VGA_BLACK);
    ~Label();

    void draw() override;
    
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