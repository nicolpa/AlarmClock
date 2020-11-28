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
        currentFrame = frmAlarm;
    else
        currentFrame = frmMain;
}

void goToSettingsAndBack()
{
    currentFrame->clear();
    if(currentFrame == frmAlarm)
        currentFrame = frmSettings;
    else
        currentFrame = frmAlarm;
}

void sleep()
{
    Serial.println("Sleep");
    static bool sleep = false;
    if(sleep)
    {
        LCD.lcdOn();
        sleep = false;
    }
    else
    {
        LCD.lcdOff();
        sleep = true;
    }
    
    // while(!Touch.dataAvailable());
}

void cycleBrightness()
{
    Serial.println("Cycle");
    static byte level = 100;
    switch (level)
    {
    case 100:
        level = 10;
        break;
    case 75:
        level = 100;
        break;
    case 25:
        level = 75;
        break;
    case 10:
    default:
        level = 25;
        break;
    }

    // LCD.setBrightness(map(level, 0, 100, 0, 255), true);
}

void loadMainFrame()
{
    frmMain = new Frame(&LCD);
    frmMain->add(lblDOW = new Label(&LCD, 2, 2, rtc.getDOWStr(), SmallFont));
    frmMain->add(lblDate = new Label(&LCD, 2, 15, rtc.getDateStr(), SmallFont));
    frmMain->add(lblClockMain = new Label(&LCD, HorizontalAlignment::Center, VerticalAlignment::Center, rtc.getTimeStr(), SevenSegNumFontPlus));

    Panel *pnlTemp = new Panel(&LCD, HorizontalAlignment::Right, VerticalAlignment::Up, 57, 12);
    pnlTemp->setBorder(false);
    pnlTemp->add(lblTemp = new Label(&LCD, HorizontalAlignment::Left, 2, String(getTemp()), SmallFont));
    pnlTemp->add(new Circle(&LCD, 42, 4, 2));
    pnlTemp->add(new Label(&LCD, HorizontalAlignment::Right, 2, "C", SmallFont));
    frmMain->add(pnlTemp);

    frmMain->add(btnMenu);

    // frmMain->setClickable(true);
    // frmMain->setNormalPressAction(&sleep);
    // frmMain->setLongPressAction(&cycleBrightness);
}

