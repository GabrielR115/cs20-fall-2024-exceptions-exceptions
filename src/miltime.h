#pragma once
#include <iostream>

using namespace std;

enum Meridian {
    AM, PM
};

template<typename T>
class BadParameterException {
private:
T badParameter, minimum, maximum;
public:
    BadParameterException(T badParameter, T minimum, T maximum){
        this->badParameter = badParameter;
        this->minimum = minimum;
        this->maximum = maximum;
    }

    int getBadParameter() const { return badParameter; }
    int getMinimum() const { return minimum; }
    int getMaximum() const { return maximum; }

};

template <typename T>
class BadNamedParameterException : public BadParameterException<T> {
    string name;
public:
    BadNamedParameterException(T badParameter, T minimum, T maximum, string parName)
        : BadParameterException<T>(badParameter, minimum, maximum) {
        this->name = parName;
    }
    string getDescription() const {
        return "Argument " + name + " needs to be between "+ 
        to_string(this->getMinimum()) + " and" +
        to_string(this->getMaximum()) + " rather than: " +
         to_string(this->getBadParameter());
    }
};

class Time {
private:
    int hour;
    int minute;
    Meridian meridian;

    void checkParam(int par, int min, int max, string parName){
        if(par < min || par > max){
            throw BadNamedParameterException(par, min, max, parName);
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
    //24 - 12
    Time(int militaryHour, int minute){
        checkParam(militaryHour, 0, 23, "militaryHour");
        checkParam(minute, 0, 59, "minute");
         if (militaryHour >= 12) {

            meridian = PM;

            if (militaryHour > 12) {

                hour = militaryHour - 12;

            } else {
                hour = 12; //militaryHour == 12 
            }
        } 

        else {
            meridian = AM;

            switch(militaryHour){
                case 0:
                    hour = 12;
                    break;
                default: 
                    hour = militaryHour;
                    break;
            }
        }
    }

    int getHour() const { return hour; }
    int getMinute() const { return minute; }
    Meridian getMeridian() const { return meridian; }
    int getMilitaryHour(){

        if (getMeridian() == AM) {
            if (getHour() == 12) {
                return 0;  
            }
            else {
                return getHour();  
            }

        } 

        else if (getMeridian() == PM) {
            if (getHour() == 12) {
                return 12;  
            } 
            else {
                return getHour() + 12;  
            }
        }

        return hour;
    }
};
