#pragma once

enum Meridian {
    AM, PM
};

class Time {
private:
    int hour;
    int minute;
    Meridian meridian;
public:
    Time(int hour, int minute, Meridian meridian) {
        this->hour = hour;
        this->minute = minute;
        this->meridian = meridian;
    }
    int getHour() const { return hour; }
    int getMinute() const { return minute; }
    Meridian getMeridian() const { return meridian; }
};
