#include "Slider.hpp"

Slider::Slider(lcd::UTFT *LCD, URTouch *Touch, uint16_t x, uint16_t y, uint16_t length, Orientation orientation)
    : Component(LCD, Touch, x, y, 0, 0), fillColor(lcd::BLUE), orientation(orientation)
{
    clickable = true;

    if (orientation == Orientation::HORIZONTAL)
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
    if (ticksValues != nullptr)
        delete[] ticksValues;
}

void Slider::draw()
{
    if (valid || !visible)
        return;

    if (orientation == Orientation::HORIZONTAL)
    {
        int screenSpaceValue = map(value, minimum, maximum, getX(), getX() + width);
        int screenSpacePreviousValue = map(previousValue, minimum, maximum, getX(), getX() + width);

        //Clear thumb
        LCD->setColor(getCurrentBackground());
        LCD->fillRect(screenSpacePreviousValue - 2, getY() - 2, screenSpacePreviousValue + 2, getY() + height + 4);

        //Fill slider
        LCD->setColor((screenSpaceValue < screenSpacePreviousValue) ? getCurrentBackground() : fillColor);
        LCD->fillRect(screenSpacePreviousValue, getY() + 1, screenSpaceValue, getY() + height - 1);

        //Draw frame
        LCD->setColor(getCurrentForeground());
        LCD->drawRect(getX(), getY(), getX() + width, getY() + height);

        LCD->setColor(lcd::WHITE);
        if (showTicks)
        {
            if (ticksValues == nullptr)
                for (int i = minimum; i <= maximum; i++)
                    LCD->drawVLine(map(i, minimum, maximum, getX(), getX() + width), getY() - 1, height + 2);
            else
                for (int i = 0; i < nTicks; i++)
                    LCD->drawVLine(map(ticksValues[i], minimum, maximum, getX(), getX() + width), getY() - 1, height + 2);
        }

        //draw thumb
        LCD->fillRect(screenSpaceValue - 2, getY() - 2, screenSpaceValue + 2, getY() + height + 3);
    }
    else
    {
        int screenSpaceValue = map(value, minimum, maximum, getY(), getY() + height);
        int screenSpacePreviousValue = map(previousValue, minimum, maximum, getY(), getY() + height);

        //Clear thumb
        LCD->setColor(getCurrentBackground());
        LCD->fillRect(getX() - 2, screenSpacePreviousValue - 2, getX() + width + 4, screenSpacePreviousValue + 2);

        //Fill slider
        LCD->setColor((screenSpaceValue < screenSpacePreviousValue) ? getCurrentBackground() : fillColor);
        LCD->fillRect(getX() + 1, screenSpacePreviousValue, getX() + width - 1, screenSpaceValue);

        //Draw frame
        LCD->setColor(getCurrentForeground());
        LCD->drawRect(getX(), getY(), getX() + width, getY() + height);

        LCD->setColor(lcd::WHITE);
        if (showTicks)
        {
            if (ticksValues == nullptr)
                for (int i = minimum; i <= maximum; i++)
                    LCD->drawHLine(getX() - 1, map(i, minimum, maximum, getY(), getY() + height), width + 2);
            else
                for (int i = 0; i < nTicks; i++)
                    LCD->drawHLine(getX() - 1, map(ticksValues[i], minimum, maximum, getY(), getY() + height), width + 2);
        }

        //draw thumb
        LCD->fillRect(getX() - 2, screenSpaceValue - 2, getX() + width + 3, screenSpaceValue + 2);
    }

    valid = true;
}

Component *Slider::onClick(uint16_t x, uint16_t y)
{
    if (contains(x, y, HIT_BOX_OFFSET) || focus)
    {
        static int prevX = 0;
        static int prevY = 0;
        if (!focus)
        {
            focus = true;
            Touch->saveStartPressTime();
        }

        if (orientation == Orientation::HORIZONTAL)
        {
            if (abs(prevX - x) > 4)
            {
                prevX = x;
                if (x < getX())
                    x = getX();
                if (x > getX() + width)
                    x = getX() + width;

                setValue(map(x, getX(), getX() + width, minimum, maximum));
                draw();
            }
        }
        else
        {
            if (abs(prevY - y) > 4)
            {
                prevY = y;
                if (y < getY())
                    y = getY();
                if (y > getY() + height)
                    y = getY() + height;

                setValue(map(y, getY(), getY() + height, minimum, maximum));
                draw();
            }
        }
        return this;
    }

    return nullptr;
}

void Slider::onRelease(uint16_t x, uint16_t y)
{
    if (!Touch->dataAvailable())
    {
        Component::onRelease(x, y);

        // focus =  false;
    }
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
    valid = false;
}

void Slider::setMaximum(int max)
{
    maximum = max;
    valid = false;
}

void Slider::setValue(int value)
{
    previousValue = this->value;

    this->value = (snapToTicks) ? getClosest(value) : value;

    if (this->value > maximum)
        this->value = maximum;
    else if (this->value < minimum)
        this->value = minimum;

    valid = false;
}

void Slider::setTickSpacing(uint16_t spacing)
{
    if (spacing < 2 || spacing > (uint16_t)((minimum) + abs(maximum)))
    {
        if (ticksValues != nullptr)
        {
            delete[] ticksValues;
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
    valid = false;
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
    valid = false;
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

void Slider::clear()
{
    Component::clear();
    previousValue = minimum;
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