#pragma once

#include "Shapes.hpp"
#include "LinkedPointerList.h"

class GraphicalComponentContainer : public GraphicalComponent
{
public:
    GraphicalComponentContainer();
    ~GraphicalComponentContainer();

    void draw() override;
    void clear() override;

    void add(GraphicalComponent *graphic);
    void remove(int index);
    GraphicalComponent *get(int index);

    void setForeground(lcd::Color foreground) override;
    void setDisableForeground(lcd::Color disableForeground) override;

private:
    LinkedPointerList<GraphicalComponent> *graphics;
};