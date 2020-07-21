#include <Arduino.h>

#include "UTFT.h"
#include "URTouch.h"

#include "Component.hpp"
#include "Panel.hpp"
#include "Label.hpp"

lcd::UTFT LCD(ITDB32S, 38, 39, 40, 41);
URTouch Touch(6, 5, 4, 3, 2);

Panel *pnlUpLeft, *pnlUpRight, *pnlBottomLeft, *pnlBottomRight;
Label *lblUpLeft, *lblUpRight, *lblBottomLeft, *lblBottomRight;

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

    pnlUpLeft->add(lblUpLeft);
    pnlUpRight->add(lblUpRight);
    pnlBottomLeft->add(lblBottomLeft);
    pnlBottomRight->add(lblBottomRight);

    pnlUpLeft->draw();
    pnlUpRight->draw();
    pnlBottomLeft->draw();
    pnlBottomRight->draw();
}

void loop()
{
}