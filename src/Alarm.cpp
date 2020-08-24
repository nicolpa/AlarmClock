#include "Alarm.hpp"

Alarm::Alarm(uint8_t hour, uint8_t min) 
{
    this->hour = hour;
    this->min = min;
}

Alarm::Alarm(Time time) 
{
    hour = time.hour;
    min = time.min;
}

Alarm::~Alarm() 
{

}

void Alarm::setAlarm(uint8_t hour, uint8_t min) 
{
    this->hour = hour;
    this->min = min;
}

uint8_t Alarm::getHour() 
{
    return hour;
}

uint8_t Alarm::getMin() 
{
    return min;
}

void Alarm::setRepeatDays(bool *repeat) 
{
    int nRepeat = 0;
    for(int i = 0; i < 7; i++)
    {
        this->repeat[i] = repeat[i];
        if(repeat[i])
            nRepeat++;
    }

    if(nRepeat == 0)
        noRepeat = true;
    else
        noRepeat = false;
}

bool* Alarm::getRepeatDays() 
{
    return repeat;
}

void Alarm::setLabel(String label) 
{
    this->label = label;
}

void Alarm::setRingDuration(uint8_t ringDuration) 
{
    this->ringDuration = ringDuration;
}

void Alarm::setNSnooze(uint8_t nSnooze) 
{
    this->nSnooze = nSnooze;
}

String Alarm::getLabel() 
{
    return label;
}

uint8_t Alarm::getRingDuration() 
{
    return ringDuration;
}

uint8_t Alarm::getSnoozeDuration() 
{
    return snoozeDuration;
}

uint8_t Alarm::getNSnooze() 
{
    return nSnooze;
}

bool Alarm::check(Time time) 
{
    if(enable)
    {
        return hour == time.hour && min == time.min;

    }
    return false;
}

void Alarm::ring() 
{
    for(int i = 0 ; i < 255; i++)
    {
        analogWrite(SPEAKER, i);
        delay(150);
    }
    for(int i = 254 ; i >= 0; i--)
    {
        analogWrite(SPEAKER, i);
        delay(150);
    }
}
