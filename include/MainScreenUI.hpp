#pragma once
#include "Components.hpp"
#include <DS1307.h>

class MainScreenUI : public Frame
{
private:
    DS1307 *rtc;
    int LM35;
    
    Label *lblDOW;
    Label *lblDate;
    Label *lblTemp;
    Label *lblClock;

    Button *btnMenu;

public:
    MainScreenUI(lcd::UTFT *LCD, URTouch *Touch, DS1307 *rtc, int LM35);
    ~MainScreenUI();

    void draw() override;

private:
    float getTemp();

};