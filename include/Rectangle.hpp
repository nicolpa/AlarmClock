#pragma once

#include "GraphicalComponent.hpp"

class Rectangle : public GraphicalComponent
{

public:
    Rectangle(lcd::UTFT *LCD, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, bool fill = false);
    Rectangle(lcd::UTFT *LCD, uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, lcd::Color color, bool fill = false);
    ~Rectangle();

    void clear() override;
    void draw() override;
};