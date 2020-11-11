#pragma once

#include "Button.hpp"
#include "Label.hpp"
#include "Panel.hpp"
#include "GraphicalComponentContainer.hpp"
#include "Shapes.hpp"

#define UNLOCK 0
#define TEMP_LOCK 1
#define HARD_LOCK 2

#define MAIN 3
#define SPE1 4
#define SPE2 5

class TextArea;

class VirtualKeyboard : public Component
{

public:
    VirtualKeyboard(lcd::UTFT *LCD, URTouch *Touch);
    ~VirtualKeyboard();

    void draw() override;
    Component *onClick(uint16_t x, uint16_t y) override;


    void subscribeComponent(TextArea *component);
    void unsubscribeComponent();

    void notify(char character);

private:
    TextArea *observer = nullptr;

    Panel *currentLayout;
    Panel *SpecialLayout;
    Panel *TextLayout;


    Button *buttons[34];

    char keysMin[29] = { 'a', 'z', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',
                         'q', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm',
                         'w', 'x', 'c', 'v', 'b', 'n', '\'', ',', '.' };

    char keysMaj[29] = { 'A', 'Z', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
                         'Q', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', 'M',
                         'W', 'X', 'C', 'V', 'B', 'N', '\'', ',', '.' };

    char keysSpe1[29] = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
                          '@', '#', '&', '_', '-', '(', ')', '=', '%', '\"',
                          '*', '\'', ':', '/', '!', '?', '+', ',', '.'};

    char keysSpe2[14] = { '$', '~', '[', ']', '{', '}', '<', '>', '^', 
                          '`', ';', '\\', '|', 'x'};

    
    uint8_t CapsLock = UNLOCK;

    uint8_t keyboardPage = MAIN;
    
    GraphicalComponentContainer *shapeCapsUnlock;
    GraphicalComponentContainer *shapeCapsTempLock;
    GraphicalComponentContainer *shapeCapsHardLock;
    GraphicalComponentContainer *shapeEnter;

};