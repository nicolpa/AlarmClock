#include <Arduino.h>

#include "UTFT.h"
#include "URTouch.h"
#include "DS1307.h"

#include "Components.hpp"

#include "Alarm.hpp"

#define LM35 A5

lcd::UTFT LCD(ITDB32S, 38, 39, 40, 41);
URTouch Touch(6, 5, 4, 3, 2);

DS1307 rtc(SDA, SCL);
Time time;

Frame *frmMain, *frmAlarm, *frmSettings;
Frame *currentFrame;

Button *btnMenu, *btnSettings;
Label *lblClockMain, *lblClockAlarm, *lblDate, *lblDOW;
Label *lblTemp;
Panel *pnlClock;
Panel *pnlAlarms;

Button *btnAlarm, *btnTimer, *btnStopWatch;

LinkedPointerList<Alarm> alarms;

float getTemp()
{
    return analogRead(LM35) / (10 / 1.0742);
}

void switchFrame()
{
    currentFrame->clear();
    if (currentFrame == frmMain)
    {
        currentFrame = frmAlarm;
    }
    else
    {
        currentFrame = frmMain;
    }
}

void loadMainFrame()
{
    frmMain = new Frame(&LCD);
    frmMain->add(lblDOW = new Label(&LCD, HorizontalAlignment::Left, 2, rtc.getDOWStr(), SmallFont));
    frmMain->add(lblDate = new Label(&LCD, HorizontalAlignment::Left, 15, rtc.getDateStr(), SmallFont));
    frmMain->add(lblClockMain = new Label(&LCD, HorizontalAlignment::Center, VerticalAlignment::Center, rtc.getTimeStr(), SevenSegNumFontPlus));

    Panel *pnlTemp = new Panel(&LCD, HorizontalAlignment::Right, VerticalAlignment::Up, 57, 12);
    pnlTemp->setBorder(false);
    pnlTemp->add(lblTemp = new Label(&LCD, HorizontalAlignment::Left, 2, String(getTemp()), SmallFont));
    pnlTemp->add(new Circle(&LCD, 42, 4, 2));
    pnlTemp->add(new Label(&LCD, HorizontalAlignment::Right, 2, "C", SmallFont));
    frmMain->add(pnlTemp);

    frmMain->add(btnMenu);
}

