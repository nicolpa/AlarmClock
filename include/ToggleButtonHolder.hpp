#pragma once

#include "Container.hpp"
#include "RadioButton.hpp"
#include "CheckBox.hpp"

class ToggleButtonHolder : public Container
{

public:
    ToggleButtonHolder();
    ~ToggleButtonHolder();

    bool* getSelectedButtons();
};