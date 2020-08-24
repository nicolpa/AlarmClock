#pragma once

#include "DS1307.h"
#define SPEAKER 11

class Alarm 
{

public:
    Alarm(uint8_t hour, uint8_t min);
    Alarm(Time time);
    ~Alarm();

    void setAlarm(uint8_t hour, uint8_t min);

    uint8_t getHour();
    uint8_t getMin();

    void setRepeatDays(bool *repeat);
    bool* getRepeatDays();

    void setLabel(String label);
    void setRingDuration(uint8_t ringDuration);
    void setSnoozeDuration(uint8_t snoozeDuration);
    void setNSnooze(uint8_t nSnooze);

    String getLabel();    
    uint8_t getRingDuration();
    uint8_t getSnoozeDuration();
    uint8_t getNSnooze();

    bool check(Time time);

    void ring();

private:
    uint8_t hour;
    uint8_t min;

    bool repeat[7] = {false, false, false, false, false, false, false};
    bool noRepeat = true;
    String label = "Alarm";
    uint8_t ringDuration = 5;
    uint8_t snoozeDuration = 10;
    uint8_t nSnooze = 3;
    bool enable = true;
};