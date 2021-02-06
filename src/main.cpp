#include <Arduino.h>

#include "UTFT.h"
#include "URTouch.h"
#include "DS1307.h"

#include "MainScreenUI.hpp"
#include "AlarmScreenUI.hpp"
#include "SettingsScreenUI.hpp"

#include "Components.hpp"

#include "Alarm.hpp"

#define LM35 A5

lcd::UTFT LCD(ITDB32S, 38, 39, 40, 41);
URTouch Touch(6, 5, 4, 3, 2);

DS1307 rtc(SDA, SCL);
Time time;

LinkedPointerList<Alarm> alarms;

Frame *currentScreen;

MainScreenUI *mainSrc;
AlarmScreenUI *alarmSrc;
SettingsScreenUI *settingsSrc;

void gotoAlarmScr()
{
	currentScreen->clear();
	currentScreen = alarmSrc;
}

void gotoMainScr()
{
	currentScreen->clear();
	currentScreen = mainSrc;
}

void gotoSettingsSrc()
{
	currentScreen->clear();
	currentScreen = settingsSrc;
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

	mainSrc = new MainScreenUI(&LCD, &Touch, &rtc, LM35);
	alarmSrc = new AlarmScreenUI(&LCD, &Touch, &rtc);
	settingsSrc = new SettingsScreenUI(&LCD, &Touch);

	mainSrc->getComponent(0)->setNormalPressAction(&gotoAlarmScr);
	alarmSrc->getComponent(0)->setNormalPressAction(&gotoMainScr);
	alarmSrc->getComponent(1)->setNormalPressAction(&gotoSettingsSrc);
	((Panel*)settingsSrc->getComponent(0))->getComponent(0)->setNormalPressAction(&gotoAlarmScr);

	currentScreen = mainSrc;
}

void loop()
{
	if (time != rtc.getTime())
	{
		currentScreen->draw();
		time = rtc.getTime();
	}

	static Component *currentlyClickedOn = nullptr;
	static int x, y;

	if (Touch.dataAvailable())
	{
		Touch.read();
		x = Touch.getX();
		y = Touch.getY();

		Component *tmpComponentClickedOn = currentScreen->onClick(x, y);

		if (tmpComponentClickedOn != currentlyClickedOn)
		{
			if (currentlyClickedOn != nullptr)
				currentlyClickedOn->onRelease(x, y);

			currentlyClickedOn = tmpComponentClickedOn;
		}
	}
	else if (currentlyClickedOn != nullptr)
	{
		currentlyClickedOn->onRelease(x, y);
		currentlyClickedOn = nullptr;
	}
}