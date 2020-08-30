#pragma once

#include "GraphicalComponent.hpp"

class Circle : public GraphicalComponent
{

public:
    Circle(lcd::UTFT *LCD, uint16_t x, uint16_t y, uint16_t radius, bool fill = false);
    ~Circle();

    void draw() override;

private:
    bool fill;
};