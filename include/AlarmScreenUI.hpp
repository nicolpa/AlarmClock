#pragma once
#include "Components.hpp"
#include "Alarm.hpp"
#include "DS1307.h"

class AlarmScreenUI : public Frame
{
private:
    DS1307 *rtc;
    
    Label *lblClock;

    Button *btnAlarm;
    Button *btnStopwatch;
    Button *btnTimer;
    Button *btnSettings;
    Button *btnMenu;

    Alarm *alarms[5];


public:
    AlarmScreenUI(lcd::UTFT *LCD, URTouch *Touch, DS1307 *rtc);
    ~AlarmScreenUI();

    void draw() override;
};