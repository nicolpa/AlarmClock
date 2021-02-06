#pragma once
#include "Components.hpp"
#include "Line.hpp"
#include <DS1307.h>

class ClockSettingsUI : public Frame
{
private:
    DS1307 *rtc;

public:
    ClockSettingsUI(lcd::UTFT *LCD, URTouch *Touch, DS1307 *rtc);
    ~ClockSettingsUI();
};