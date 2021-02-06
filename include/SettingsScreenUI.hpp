#pragma once
#include "Components.hpp"

class SettingsScreenUI : public Frame
{
public:
    SettingsScreenUI(lcd::UTFT *LCD, URTouch *Touch);
    ~SettingsScreenUI();
};