void loadAlarmFrame()
{
    frmAlarm = new Frame(&LCD);

    Panel *pnlHeader = new Panel(&LCD, 0, 0, LCD.getDisplayXSize() - 1, 20);
    pnlHeader->setBorder(false, true, false, false);
    pnlHeader->add(new Label(&LCD, 2, VerticalAlignment::Center, "Alarm", SmallFont));
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
    btnSettings->setBorderless(true);
    btnSettings->setContentHighlight(true);
    btnSettings->setNormalPressAction(&goToSettingsAndBack);
    pnlHeader->add(btnSettings);

    frmAlarm->add(pnlClock = new Panel(&LCD, 0, pnlHeader->getHeight() + 1, 150, LCD.getDisplayYSize() - pnlHeader->getHeight() - 1));
    pnlClock->setBorder(false, false, false, true);
    pnlClock->add(lblClockAlarm = new Label(&LCD, HorizontalAlignment::Center, VerticalAlignment::Center, rtc.getTimeStr(), BigFont));
    frmAlarm->add(pnlAlarms = new Panel(&LCD, pnlClock->getWidth(), pnlHeader->getHeight() + 1,
                                        LCD.getDisplayXSize() - pnlClock->getWidth() - 1, LCD.getDisplayYSize() - pnlHeader->getHeight() - btnMenu->getHeight() - 5));
    pnlAlarms->setBorder(false, true, false, false);
    Panel *pnlBtnMenu = new Panel(&LCD, pnlAlarms->getX(), pnlAlarms->getY() + pnlAlarms->getHeight(),
                                         pnlAlarms->getWidth() - btnMenu->getWidth() - 5, LCD.getDisplayYSize() - pnlAlarms->getHeight() - pnlHeader->getHeight() - 1);
    pnlBtnMenu->add(btnAlarm = new Button(&LCD, &Touch, 0, 0, pnlBtnMenu->getWidth() / 3, pnlBtnMenu->getHeight(), "A", SmallFont));
    pnlBtnMenu->add(btnStopWatch = new Button(&LCD, &Touch, HorizontalAlignment::Center, 0, pnlBtnMenu->getWidth() / 3, pnlBtnMenu->getHeight(), "S", SmallFont));
    pnlBtnMenu->add(btnTimer = new Button(&LCD, &Touch, HorizontalAlignment::Right, 0, pnlBtnMenu->getWidth() / 3, pnlBtnMenu->getHeight(), "T", SmallFont));
    pnlBtnMenu->setBorder(false);
    btnAlarm->setBorderHighlight(false);
    btnAlarm->setContentHighlight(true);
    btnStopWatch->setBorderHighlight(false);
    btnStopWatch->setContentHighlight(true);
    btnTimer->setBorderHighlight(false);
    btnTimer->setContentHighlight(true);

    Line *lnLeft = new Line(&LCD, LCD.getDisplayXSize() - 1, pnlBtnMenu->getY(), LCD.getDisplayXSize() - 1, pnlBtnMenu->getY() + pnlBtnMenu->getHeight() - 1);
    Line *lnBottom = new Line(&LCD, pnlBtnMenu->getX() + pnlBtnMenu->getWidth(), LCD.getDisplayYSize() - 1,  LCD.getDisplayXSize() - 1, LCD.getDisplayYSize() - 1);

    frmAlarm->add(lnLeft);
    frmAlarm->add(lnBottom);

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

void loadSettingsFrame()
{
    frmSettings = new Frame(&LCD);

    Panel *pnlHeader = new Panel(&LCD, 0, 0, LCD.getDisplayXSize() - 1, 20);
    pnlHeader->setBorder(false, true, false, false);
    pnlHeader->add(new Label(&LCD, 2, VerticalAlignment::Center, "Settings", SmallFont));
    Button *btnBack = new Button(&LCD, &Touch, HorizontalAlignment::Right, VerticalAlignment::Center, 16, 16);
    GraphicalComponentContainer *gBack = new GraphicalComponentContainer();
    gBack->add(new Line(&LCD, 2, btnBack->getHeight() / 2, btnBack->getWidth() / 2, 2));
    gBack->add(new Line(&LCD, 2, btnBack->getHeight() / 2, btnBack->getWidth() / 2, btnBack->getHeight() - 2));
    btnBack->setGraphics(gBack);
    btnBack->setNormalPressAction(&goToSettingsAndBack);
    btnBack->setBorderless(true);
    btnBack->setContentHighlight(true);
    pnlHeader->add(btnBack);

    Panel *pnlSettingsMenu = new Panel(&LCD, 0,  pnlHeader->getHeight() + 1, 125, LCD.getDisplayYSize() - pnlHeader->getHeight() - 1);
    pnlSettingsMenu->setBorder(false);
    Panel *pnlSettingsOption = new Panel(&LCD, pnlSettingsMenu->getWidth(), pnlSettingsMenu->getY(), LCD.getDisplayXSize() - pnlSettingsMenu->getWidth() - 1, LCD.getDisplayYSize() - pnlHeader->getHeight() - 1);
    pnlSettingsOption->setBorder(false);

    byte nSettigns = 5;

    Button *btnTimeAndDate = new Button(&LCD, &Touch, 
                                        HorizontalAlignment::Center, 0,
                                        pnlSettingsMenu->getWidth(), (pnlSettingsMenu->getHeight() / nSettigns), 
                                        "Time and Date", SmallFont);
    // btnTimeAndDate->setBorderless(true);
    btnTimeAndDate->setHorizontalAlignment(HorizontalAlignment::Left);
    btnTimeAndDate->setContentHighlight(true);
    pnlSettingsMenu->add(btnTimeAndDate);

    Button *btnSoundVolume = new Button(&LCD, &Touch,
                                        HorizontalAlignment::Center, btnTimeAndDate->getHeight(), 
                                        pnlSettingsMenu->getWidth(), (pnlSettingsMenu->getHeight() / nSettigns), 
                                        "Sound", SmallFont);
    // btnSoundVolume->setBorderless(true);
    btnSoundVolume->setHorizontalAlignment(HorizontalAlignment::Left);
    btnSoundVolume->setContentHighlight(true);
    pnlSettingsMenu->add(btnSoundVolume);

    Button *btnSleepSchedule = new Button(&LCD, &Touch, 
                                          HorizontalAlignment::Center, btnSoundVolume->getY(false) + btnSoundVolume->getHeight(), 
                                          pnlSettingsMenu->getWidth(), (pnlSettingsMenu->getHeight() / nSettigns), 
                                          "Sleep Schedule", SmallFont);
    // btnSleepSchedule->setBorderless(true);
    btnSleepSchedule->setHorizontalAlignment(HorizontalAlignment::Left);
    btnSleepSchedule->setContentHighlight(true);
    pnlSettingsMenu->add(btnSleepSchedule);

    Button *btnBrightness = new Button(&LCD, &Touch,
                                       HorizontalAlignment::Center, btnSleepSchedule->getY(false) + btnSleepSchedule->getHeight(), 
                                       pnlSettingsMenu->getWidth(), (pnlSettingsMenu->getHeight() / nSettigns), 
                                       "Brightness", SmallFont);
    // btnBrightness->setBorderless(true);
    btnBrightness->setHorizontalAlignment(HorizontalAlignment::Left);
    btnBrightness->setContentHighlight(true);
    pnlSettingsMenu->add(btnBrightness);

    Button *btnGentleWake = new Button(&LCD, &Touch, 
                                       HorizontalAlignment::Center, btnBrightness->getY(false) + btnBrightness->getHeight(), 
                                       pnlSettingsMenu->getWidth(), (pnlSettingsMenu->getHeight() / nSettigns), 
                                       "Gentle Wake", SmallFont);
    // btnGentleWake->setBorderless(true);
    btnGentleWake->setHorizontalAlignment(HorizontalAlignment::Left);
    btnGentleWake->setContentHighlight(true);
    pnlSettingsMenu->add(btnGentleWake);

    // for(int i = 1; i < nSettigns; i++)
    //     pnlSettingsMenu->add(new Line(&LCD, 7, (pnlSettingsOption->getHeight() / nSettigns) * i, pnlSettingsMenu->getWidth() - 15, (pnlSettingsOption->getHeight() / nSettigns) * i));

    frmSettings->add(pnlHeader);
    frmSettings->add(pnlSettingsMenu);
    frmSettings->add(pnlSettingsOption);
}

void setup()
{
    Serial.begin(9600);

    rtc.begin();
    rtc.halt(false);
    time = rtc.getTime();

    LCD.fade(true);
    LCD.InitLCD();
    // LCD.setBrightness(255, true);

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
    btnMenu->setContentHighlight(true);

    loadMainFrame();
    loadAlarmFrame();
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

    static Component *currentlyClickedOn = nullptr;
    static int x, y;

    if(Touch.dataAvailable())
    {
        Touch.read();
        x = Touch.getX();
        y = Touch.getY();

        Component *tmpComponentClickedOn = currentFrame->onClick(x, y);

        if(tmpComponentClickedOn != currentlyClickedOn)
        {
            if(currentlyClickedOn != nullptr)
                currentlyClickedOn->onRelease(x, y);
            
            currentlyClickedOn = tmpComponentClickedOn;
        }
    }
    else if(currentlyClickedOn != nullptr)
    {
        currentlyClickedOn->onRelease(x, y);
        currentlyClickedOn = nullptr;
    }
}