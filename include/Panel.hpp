#pragma once

#include "Container.hpp"

class Panel : public Container
{

public:
    Panel(lcd::UTFT* LCD, uint16_t x, uint16_t y, uint16_t width, uint16_t height, word borderColor = VGA_WHITE);
    Panel(lcd::UTFT* LCD, HorizontalAlignment horizontalAlignment, VerticalAlignment verticalAlignment, uint16_t width, uint16_t height, word borderColor = VGA_WHITE);
    Panel(lcd::UTFT* LCD, uint16_t x, VerticalAlignment verticalAlignment, uint16_t width, uint16_t height, word borderColor = VGA_WHITE);
    Panel(lcd::UTFT* LCD, HorizontalAlignment horizontalAlignment, uint16_t y, uint16_t width, uint16_t height, word borderColor = VGA_WHITE);
    ~Panel();

    void draw() override;

    /**
     * Set whether or not the borders are shown
     * @param top The top border
     * @param bottom The bottom border
     * @param left The left border
     * @param right The right border
     */
    void setBorder(bool top, bool bottom, bool left, bool right);

    /**
     * Set whether or not the borders are shown
     * @param borders True to show all borders
     */
    void setBorder(bool borders);

private:
    word borderColor;

    bool borderTop      = true;
    bool borderBottom   = true;
    bool borderLeft     = true;
    bool borderRight    = true;
};