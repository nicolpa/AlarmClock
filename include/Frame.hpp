#pragma once

#include "Container.hpp"

class Frame : public Container
{

public:
    Frame(lcd::UTFT *LCD, lcd::Color background = lcd::BLACK);
    ~Frame();

    void clear() override;
    void draw() override;
};