#pragma once
#include "Arduino.h"
#include "UTFT.h"

struct Segment
{
    int x1, y1, x2, y2;
    bool rectangle;
    bool fill;
public:
    Segment(int x1, int y1, int x2, int y2, bool rectangle = false, bool fill = false)
        : x1(x1), y1(y1), x2(x2), y2(y2), rectangle(rectangle), fill(fill)
    {

    }

    void draw(lcd::UTFT *LCD, word color)
    {
        LCD->setColor(color);
        if(rectangle)
        {
            if(fill)
                LCD->fillRect(x1, y1, x2, y2);
            else
                LCD->drawRect(x1, y1, x2, y2);
        }
        else
            LCD->drawLine(x1, y1, x2, y2);
    }
};


class Shape 
{

public:
    Shape(lcd::UTFT *LCD, Segment* segments, uint16_t nSegments, word color = VGA_WHITE);
    ~Shape();

    void draw();
private:
    uint16_t nSegments;
    Segment *segments;

    word color;

    lcd::UTFT *LCD;
};