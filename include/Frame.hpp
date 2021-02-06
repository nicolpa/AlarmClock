#pragma once

#include "Container.hpp"

class Frame : public Container
{

public:
    Frame(lcd::UTFT *LCD, lcd::Color background = lcd::TRANSPARENT);
    Frame(lcd::UTFT *LCD, URTouch *Touch, lcd::Color background = lcd::TRANSPARENT);
    ~Frame();

    void clear() override;
    void draw() override;
};