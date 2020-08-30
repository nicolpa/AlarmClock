#pragma once

#include "Component.hpp"

class GraphicalComponent : public Component
{

public:
    GraphicalComponent(lcd::UTFT *LCD, uint16_t x, uint16_t y, uint16_t width, uint16_t height, bool fill = false);
    virtual ~GraphicalComponent();

    void setFill(bool fill);

    bool getFill();

protected:
    bool fill;
};