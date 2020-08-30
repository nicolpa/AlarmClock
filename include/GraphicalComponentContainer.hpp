#pragma once

#include "Shapes.hpp"
#include "LinkedPointerList.h"

class GraphicalComponentContainer : public GraphicalComponent
{
public:
    GraphicalComponentContainer();
    ~GraphicalComponentContainer();

    LinkedPointerList<GraphicalComponent> *getGraphics();

    void draw() override;

    void setForeground(word foreground) override;
    void setDisableForeground(word disableForeground) override;
private:
    LinkedPointerList<GraphicalComponent> *graphics;
};