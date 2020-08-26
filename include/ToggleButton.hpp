#pragma once

#include "AbstractButton.hpp"

class ToggleButton : public AbstractButton
{

public:
    ToggleButton(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, uint16_t y, String label, uint8_t *font);
    ToggleButton(lcd::UTFT *LCD, URTouch *Touch, HorizontalAlignment horizontalAlignment, VerticalAlignment verticalAlignment, String label, uint8_t *font);
    ToggleButton(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, VerticalAlignment verticalAlignment, String label, uint8_t *font);
    ToggleButton(lcd::UTFT *LCD, URTouch *Touch, HorizontalAlignment horizontalAlignment, uint16_t y, String label, uint8_t *font);
    virtual ~ToggleButton();

    bool onClick(uint16_t x, uint16_t y) override;

    /**
     * Return whether or not the button is selected
     * @return True if checked
     */
    bool isSelected();

    /**
     * Select or not the button
     * @param selected True for the button to be selected
     */
    void setChecked(bool selected);

    /**
     * Select or not the button based on its current value
     */
    void toggle();

protected:
    /**
     * Whether or not the button is selected
     */
    bool selected = false;
    
    /**
     * Update the component's graphics
     */
    virtual void update() = 0;
};