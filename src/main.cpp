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

DS1307 rtc(SDA, SCL);
Time time;

Frame *currentFrame;

Frame *frmMain;
Label *lblClock, *lblDate, *lblDow;
Label *lblTemp;
Button *btnSettings;

Frame *frmSettings;
Label *lblSettingsHeader;

Alarm *alarm1;

Panel *pnlSettingsHeader;
Panel *pnlClockSettings;
Panel *pnlDateDowSettings;
Panel *pnlAlarmsSettings;
Panel *pnlBtnSettings;

Shape *shapeBtnSettings;

Button *btnHourUp, *btnMinUp, *btnSecUp, *btnDayUp, *btnMonthUp, *btnYearUp;
Button *btnHourDown, *btnMinDown, *btnSecDown, *btnDayDown, *btnMonthDown, *btnYearDown;
Label *lblClockSettings, *lblDateSettings;

Alarm *Alarms[5];
uint8_t nAlarm = 0;

#define LM35 A5

float getTemp()
{
    return analogRead(LM35) / (10 / 1.0742);
}

void switchFrame()
{
    currentFrame->clear();
    if (currentFrame == frmMain)
        currentFrame = frmSettings;
    else
        currentFrame = frmMain;
}

void loadMainScreen()
{
    lblClock = new Label(&LCD, HorizontalAlignment::Center, VerticalAlignment::Center, rtc.getTimeStr(), SevenSegNumFontPlus);
    // lblClock->draw();
    lblDow = new Label(&LCD, HorizontalAlignment::Left, 2, rtc.getDOWStr(), SmallFont);
    lblDate = new Label(&LCD, HorizontalAlignment::Left, 15, rtc.getDateStr(), SmallFont);
    lblTemp = new Label(&LCD, HorizontalAlignment::Right, 2, String(getTemp()) + " C", SmallFont);

    btnSettings = new Button(&LCD, &Touch, HorizontalAlignment::Right, VerticalAlignment::Down, 15, 15);

    static Segment segBtnSettings[3] =
        {
            {btnSettings->getX() + 2, btnSettings->getY() + 3, btnSettings->getX() + btnSettings->getWidth() - 2, btnSettings->getY() + 4, true, true},
            {btnSettings->getX() + 2, btnSettings->getY() + 7, btnSettings->getX() + btnSettings->getWidth() - 2, btnSettings->getY() + 8, true, true},
            {btnSettings->getX() + 2, btnSettings->getY() + 11, btnSettings->getX() + btnSettings->getWidth() - 2, btnSettings->getY() + 12, true, true}
        };

    shapeBtnSettings = new Shape(&LCD, segBtnSettings, 3);

    btnSettings->setShape(shapeBtnSettings);
    btnSettings->setBorderless(true);

    frmMain = new Frame(&LCD);
    frmMain->add(lblClock);
    frmMain->add(lblDow);
    frmMain->add(lblDate);
    frmMain->add(lblTemp);
    frmMain->add(btnSettings);
    // frmMain->draw();
}

void loadSettingsScreen()
{
    lblSettingsHeader = new Label(&LCD, 2, 2, "Settings", SmallFont);

    frmSettings = new Frame(&LCD);
    frmSettings->add(btnSettings);


    pnlSettingsHeader = new Panel(&LCD, 0, 0, LCD.getDisplayXSize() - 1, 20);
    pnlSettingsHeader->setBorder(false, true, false, false);
    pnlClockSettings = new Panel(&LCD, 0, pnlSettingsHeader->getHeight() + 1, 150, LCD.getDisplayYSize() - 1 - pnlSettingsHeader->getHeight() - 16);
    pnlClockSettings->setBorder(false, false, false, true);

    lblClockSettings = new Label(&LCD, HorizontalAlignment::Center, VerticalAlignment::Center, rtc.getTimeStr(), BigFont);

    lblClockSettings = new Label(&LCD, HorizontalAlignment::Center, VerticalAlignment::Center, rtc.getTimeStr(), BigFont);
    lblDateSettings = new Label(&LCD, HorizontalAlignment::Center, VerticalAlignment::Center, rtc.getDateStr(), BigFont);
    pnlDateDowSettings->setBorder(false);
    pnlBtnSettings = new Panel(&LCD, pnlClockSettings->getWidth(), pnlDateDowSettings->getY() + pnlDateDowSettings->getHeight(), pnlDateDowSettings->getX() + pnlDateDowSettings->getWidth(), LCD.getDisplayXSize() - 1 - pnlClockSettings->getWidth());
    pnlDateDowSettings = new Panel(&LCD, pnlClockSettings->getWidth() + 1, pnlSettingsHeader->getHeight() + 1, LCD.getDisplayXSize() - 1 - pnlClockSettings->getWidth(), LCD.getDisplayYSize() - pnlSettingsHeader->getWidth() - 2 - 16);
    pnlClockSettings->add(lblClockSettings);
    // pnlBtnSettings->add(btnSettings);
    // frmSettings->add(pnlBtnSettings);
    frmSettings->add(pnlSettingsHeader);
    frmSettings->add(pnlClockSettings);
    frmSettings->add(pnlDateDowSettings);

    pnlSettingsHeader->add(lblSettingsHeader);
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

    loadMainScreen();
    // loadSettingsScreen();

    btnSettings->setNormalPressAction(&switchFrame);
    btnSettings->setTextHighlight(true);

    currentFrame = frmMain;

    // alarm1 = new Alarm(12, 4);
}

void loop()
{
    if (time != rtc.getTime())
    {
        currentFrame->draw();
        if (currentFrame == frmMain)
        {
            lblClock->setText(rtc.getTimeStr());
            lblDow->setText(rtc.getDOWStr());
            lblDate->setText(rtc.getDateStr());
            lblTemp->setText(String(getTemp()) + " C");

            LCD.drawCircle(307, 4, 2);
        }
        else
        {
            lblClockSettings->setText(rtc.getTimeStr());
        }

        time = rtc.getTime();
    }

    if (Touch.dataAvailable())
    {
        Touch.read();
        int x = Touch.getX();
        int y = Touch.getY();
        frmMain->onClick(x, y);
    }
}