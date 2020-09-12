#pragma once

#include "UTFT.h"
#include "URTouch.h"

#define LONG_PRESS_TIME 750 //in millisecond

extern uint8_t SmallFont[], BigFont[], SevenSegNumFontPlus[];

class Container;

enum class HorizontalAlignment
{
    Left,
    Right,
    Center,
    None
};

enum class VerticalAlignment
{
    Up,
    Down,
    Center,
    None
};

class Component
{

public:
    Component(lcd::UTFT *LCD, uint16_t x, uint16_t y, uint16_t width, uint16_t height);
    Component(lcd::UTFT *LCD, HorizontalAlignment horizontalAlignment, VerticalAlignment verticalAlignment, uint16_t width, uint16_t height);
    Component(lcd::UTFT *LCD, uint16_t x, VerticalAlignment verticalAlignment, uint16_t width, uint16_t height);
    Component(lcd::UTFT *LCD, HorizontalAlignment horizontalAlignment, uint16_t y, uint16_t width, uint16_t height);

    Component(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, uint16_t y, uint16_t width, uint16_t height);
    Component(lcd::UTFT *LCD, URTouch *Touch, HorizontalAlignment horizontalAlignment, VerticalAlignment verticalAlignment, uint16_t width, uint16_t height);
    Component(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, VerticalAlignment verticalAlignment, uint16_t width, uint16_t height);
    Component(lcd::UTFT *LCD, URTouch *Touch, HorizontalAlignment horizontalAlignment, uint16_t y, uint16_t width, uint16_t height);

    virtual ~Component();

    /**
     * Draw the component
     */
    virtual void draw() = 0;

    /**
     * Clear the component from the display
     */
    virtual void clear();

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
    Component *getParent();

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
    uint8_t *getFont();

    bool isTransparent();

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
    void setFont(uint8_t *font);

    void setNormalPressAction(void (*normalPressAction)(void));

    void setLongPressAction(void (*longPressAction)(void));

    void removeNormalPressAction();

    void removeLongPressAction();

    void setHorizontalAlignment(HorizontalAlignment horizontalAlignment);

    void setVerticalAlignment(VerticalAlignment verticalAlignment);

    HorizontalAlignment getHorizontalAlignment();
    VerticalAlignment getVerticalAlignment();

    virtual void updateLayout();

    virtual void setForeground(word foreground);
    virtual void setBackground(word background);
    virtual void setDisableForeground(word disableForeground);
    virtual void setDisableBackground(word disableForeground);
    void setTransparent(bool transparent);

    virtual void validate();
    virtual void invalidate();

    void print();


protected:
    lcd::UTFT *LCD;
    URTouch *Touch = nullptr;

    Component *parent = nullptr;
    
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
    uint16_t x = 0;

    /**
     * The y position of the component in the parent's coordinate system
     */
    uint16_t y = 0;

    /**
     * The component width
     */
    uint16_t width = 0;

    /**
     * The component height
     */
    uint16_t height = 0;

    /**
     * The foreground color of the component
     */
    word foreground = VGA_WHITE;

    /**
     * The backgroundColor of the component
     */
    word background = VGA_BLACK;

    /**
     * The foreground color of the component when disabled
     */
    word disableForeground = VGA_GRAY;

    /**
     * The backgroundColor of the component when disabled
     */
    word disableBackground = VGA_BLACK;

    /**
     * The default font used in the component
     * This may be null
     */
    uint8_t *font = nullptr;

    /**
     * Whether or not the component has focus
     */
    bool focus = false;

    HorizontalAlignment horizontalAlignment = HorizontalAlignment::None;

    VerticalAlignment verticalAlignment = VerticalAlignment::None;

    /**
     * Function to execute when the component is pressed
     */
    void (*normalPressAction)(void) = nullptr;

    /**
     * Function to execute when the component is pressed for a long time
     */
    void (*longPressAction)(void) = nullptr;

    /**
     * Test whether or not the specified point is contained within this component.
     * @param x The x coordinate of the point to test in screen coordinates
     * @param y The y coordinate of the poinr to test in screen coordinates
     * @param hitboxOffset Increase the size of hitbox of the component by the specified value
     * @return true if the point is within this component
     */
    bool contains(uint16_t x, uint16_t y, uint16_t hitboxOffset = 0);

    /**
     * True if the component is valid. This is set to false when any ajustement was made to the component
     */
    bool valid = false;

    bool transparent = false;
};