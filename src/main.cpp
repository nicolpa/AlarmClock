#include <Arduino.h>

#include "UTFT.h"
#include "URTouch.h"
#include "DS1307.h"

#include "Component.hpp"
#include "Panel.hpp"
#include "Label.hpp"
#include "Slider.hpp"
#include "Button.hpp"
#include "RadioButton.hpp"
#include "CheckBox.hpp"
#include "ToggleButtonHolder.hpp"
#include "RadioButtonHolder.hpp"
#include "Frame.hpp"
#include "VirtualKeyboard.hpp"
#include "Shape.hpp"
#include "TextArea.hpp"
#include "Alarm.hpp"

lcd::UTFT LCD(ITDB32S, 38, 39, 40, 41);
URTouch Touch(6, 5, 4, 3, 2);

DS1307  rtc(SDA, SCL);
Time time;

Frame *currentFrame;

Frame *frmMain;
Label *lblClock, *lblDate, *lblDow;
Label *lblTemp;
Button *btnSettings;

Frame *frmSettings;
Label *lblSettingsHeader;

Alarm *alarm1;

#define LM35 A5


float getTemp()
{
    return analogRead(LM35) / (10 / 1.0742);
}

void switchFrame()
{
    currentFrame->clear();
    if(currentFrame == frmMain)
        currentFrame = frmSettings;
    else
        currentFrame = frmMain;
}

void setup()
{
    Serial.begin(9600);

    rtc.begin();
    rtc.halt(false);

    time = rtc.getTime();

    LCD.fade(true);
    LCD.InitLCD();
    Touch.InitTouch();
    Touch.setPrecision(PREC_MEDIUM);

    analogReference(INTERNAL1V1);
    pinMode(LM35, INPUT);
    pinMode(SPEAKER, OUTPUT);

    lblClock = new Label(&LCD, CENTER, (LCD.getDisplayYSize() - 50) / 2, rtc.getTimeStr(), SevenSegNumFontPlus);
    lblDow = new Label(&LCD, LEFT, 2, rtc.getDOWStr(), SmallFont);
    lblDate = new Label(&LCD, LEFT, 15, rtc.getDateStr(), SmallFont);
    lblTemp = new Label(&LCD, RIGHT, 2, String(getTemp()) + " C", SmallFont);
    btnSettings = new Button(&LCD, &Touch, LCD.getDisplayXSize() - 16, LCD.getDisplayYSize() - 16, 15, 15);
    btnSettings->setFont(SmallFont);
    btnSettings->setText("s");

    frmMain = new Frame(&LCD, VGA_TRANSPARENT);
    frmMain->add(lblClock);
    frmMain->add(lblDow);
    frmMain->add(lblDate);
    frmMain->add(lblTemp);
    frmMain->add(btnSettings);

    lblSettingsHeader = new Label(&LCD, 2, 2, "Settings", SmallFont);
    frmSettings = new Frame(&LCD, VGA_TRANSPARENT);
    frmSettings->add(lblSettingsHeader);
    frmSettings->add(btnSettings);

    btnSettings->setNormalPressAction(&switchFrame);

    currentFrame = frmMain;

    alarm1 = new Alarm(12, 4);
}

void loop()
{
    if(time != rtc.getTime())
    {
        lblClock->setText(rtc.getTimeStr());
        lblDow->setText(rtc.getDOWStr());
        lblDate->setText(rtc.getDateStr());
        lblTemp->setText(String(getTemp()) + " C");
        currentFrame->draw();
        LCD.drawCircle(307,4,2);
        time = rtc.getTime();
        if(alarm1->check(time))
            alarm1->ring();
    }

    if(Touch.dataAvailable())
    {
        Touch.read();
        int x = Touch.getX();
        int y = Touch.getY();
        frmMain->onClick(x, y);
    }
}