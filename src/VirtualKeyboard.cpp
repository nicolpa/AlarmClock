#include "VirtualKeyboard.hpp"
#include "TextArea.hpp"

VirtualKeyboard::VirtualKeyboard(lcd::UTFT *LCD, URTouch *Touch)
    : Component(LCD, Touch, 0, 110, LCD->getDisplayXSize() - 1, LCD->getDisplayYSize() - 111)
{
    shapeEnter = new GraphicalComponentContainer();
    shapeEnter->add(new Line(LCD, 5, 12, 13, 7));
    shapeEnter->add(new Line(LCD, 5, 12, 13, 17));
    shapeEnter->add(new Line(LCD, 13, 7, 13, 17));
    shapeEnter->add(new Line(LCD, 13, 12, 18, 12));
    shapeEnter->add(new Line(LCD, 18, 12, 18, 7));

    shapeCapsUnlock = new GraphicalComponentContainer();
    shapeCapsUnlock->add(new Line(LCD, 12, 13, 20, 5));
    shapeCapsUnlock->add(new Line(LCD, 28, 13, 20, 5));
    shapeCapsUnlock->add(new Line(LCD, 12, 13, 17, 13));
    shapeCapsUnlock->add(new Line(LCD, 18, 13, 23, 13));
    shapeCapsUnlock->add(new Line(LCD, 17, 13, 17, 20));
    shapeCapsUnlock->add(new Line(LCD, 23, 13, 23, 20));
    shapeCapsUnlock->add(new Line(LCD, 17, 20, 23, 20));

    shapeCapsTempLock = new GraphicalComponentContainer();
    shapeCapsTempLock->add(new Line(LCD, 12, 13, 20, 5));
    shapeCapsTempLock->add(new Line(LCD, 28, 13, 20, 5));
    shapeCapsTempLock->add(new Line(LCD, 12, 13, 17, 13));
    shapeCapsTempLock->add(new Line(LCD, 18, 13, 23, 13));
    shapeCapsTempLock->add(new Line(LCD, 17, 13, 17, 15));
    shapeCapsTempLock->add(new Line(LCD, 23, 13, 23, 15));
    shapeCapsTempLock->add(new Line(LCD, 17, 15, 23, 15));
    shapeCapsTempLock->add(new Rectangle(LCD, 17, 17, 23, 20));

    shapeCapsHardLock = new GraphicalComponentContainer();
    shapeCapsHardLock->add(new Line(LCD, 12, 13, 20, 5));
    shapeCapsHardLock->add(new Line(LCD, 28, 13, 20, 5));
    shapeCapsHardLock->add(new Line(LCD, 12, 13, 17, 13));
    shapeCapsHardLock->add(new Line(LCD, 18, 13, 23, 13));
    shapeCapsHardLock->add(new Line(LCD, 17, 13, 17, 15));
    shapeCapsHardLock->add(new Line(LCD, 23, 13, 23, 15));
    shapeCapsHardLock->add(new Line(LCD, 17, 15, 23, 15));
    shapeCapsHardLock->add(new Rectangle(LCD, 17, 17, 23, 20, true));

    for (int i = 0; i < 10; i++)
        buttons[i] = new Button(LCD, Touch, 10 + 30 * i, 110, 25, 25, String(keysMin[i]), BigFont);
    for (int i = 10; i < 20; i++)
        buttons[i] = new Button(LCD, Touch, 10 + 30 * (i - 10), 140, 25, 25, String(keysMin[i]), BigFont);
    for (int i = 20; i < 27; i++)
        buttons[i] = new Button(LCD, Touch, 55 + 30 * (i - 20), 170, 25, 25, String(keysMin[i]), BigFont);

    buttons[27] = new Button(LCD, Touch, 40, 200, 25, 25, String(keysMin[27]), BigFont);
    buttons[28] = new Button(LCD, Touch, 250, 200, 25, 25, String(keysMin[28]), BigFont);

    buttons[29] = new Button(LCD, Touch, 70, 200, 175, 25, " ", SmallFont); //space
    buttons[30] = new Button(LCD, Touch, 10, 170, 40, 25, shapeCapsUnlock); //CapsLock
    buttons[31] = new Button(LCD, Touch, 265, 170, 40, 25);                 //Backspace
    buttons[32] = new Button(LCD, Touch, 10, 200, 25, 25, "123", SmallFont);
    buttons[33] = new Button(LCD, Touch, 280, 200, 25, 25, shapeEnter); //Enter
}

VirtualKeyboard::~VirtualKeyboard()
{
}

void VirtualKeyboard::draw()
{
    if (valid || !visible)
        return;

    for (int i = 0; i < 34; i++)
        buttons[i]->draw();

    LCD->setFont(BigFont);
    LCD->setColor(VGA_WHITE);
    LCD->setBackColor(VGA_TRANSPARENT);
    LCD->print("<", 270, 175);
    LCD->print("_", 280, 174);
    LCD->print("_", 280, 162);
    LCD->print("|", 285, 175);

    valid = true;
}

bool VirtualKeyboard::onClick(uint16_t x, uint16_t y)
{
    if (Component::contains(x, y))
    {
        for (int i = 0; i < 34; i++)
        {
            if (buttons[i]->onClick(x, y))
            {
                if (i < 30)
                {
                    notify(buttons[i]->getText().c_str()[0]);
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
                        buttons[30]->setGraphics(shapeCapsTempLock);
                        break;
                    case TEMP_LOCK:
                        CapsLock = HARD_LOCK;
                        buttons[30]->setGraphics(shapeCapsHardLock);
                        break;
                    case HARD_LOCK:
                    default:
                        CapsLock = UNLOCK;
                        for (int j = 0; j < 26; j++)
                        {
                            buttons[j]->setText(String(keysMin[j]));
                            buttons[j]->draw();
                        }
                        buttons[30]->setGraphics(shapeCapsUnlock);
                        break;
                    }
                    buttons[30]->draw();
                }
                else if (i == 31)
                {
                    notify('\0');
                }
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
                    notify('\n');
            }
        }
        return true;
    }
    return false;
}

void VirtualKeyboard::subscribeComponent(TextArea *component)
{
    observer = component;
}

void VirtualKeyboard::unsubscribeComponent()
{
    observer = nullptr;
}

void VirtualKeyboard::notify(char character)
{
    if (observer != nullptr)
        observer->update(character);
}