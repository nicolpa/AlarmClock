#include <Arduino.h>

#include "UTFT.h"
#include "URTouch.h"

#include "Component.hpp"
#include "Panel.hpp"
#include "Label.hpp"
#include "Slider.hpp"
#include "Button.hpp"
#include "RadioButton.hpp"
#include "CheckBox.hpp"

lcd::UTFT LCD(ITDB32S, 38, 39, 40, 41);
URTouch Touch(6, 5, 4, 3, 2);

Panel *pnlUpLeft, *pnlUpRight, *pnlBottomLeft, *pnlBottomRight;
Label *lblUpLeft, *lblUpRight, *lblBottomLeft, *lblBottomRight;
Slider *slrVertical, *slrHorizontal;
Button *btn;
RadioButton *roBtn;
CheckBox *chkBtn;

void setup()
{
    Serial.begin(9600);

    LCD.fade(true);
    LCD.InitLCD();
    Touch.InitTouch();
    Touch.setPrecision(PREC_MEDIUM);

    pnlUpLeft       = new Panel(&LCD, 0, 0
                                    , LCD.getDisplayXSize() / 2, LCD.getDisplayYSize() / 2);

    pnlUpRight      = new Panel(&LCD, LCD.getDisplayXSize() / 2, 0
                                    , (LCD.getDisplayXSize() / 2) - 1, LCD.getDisplayYSize() / 2);

    pnlBottomLeft   = new Panel(&LCD, 0, LCD.getDisplayYSize() / 2
                                    , LCD.getDisplayXSize() / 2, (LCD.getDisplayYSize() / 2) - 1);

    pnlBottomRight  = new Panel(&LCD, LCD.getDisplayXSize() / 2, LCD.getDisplayYSize() / 2
                                    , (LCD.getDisplayXSize() / 2) - 1, (LCD.getDisplayYSize() / 2) - 1);

    lblUpLeft = new Label(&LCD, 10, 10, "Upper left", SmallFont);
    lblUpRight = new Label(&LCD, 10, 10, "Upper right", SmallFont);
    lblBottomLeft = new Label(&LCD, 10, 10, "bottom left", SmallFont);
    lblBottomRight = new Label(&LCD, 10, 10, "bottom right", SmallFont);

    slrHorizontal = new Slider(&LCD, &Touch, pnlUpLeft->getX() + 10, pnlUpLeft->getY() + pnlUpLeft->getHeight() - 20, pnlUpLeft->getWidth() - 20);
    slrVertical = new Slider(&LCD, &Touch, 10, 10, pnlUpLeft->getHeight() - 20, Orientation::VERTICAL);

    btn = new Button(&LCD, &Touch, 10, 25, 100, 20);

    roBtn = new RadioButton(&LCD, &Touch, 10, 50, "Select me", SmallFont);

    chkBtn = new CheckBox(&LCD, &Touch, 10, 90, "Select me", SmallFont);

    btn->setFont(SmallFont);
    btn->setText("Click me");

    slrHorizontal->setMinimum(1);
    slrHorizontal->setMaximum(7);
    slrHorizontal->setShowTicks(true);

    slrVertical->setTickSpacing(1);
    slrVertical->setTickSpacing(20);
    slrVertical->setSnapToTicks(true);
    slrVertical->setShowTicks(true);

    slrHorizontal->setValue(2);
    slrVertical->setValue(59);

    pnlBottomLeft->add(btn);

    pnlUpLeft->add(lblUpLeft);
    pnlUpRight->add(lblUpRight);
    pnlBottomLeft->add(lblBottomLeft);
    pnlBottomRight->add(lblBottomRight);

    pnlUpLeft->add(slrHorizontal);
    pnlBottomRight->add(slrVertical);

    pnlUpRight->add(roBtn);

    pnlUpRight->add(chkBtn);

    pnlUpRight->draw();
    pnlBottomLeft->draw();
    pnlBottomRight->draw();
    pnlUpLeft->draw();
}

void loop()
{
    if(Touch.dataAvailable())
    {
        Touch.read();
        int x = Touch.getX();
        int y = Touch.getY();
        pnlUpLeft->onClick(x, y);
        pnlUpRight->onClick(x, y);
        pnlBottomLeft->onClick(x, y);
        pnlBottomRight->onClick(x, y);
    }
}