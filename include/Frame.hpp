#pragma once

#include "Container.hpp"

class Frame : public Container
{

public:
    Frame(lcd::UTFT *LCD, word background = VGA_TRANSPARENT);
    ~Frame();

    void draw() override;
};