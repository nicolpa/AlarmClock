#pragma once

#include "Component.hpp"
#include "Panel.hpp"

#define HIT_BOX_OFFSET 5

enum class Orientation
{
    VERTICAL,
    HORIZONTAL
};

class Slider : public Component
{
private:
    /* data */
public:
    Slider(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, uint16_t y, uint16_t length, Orientation orientation = Orientation::HORIZONTAL);
    ~Slider();

    void draw() override;

    bool onClick(uint16_t x, uint16_t y) override;

    /**
     * Return the minimum value of the slider
     * @return The minimum value
     */
    int getMinimum();

    /**
     * Return the maximum value of the slider
     * @return The maximum value
     */
    int getMaximum();

    /**
     * Return the current value of the slider
     * @return The current value
     */
    int getValue();

    /**
     */
    bool getShowTicks();

    /**
     * Get the orientation of the slider
     * @return The orientation
     */
    Orientation getOrientation();

    /**
     * Return whether the ticks' values are shown
     * @return True if the ticks' values are shown
     */
    bool getShowTicksValues();

    /**
     * Set the minimum value of the slider
     * @param minimum The minimum value
     */
    void setMinimum(int minimum);

    /**
     * Set the maximum value of the slider
     * @param maximum The maximum value
     */
    void setMaximum(int maximum);

    /**
     * Set the value of the slider
     * @param value The new value of the slider
     */
    void setValue(int value);

    /**
     * Set the distance between ticks
     * @param spacing The amount of units between each tick mark
     */
    void setTickSpacing(uint16_t spacing);

    /**
     * Make the tick mark visible or invisible
     * @param visible True to make the tick mark visible
     */
    void setShowTicks(bool visible);

    /**
     * Make the slider thumb snap or not to the closest tick mark
     * @param snap True to make the thumb snap
     */
    void setSnapToTicks(bool snap);

    /**
     * The the orientation of the slider
     * @param orientation The new orientation of the slider
     */
    void setOrientation(Orientation orientation);

    /**
     * Increase the slider value by the specified amount
     * @param amount The amount to add to the slider's value
     */
    void increaseValueBy(int amount);

private:
    word fillColor;

    uint16_t length;

    /**
     * The orientation of the slider
     */
    Orientation orientation = Orientation::HORIZONTAL;

    /**
     * The minimum value of the slider
     */
    int minimum = 0;

    /**
     * The maximum value of the slider
     */
    int maximum = 100;

    /**
     * The current value of the slider
     */
    int value = 0;

    /**
     * Whether the slider show the ticks
     */
    bool showTicks = false;

    /**
     * Whether the slider show the ticks' values
     */
    bool showTicksValues = false;

    /**
     * Whether the slider snaps its values to ticks
     */
    bool snapToTicks = false;

    /**
     * The space between ticks
     */
    uint16_t tickSpacing = 1;

    /**
     * The number of ticks for this slider
     */
    int nTicks;

    /**
     * The array containing all the ticks' values
     */
    int *ticksValues = nullptr;

    /**
     * Return the closest tick value for the specified value
     * @param value The new value
     * @return The closest tick value
     */
    int getClosest(int value);

    /**
     * The thickness of the slider to be drawn
     */
    int thickness = 3;
};