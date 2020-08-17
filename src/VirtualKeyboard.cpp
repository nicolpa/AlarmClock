#include "VirtualKeyboard.hpp"

VirtualKeyboard::VirtualKeyboard(lcd::UTFT *LCD, URTouch *Touch, String text)
    : Component(LCD, Touch, 0, 0, LCD->getDisplayXSize(), LCD->getDisplayYSize()), text(text)
{

    
    shapeEnter = new Shape(LCD, segEnter, 5);
    shapeCapsUnlock = new Shape(LCD, segCapsUnlock, 7);
    shapeCapsTempLock = new Shape(LCD, segCapsTempLock, 8);
    shapeCapsHardLock = new Shape(LCD, segCapsHardLock, 8);

    for (int i = 0; i < 10; i++)
        buttons[i] = new Button(LCD, Touch, 10 + 30 * i, 110, 25, 25, String(keysMin[i]), BigFont);
    for (int i = 10; i < 20; i++)
        buttons[i] = new Button(LCD, Touch, 10 + 30 * (i - 10), 140, 25, 25, String(keysMin[i]), BigFont);
    for (int i = 20; i < 27; i++)
        buttons[i] = new Button(LCD, Touch, 55 + 30 * (i - 20), 170, 25, 25, String(keysMin[i]), BigFont);

    buttons[27] = new Button(LCD, Touch, 40, 200, 25, 25, String(keysMin[27]), BigFont);
    buttons[28] = new Button(LCD, Touch, 250, 200, 25, 25, String(keysMin[28]), BigFont);

    buttons[29] = new Button(LCD, Touch, 70, 200, 175, 25, " ", SmallFont); //space
    buttons[30] = new Button(LCD, Touch, 10, 170, 40, 25, shapeCapsUnlock);                  //CapsLock
    buttons[31] = new Button(LCD, Touch, 265, 170, 40, 25);                 //Backspace
    buttons[32] = new Button(LCD, Touch, 10, 200, 25, 25, "123", SmallFont);
    buttons[33] = new Button(LCD, Touch, 280, 200, 25, 25, shapeEnter); //Enter
}

VirtualKeyboard::~VirtualKeyboard()
{
}

void VirtualKeyboard::draw()
{
    for (int i = 0; i < 34; i++)
        buttons[i]->draw();

    LCD->setFont(BigFont);
    LCD->setColor(VGA_WHITE);
    LCD->setBackColor(VGA_TRANSPARENT);
    LCD->print("<", 270, 175);
    LCD->print("_", 280, 174);
    LCD->print("_", 280, 162);
    LCD->print("|", 285, 175);
}

bool VirtualKeyboard::onClick(uint16_t x, uint16_t y)
{
    for (int i = 0; i < 34; i++)
    {
        if (buttons[i]->onClick(x, y))
        {
            if (i < 30)
            {
                text += buttons[i]->getText();
                if (CapsLock == TEMP_LOCK && keyboardPage == MAIN)
                {
                    CapsLock = UNLOCK;
                    for (int j = 0; j < 26; j++)
                    {
                        buttons[j]->setText(String(keysMin[j]));
                        buttons[j]->draw();
                    }
                    buttons[30]->draw();
                }
                LCD->setFont(SmallFont);
                LCD->setColor(VGA_WHITE);
                LCD->print(text, 10, 10);
            }
            else if (i == 30 && keyboardPage == MAIN)
            {
                switch (CapsLock)
                {
                case UNLOCK:
                    CapsLock = TEMP_LOCK;
                    for (int j = 0; j < 26; j++)
                    {
                        buttons[j]->setText(String(keysMaj[j]));
                        buttons[j]->draw();
                    }
                    buttons[30]->setShape(shapeCapsTempLock);
                    break;
                case TEMP_LOCK:
                    CapsLock = HARD_LOCK;
                    buttons[30]->setShape(shapeCapsHardLock);
                    break;
                case HARD_LOCK:
                default:
                    CapsLock = UNLOCK;
                    for (int j = 0; j < 26; j++)
                    {
                        buttons[j]->setText(String(keysMin[j]));
                        buttons[j]->draw();
                    }
                    buttons[30]->setShape(shapeCapsUnlock);
                    break;
                }
                buttons[30]->draw();
            }
            else if (i == 31)
                text.remove(text.length() - 1);
            else if (i == 32)
            {
                switch (keyboardPage)
                {
                case MAIN:
                    keyboardPage = SPE1;
                    for (int j = 0; j < 29; j++)
                        buttons[j]->setText(String(keysSpe1[j]));
                    buttons[32]->setText("abc");
                    draw();
                    break;
                case SPE1:
                    keyboardPage = MAIN;
                    for (int j = 0; j < 29; j++)
                        buttons[j]->setText(String((CapsLock == UNLOCK) ? keysMin[j] : keysMaj[j]));
                    buttons[32]->setText("123");
                    draw();
                    break;
                default:
                    break;
                }
            }
            else
            {
                Serial.println(text);
            }

            return true;
        }
    }
    return false;
}

String VirtualKeyboard::getText()
{
    return text;
}