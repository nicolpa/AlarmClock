#include "Slider.hpp"

Slider::Slider(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, uint16_t y, uint16_t length, Orientation orientation, word color, word fillColor, uint32_t backcolor)
    : Component(LCD, Touch, x, y, 0, 0, color, backcolor), fillColor(fillColor), orientation(orientation)
{
    clickable = true;

    if(orientation == Orientation::HORIZONTAL)
    {
        width = length;
        height = 5;
    }
    else
    {
        width = 5;
        height = length;
    }
}

Slider::~Slider()
{
    // if (picker != nullptr)
    //     delete picker;
}

void Slider::draw()
{
    Serial.println("hello ?!." + String(value));
    // delay(1000);
    if(orientation == Orientation::HORIZONTAL)
    {
        int screenSpaceValue = map(value, minimum, maximum, getX(), getX() + width);

        LCD->setColor(fillColor);
        LCD->fillRect(getX(), getY(), screenSpaceValue - 2, getY() + height);
        LCD->setColor(foreground);
        LCD->drawRect(getX(), getY(), screenSpaceValue - 2, getY() + height);

        LCD->setColor(background);
        LCD->fillRect(screenSpaceValue + 3, getY() + 1, getX() + width - 1, getY() + height - 1);
        LCD->setColor(foreground);
        LCD->drawRect(screenSpaceValue + 2, getY(), getX() + width, getY() + height);

        if(showTicks)
        {
            if(ticksValues == nullptr)
            {
                Serial.println("nullptr");
                for(int i = minimum; i <= maximum; i++)
                    LCD->drawVLine(map(i, minimum, maximum, getX(), getX() + width), getY() - 1, height + 2);
            }
            else
            {
                Serial.println("!= nullptr1");
                for(int i = 0; i < nTicks; i++)
                    LCD->drawVLine(map(ticksValues[i], minimum, maximum, getX(), getX() + width), getY() - 1, height + 2);
            }
        }

        LCD->fillRect(screenSpaceValue - 2, getY() - 2, screenSpaceValue + 2, getY() + height + 4);
        // LCD->drawVLine(screenSpaceValue, getY() - 2, height + 4);
    }
    else
    {
        int screenSpaceValue = map(value, minimum, maximum, getY(), getY() + height);

        LCD->setColor(fillColor);
        LCD->fillRect(getX(), getY(), getX() + width, screenSpaceValue - 2);
        LCD->setColor(foreground);
        LCD->drawRect(getX(), getY(), getX() + width, screenSpaceValue - 2);

        LCD->setColor(background);
        LCD->fillRect(getX() + 1, screenSpaceValue + 3, getX() + width - 1, getY() + height - 1);
        LCD->setColor(foreground);
        LCD->drawRect(getX(), screenSpaceValue + 2, getX() + width, getY() + height);

        if(showTicks)
        {
            if(ticksValues == nullptr)
            {
                Serial.println("nullptr2");
                for(int i = minimum; i <= maximum; i++)
                    LCD->drawHLine(getX() - 1, map(i, minimum, maximum, getY(), getY() + height), width + 2);
            }
            else
            {
                Serial.println("!= nullptr2");
                for(int i = 0; i < nTicks; i++)
                    LCD->drawHLine(getX() - 1, map(ticksValues[i], minimum, maximum, getY(), getY() + height), width + 2);
            }
        }

        LCD->fillRect(getX() - 2, screenSpaceValue - 2, getX() + width + 2, screenSpaceValue + 2);
        // LCD->drawHLine(getX() - 2, screenSpaceValue, width + 4);
    }
}

