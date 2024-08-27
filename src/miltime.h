#pragma once

#include <string>

template <typename T>
class BadParameterException {
    T badParameter;
    T minimum;
    T maximum;
public:
    BadParameterException(T badParameter, T minimum, T maximum) {
        this->badParameter = badParameter;
        this->minimum = minimum;
        this->maximum = maximum;
    }
    T getBadParameter() const { return badParameter; }
    T getMinimum() const { return minimum; }
    T getMaximum() const { return maximum; }
};

template <typename T>
class BadNamedParameterException : public BadParameterException<T> {
    std::string name;
public:
    BadNamedParameterException(T badParameter, T minimum, T maximum, std::string name)
        : BadParameterException<T>(badParameter, minimum, maximum) {
        this->name = name;
    }
    std::string getDescription() const {
        return "Argument " + name + " must be between "
            + std::to_string(this->getMinimum()) + " and "
            + std::to_string(this->getMaximum()) + " (got "
            + std::to_string(this->getBadParameter()) + ")";
    }
};

enum Meridian {
    AM, PM
};

class Time {
private:
    int hour;
    int minute;
    Meridian meridian;
    int getStandardHour(int militaryHour) {
        if (militaryHour < 13) {
            return militaryHour == 0 ? 12 : militaryHour;
        } else {
            return militaryHour - 12;
        }
    }
    void checkParam(int param, int min, int max, std::string paramName) {
        if (param < min || param > max) {
            throw BadNamedParameterException(param, min, max, paramName);
        }
    }
public:
    Time(int hour, int minute, Meridian meridian) {
        checkParam(hour, 1, 12, "hour");
        checkParam(minute, 0, 59, "minute");
        this->hour = hour;
        this->minute = minute;
        this->meridian = meridian;
    }
    Time(int militaryHour, int minute) {
        checkParam(militaryHour, 0, 23, "militaryHour");
        checkParam(minute, 0, 59, "minute");
        this->hour = getStandardHour(militaryHour);
        this->minute = minute;
        this->meridian = militaryHour < 12 ? AM : PM;
    }
    int getHour() const { return hour; }
    int getMinute() const { return minute; }
    Meridian getMeridian() const { return meridian; }
    int getMilitaryHour() const {
        switch (getMeridian()) {
            case AM:
            return getHour() == 12 ? 0 : getHour();
            case PM:
            return getHour() == 12 ? 12 : getHour() + 12;
        }
    }
};
