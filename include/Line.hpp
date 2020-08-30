#pragma once

#include "GraphicalComponent.hpp"

class Line : public GraphicalComponent
{

public:
    Line(lcd::UTFT *LCD, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
    ~Line();

    void draw() override;
};