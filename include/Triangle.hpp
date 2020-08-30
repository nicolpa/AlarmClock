#pragma once

#include "GraphicalComponent.hpp"

class Triangle : public GraphicalComponent
{
public:
    Triangle(lcd::UTFT *LCD, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t x3, uint16_t y3, bool fill = false);
    ~Triangle();

    void draw() override;

private:
    uint16_t x1, y1;
    uint16_t x2, y2;
    uint16_t x3, y3;
};