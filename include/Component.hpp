#pragma once

#include "UTFT.h"
#include "URTouch.h"

#define LONG_PRESS_TIME 750 //in millisecond

extern uint16_t SmallFont[], BigFont[], SevenSegNumFontPlus[];

class Container;

class Component
{

public:
    Component(lcd::UTFT *LCD, uint16_t x, uint16_t y, uint16_t width, uint16_t height,
              word foreground = VGA_WHITE, uint32_t background = VGA_BLACK, word disableForeground = VGA_GRAY, uint32_t disableBackground = VGA_GRAY);
    Component(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, uint16_t y, uint16_t width, uint16_t height,
              word foreground = VGA_WHITE, uint32_t background = VGA_BLACK, word disableForeground = VGA_GRAY, uint32_t disableBackground = VGA_GRAY);
    
    virtual ~Component();

    /**
     * Draw the component
     */
    virtual void draw() = 0;

    /**
     * Return true if the component is clicked
     * @param x The x position of the click in the screen coordinates
     * @param y The y position of the click in the screen coordinates
     * @return Whether or not the component is clicked
     */
    virtual bool onClick(uint16_t x, uint16_t y);

    /**
     * Test whether or not this component can be shown on the screen
     * This will be true if and only if this component is visible and its parent components are all visible
     * @return true if the component is visible
     */
    bool isShowing();

    /**
     * Return true if the component is clickable
     * @return Whether or not the component can be clicked upon
     */
    bool isClickable();

    /**
     * Return true if the component can interact with the user
     * @return true if the component is enable
     */
    bool isEnable();

    /**
     * Return the parent of this component
     * @return The parent of this container
     */
    Container *getParent();

    /**
     * Get the x coordinate of the upper left corner
     * @param useScreenSpace Set to true to get the x value in the absolue, false otherwise
     * @return The current x coordinate
     */
    uint16_t getX(bool useScreenSpace = true);

    /**
     * Get the y coordinate of the upper left corner
     * * @param useScreenSpace Set to true to get the y value in the absolue, false otherwise
     * @return The current y coordinate
     */
    uint16_t getY(bool useScreenSpace = true);

    /**
     * Get the width of the component
     * @return The current width
     */
    uint16_t getWidth();

    /**
     * Get the height of the component
     * @return The current height
     */
    uint16_t getHeight();

    /**
     * Return the font in use for this component
     * @return The font for this component
     */
    uint16_t *getFont();

    /**
     * Set the parent of the component
     * @param parent The new parent of the component
     */
    void setParent(Container *parent);

    /**
     * Set the component visibility
     * @param visible The visibility
     */
    void setVisible(bool visible);

    /**
     * Set the component to be clicked uppon
     * @param clickable Whether or not the component can be clicked
     */
    void setClickable(bool clickable);

    /**
     * Enable or disable this component
     * @param enable true to enable this component
     */
    void setEnable(bool enable);

    /**
     * Set the x coordinate of the component
     * @param x The new x coordinate
     */
    void setX(uint16_t x);

    /**
     * Set the y coordinate of the component
     * @param y The new y coordinate
     */
    void setY(uint16_t y);

    /**
     * Set the width to the specified value
     * @param width The new width of the component
     */
    void setWidth(uint16_t width);

    /**
     * Set the height to the specified value
     * @param height The new height of the component
     */
    void setHeight(uint16_t height);

    /**
     * Move the component to the specified location relative to the parent's coordinates
     * The coordinates are the upper left corner of this component
     * @param x The new x coordinate of this component
     * @param y The new y coordinate of this component
     */
    void setLocation(uint16_t x, uint16_t y);

    /**
     * Set the size of this component to the specefied width and height
     * @param width The new width of this component
     * @param height The new height of this component
     */
    void setSize(uint16_t width, uint16_t height);

    /**
     * Set the bounding rectangle for this component to the specified values
     * These coordinates are relative to the parent
     * @param x The x coordinate of the upper left of the rectangle
     * @param y The y coordinate of the upper left of the rectangle
     * @param width The width of the rectangle
     * @param height The height of the rectangle
     */
    void setBounds(uint16_t x, uint16_t y, uint16_t width, uint16_t height);

    /**
     * Set the font for this component
     * @param font The new font for this component
     */
    void setFont(uint16_t *font);

protected:
    lcd::UTFT *LCD;
    URTouch *Touch = nullptr;

    Container *parent = nullptr;
    
    /**
     * True is the object is visible (although it is only showing if all ancestors are likewise visible)
     */
    bool visible = true;

    /**
     *  True if the object is enabled, meaning it can interact with the user.
     */
    bool enable = true;

    /**
     * True if the object can be clicked
     */
    bool clickable = false;

    /**
     * The x position of the component in the parent's coordinate system
     */
    uint16_t x;

    /**
     * The y position of the component in the parent's coordinate system
     */
    uint16_t y;

    /**
     * The component width
     */
    uint16_t width;

    /**
     * The component height
     */
    uint16_t height;

    /**
     * The foreground color of the component
     */
    word foreground;

    /**
     * The backgroundColor of the component
     */
    uint32_t background;

    /**
     * The foreground color of the component when disabled
     */
    word disableForeground;

    /**
     * The backgroundColor of the component when disabled
     */
    uint32_t disableBackground;

    /**
     * The default font used in the component
     * This may be null
     */
    uint16_t *font = nullptr;


    /**
     * Test whether or not the specified point is contained within this component.
     * @param x The x coordinate of the point to test in screen coordinates
     * @param y The y coordinate of the poinr to test in screen coordinates
     * @return true if the point is within this component
     */
    bool contains(uint16_t x, uint16_t y);
};