bool Slider::onClick(uint16_t x, uint16_t y)
{

    if (contains(x, y, HIT_BOX_OFFSET))
    {
        Serial.println("Slider");
        // Touch->saveStartPressTime();
        while (Touch->dataAvailable())
        {
            Touch->read();
            int oldValue = value;

            if(orientation == Orientation::HORIZONTAL)
            {
                if(abs(x - Touch->getX()) > 4)
                {
                    x = Touch->getX();
                    if(x < getX()) x = getX();
                    if(x > getX() + width) x = getX() + width;
                    setValue(map(x, getX(), getX() + width, minimum, maximum));
                    if(oldValue != value)
                    {
                        int screenSpaceValue = map(oldValue, minimum, maximum, getX(), getX() + width);
                        LCD->setColor(background);
                        LCD->fillRect(screenSpaceValue - 2, getY() - 2, screenSpaceValue + 2, getY() + height + 4);
                        draw();
                        Serial.println(String(value) + " ->" + String(getX()));
                    }

                } 
            }
            else
            {
                if(abs(y - Touch->getY()) > 4)
                {
                    y = Touch->getY();
                    if(y < getY()) y = getY();
                    if(y > getY() + height) y = getY() + height;
                    setValue(map(y, getY(), getY() + height, minimum, maximum));
                    if(oldValue != value)
                    {
                        int screenSpaceValue = map(oldValue, minimum, maximum, getY(), getY() + height);
                        LCD->setColor(background);
                        LCD->fillRect(getX() - 2, screenSpaceValue - 2, getX() + width + 4, screenSpaceValue + 2);
                        draw();
                        Serial.println(String(value) + " -> " + String(getY()));
                        
                    }
                }
            }
        }

        // if (Touch->getElapsedTime() > 750)
        // {
        //     Serial.println("LongPress");
        // }
        // Touch->resetStartPressTime();


        return true;
    }

    return false;
}

int Slider::getMinimum()
{
    return minimum;
}

int Slider::getMaximum()
{
    return maximum;
}

int Slider::getValue()
{
    return value;
}

bool Slider::getShowTicks()
{
    return showTicks;
}

Orientation Slider::getOrientation()
{
    return orientation;
}

bool Slider::getShowTicksValues()
{
    return showTicks;
}

void Slider::setMinimum(int min)
{
    minimum = min;
}

void Slider::setMaximum(int max)
{
    maximum = max;
}

void Slider::setValue(int value)
{
    this->value = (snapToTicks) ? getClosest(value) : value;

    if (this->value > maximum)
        this->value = maximum;
    else if (this->value < minimum)
        this->value = minimum;

    Serial.println("Slider value : " + String(value));
}

void Slider::setTickSpacing(uint16_t spacing)
{
    if (spacing < 2 || spacing > (uint16_t)((minimum) + abs(maximum)))
    {
        if (ticksValues != nullptr)
        {
            delete [] ticksValues;
            if(ticksValues == nullptr)
            {
                Serial.println("destroy");
            }
            ticksValues = nullptr;
        }
    }
    else
    {
        tickSpacing = spacing;
        nTicks = ceil((abs(minimum) + abs(maximum)) / (float)tickSpacing) + 1;
        ticksValues = new int[nTicks];

        for (int i = 0; i < nTicks - 1; i++)
            ticksValues[i] = minimum + (i * tickSpacing);

        ticksValues[nTicks - 1] = maximum;
    }
}

void Slider::setShowTicks(bool display)
{
    showTicks = display;
}

void Slider::setSnapToTicks(bool snap)
{
    snapToTicks = snap;
    if (snapToTicks)
        setValue(value);
}

void Slider::setOrientation(Orientation orientation)
{
    this->orientation = orientation;
}

void Slider::increaseValueBy(int amount)
{
    if (amount < 0)
    {
        if (value + amount >= minimum)
            setValue(value + amount);
        else
            setValue(minimum);
    }
    else
    {
        if (value + amount <= maximum)
            setValue(value + amount);
        else
            setValue(maximum);
    }
}

int Slider::getClosest(int value)
{
    int curr = ticksValues[0];
    for (int i = 1; i < nTicks; i++)
    {
        if (abs(curr - value) <= abs(ticksValues[i] - value))
            return curr;
        curr = ticksValues[i];
    }
    return curr;
}