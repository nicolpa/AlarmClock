#include <Arduino.h>

#include "LinkedPointerList.h"

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
#include "Shapes.hpp"
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
Panel *pnlTemp;

GraphicalComponentContainer *shapeBtnSettings;

Button *btnHourUp, *btnMinUp, *btnSecUp, *btnDayUp, *btnMonthUp, *btnYearUp;
Button *btnHourDown, *btnMinDown, *btnSecDown, *btnDayDown, *btnMonthDown, *btnYearDown;
Label *lblClockSettings, *lblDateSettings;
Circle *circTemp;
Label *lblTempC;

Alarm *Alarms[5];
uint8_t nAlarm = 0;

LinkedPointerList<Component>* frm;

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

Panel *test;
GraphicalComponentContainer *teste;
void loadMainScreen()
{
    lblClock = new Label(&LCD, HorizontalAlignment::Center, VerticalAlignment::Center, rtc.getTimeStr(), SevenSegNumFontPlus);
    // lblClock->draw();
    lblDow = new Label(&LCD, HorizontalAlignment::Left, 2, rtc.getDOWStr(), SmallFont);
    lblDate = new Label(&LCD, HorizontalAlignment::Left, 15, rtc.getDateStr(), SmallFont);
    lblTemp = new Label(&LCD, HorizontalAlignment::Left, 2, String(getTemp()), SmallFont);
    pnlTemp = new Panel(&LCD, HorizontalAlignment::Right, VerticalAlignment::Up, 56, 12);
    pnlTemp->setBorder(false);
    pnlTemp->add(lblTemp);
    circTemp = new Circle(&LCD, 44, 4, 2);
    pnlTemp->add(circTemp);
    
    lblTempC = new Label(&LCD, 311, 2, "C", SmallFont);
    Serial.println("C : " + String(lblTempC->getX()));
    pnlTemp->add(lblTempC);
    
    frmMain = new Frame(&LCD);
    frmMain->add(lblClock);
    frmMain->add(lblDow);
    frmMain->add(lblDate);
    frmMain->add(pnlTemp);
    Serial.println("C : " + String(lblTempC->getX()));

    // shapeBtnSettings = new GraphicalComponentContainer();
    // shapeBtnSettings->getGraphics()->add(new Rectangle(&LCD, btnSettings->getX() + 2, btnSettings->getY() + 3, btnSettings->getX() + btnSettings->getWidth() - 2, btnSettings->getY() + 4, true));
    // shapeBtnSettings->getGraphics()->add(new Rectangle(&LCD, btnSettings->getX() + 2, btnSettings->getY() + 7, btnSettings->getX() + btnSettings->getWidth() - 2, btnSettings->getY() + 8, true));
    // shapeBtnSettings->getGraphics()->add(new Rectangle(&LCD, btnSettings->getX() + 2, btnSettings->getY() + 11, btnSettings->getX() + btnSettings->getWidth() - 2, btnSettings->getY() + 12, true));
    // shapeBtnSettings->draw();

    
    Serial.println("Draw");
    btnSettings = new Button(&LCD, &Touch, HorizontalAlignment::Right, VerticalAlignment::Down, 15, 15);
    btnSettings->setBorderless(true);
    frmMain->add(btnSettings);
}

void loadSettingsScreen()
{
    lblSettingsHeader = new Label(&LCD, 2, 2, "Settings", SmallFont);

    frmSettings = new Frame(&LCD, 10);
    frmSettings->add(btnSettings);


    pnlSettingsHeader = new Panel(&LCD, 0, 0, LCD.getDisplayXSize() - 1, 20, 20);
    pnlSettingsHeader->setBorder(false, true, false, false);
    pnlClockSettings = new Panel(&LCD, 0, pnlSettingsHeader->getHeight() + 1, 150, LCD.getDisplayYSize() - 1 - pnlSettingsHeader->getHeight() - 16, 10);
    pnlClockSettings->setBorder(false, false, false, true);

    lblClockSettings = new Label(&LCD, HorizontalAlignment::Center, VerticalAlignment::Center, rtc.getTimeStr(), BigFont);

    lblClockSettings = new Label(&LCD, HorizontalAlignment::Center, VerticalAlignment::Center, rtc.getTimeStr(), BigFont);
    lblDateSettings = new Label(&LCD, HorizontalAlignment::Center, VerticalAlignment::Center, rtc.getDateStr(), BigFont);
    pnlDateDowSettings->setBorder(false);
    pnlBtnSettings = new Panel(&LCD, pnlClockSettings->getWidth(), pnlDateDowSettings->getY() + pnlDateDowSettings->getHeight(), pnlDateDowSettings->getX() + pnlDateDowSettings->getWidth(), LCD.getDisplayXSize() - 1 - pnlClockSettings->getWidth(), 10);
    pnlDateDowSettings = new Panel(&LCD, pnlClockSettings->getWidth() + 1, pnlSettingsHeader->getHeight() + 1, LCD.getDisplayXSize() - 1 - pnlClockSettings->getWidth(), LCD.getDisplayYSize() - pnlSettingsHeader->getWidth() - 2 - 16, 10);
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
    frmSettings = new Frame(&LCD);
    frmSettings->add(btnSettings);
    teste = new GraphicalComponentContainer();
    teste->getGraphics()->add(new Rectangle(&LCD, btnSettings->getX() + 2, btnSettings->getY() + 3, btnSettings->getX() + btnSettings->getWidth() - 2, btnSettings->getY() + 4, true));
    teste->getGraphics()->add(new Rectangle(&LCD, btnSettings->getX() + 2, btnSettings->getY() + 7, btnSettings->getX() + btnSettings->getWidth() - 2, btnSettings->getY() + 8, true));
    teste->getGraphics()->add(new Rectangle(&LCD, btnSettings->getX() + 2, btnSettings->getY() + 11, btnSettings->getX() + btnSettings->getWidth() - 2, btnSettings->getY() + 12, true));
    teste->draw();
    Serial.println("Done");
    // loadSettingsScreen();

    btnSettings->setNormalPressAction(&switchFrame);
    btnSettings->setTextHighlight(true);

    currentFrame = frmMain;

    // alarm1 = new Alarm(12, 4);
    btnSettings->setGraphics(teste);
}

void loop()
{
    if (time != rtc.getTime())
    {
        if (currentFrame == frmMain)
        {
            lblClock->setText(rtc.getTimeStr());
            lblDow->setText(rtc.getDOWStr());
            lblDate->setText(rtc.getDateStr());
            lblTemp->setText(String(getTemp()));
        }
        else
        {
            // lblClockSettings->setText(rtc.getTimeStr());
        }

        currentFrame->draw();
        time = rtc.getTime();
    }

    if (Touch.dataAvailable())
    {
        Touch.read();
        int x = Touch.getX();
        int y = Touch.getY();
        currentFrame->onClick(x, y);
    }
}