void loadSettingsFrame()
{
    frmAlarm = new Frame(&LCD);

    Panel *pnlHeader = new Panel(&LCD, 0, 0, LCD.getDisplayXSize() - 1, 20);
    pnlHeader->setBorder(false, true, false, false);
    pnlHeader->add(new Label(&LCD, 0, VerticalAlignment::Center, "Alarm", SmallFont));
    frmAlarm->add(pnlHeader);

    Line *lineBtnSettingsTop = new Line(&LCD, 2, 2, 14, 2);
    Rectangle *rectBtnSettingsTop = new Rectangle(&LCD, lineBtnSettingsTop->getX() + lineBtnSettingsTop->getWidth() - 5, lineBtnSettingsTop->getY() - 2,
                                                  lineBtnSettingsTop->getX() + lineBtnSettingsTop->getWidth() - 2, lineBtnSettingsTop->getY() + 2, true);

    Line *lineBtnSettingsBottom1 = new Line(&LCD, 2, 10, 5, 10);
    Line *lineBtnSettingsBottom2 = new Line(&LCD, 8, 10, 14, 10);

    Rectangle *rectBtnSettingsBottom = new Rectangle(&LCD, lineBtnSettingsBottom1->getX() + lineBtnSettingsBottom1->getWidth(), lineBtnSettingsBottom1->getY() - 2,
                                                     lineBtnSettingsBottom2->getX(), lineBtnSettingsBottom1->getY() + 2);

    GraphicalComponentContainer *shapeBtnSettings = new GraphicalComponentContainer();
    shapeBtnSettings->add(lineBtnSettingsTop);
    shapeBtnSettings->add(rectBtnSettingsTop);
    shapeBtnSettings->add(lineBtnSettingsBottom1);
    shapeBtnSettings->add(rectBtnSettingsBottom);
    shapeBtnSettings->add(lineBtnSettingsBottom2);

    btnSettings = new Button(&LCD, &Touch, HorizontalAlignment::Right, VerticalAlignment::Center, 16, 15, shapeBtnSettings);
    // btnSettings->setBorderless(true);
    pnlHeader->add(btnSettings);

    frmAlarm->add(pnlClock = new Panel(&LCD, 0, pnlHeader->getHeight() + 1, 150, LCD.getDisplayYSize() - pnlHeader->getHeight() - 1));
    pnlClock->setBorder(false, false, false, true);
    pnlClock->add(lblClockAlarm = new Label(&LCD, HorizontalAlignment::Center, VerticalAlignment::Center, rtc.getTimeStr(), BigFont));
    frmAlarm->add(pnlAlarms = new Panel(&LCD, pnlClock->getWidth(), pnlHeader->getHeight() + 1,
                                        LCD.getDisplayXSize() - pnlClock->getWidth() - 1, LCD.getDisplayYSize() - pnlHeader->getHeight() - btnMenu->getHeight() - 5));
    pnlAlarms->setBorder(false, true, false, false);
    static Panel *pnlBtnMenu = new Panel(&LCD, pnlAlarms->getX(), pnlAlarms->getY() + pnlAlarms->getHeight(),
                                         pnlAlarms->getWidth() - btnMenu->getWidth() - 5, LCD.getDisplayYSize() - pnlAlarms->getHeight() - pnlHeader->getHeight() - 1);
    pnlBtnMenu->add(btnAlarm = new Button(&LCD, &Touch, 0, 0, pnlBtnMenu->getWidth() / 3, pnlBtnMenu->getHeight(), "A", SmallFont));
    pnlBtnMenu->add(btnStopWatch = new Button(&LCD, &Touch, HorizontalAlignment::Center, 0, pnlBtnMenu->getWidth() / 3, pnlBtnMenu->getHeight(), "S", SmallFont));
    pnlBtnMenu->add(btnTimer = new Button(&LCD, &Touch, HorizontalAlignment::Right, 0, pnlBtnMenu->getWidth() / 3, pnlBtnMenu->getHeight(), "T", SmallFont));
    pnlBtnMenu->setBorder(false);

    frmAlarm->add(pnlBtnMenu);

    static Panel *pnlAlarm1 = new Panel(&LCD, 0, 0, pnlAlarms->getWidth(), 40);
    pnlAlarm1->setBorder(false, true, false, false);
    static Label *lblTime = new Label(&LCD, 5, 5, "06:30", BigFont);
    pnlAlarm1->add(lblTime);
    static Label *lblLabel = new Label(&LCD, 5, lblTime->getY() + lblTime->getHeight() + 5, "Alarm,", SmallFont);
    pnlAlarm1->add(lblLabel);
    static Label *lblRepeat = new Label(&LCD, lblLabel->getX() + lblLabel->getWidth() + 10, lblLabel->getY(), "Repeat once", SmallFont);
    pnlAlarm1->add(lblRepeat);
    pnlAlarms->add(pnlAlarm1);
    static Label *lblNextRing = new Label(&LCD, HorizontalAlignment::Center, pnlClock->getY() + pnlClock->getHeight() - 50, "No alarms on", SmallFont);
    pnlClock->add(lblNextRing);

    frmAlarm->add(btnMenu);
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

    btnMenu = new Button(&LCD, &Touch, HorizontalAlignment::Right, VerticalAlignment::Down, 16, 16);
    GraphicalComponentContainer *shapeBtnMenu = new GraphicalComponentContainer();
    shapeBtnMenu->add(new Rectangle(&LCD, 2, 3, btnMenu->getWidth() - 2, 4, true));
    shapeBtnMenu->add(new Rectangle(&LCD, 2, 7, btnMenu->getWidth() - 2, 8, true));
    shapeBtnMenu->add(new Rectangle(&LCD, 2, 11, btnMenu->getWidth() - 2, 12, true));
    btnMenu->setGraphics(shapeBtnMenu);
    btnMenu->setBorderless(true);
    btnMenu->setNormalPressAction(&switchFrame);

    loadMainFrame();
    loadSettingsFrame();

    currentFrame = frmMain;
}

void loop()
{
    if (time != rtc.getTime())
    {
        if (currentFrame == frmMain)
        {
            lblClockMain->setText(rtc.getTimeStr());
            lblDate->setText(rtc.getDateStr());
            lblDOW->setText(rtc.getDOWStr());
            lblTemp->setText(String(getTemp()));
        }
        else if (currentFrame == frmAlarm)
        {
            lblClockAlarm->setText(rtc.getTimeStr());
        }

        currentFrame->draw();
        time = rtc.getTime();
    }

    if (Touch.dataAvailable())
    {
        Touch.read();
        currentFrame->onClick(Touch.getX(), Touch.getY());
    }
}