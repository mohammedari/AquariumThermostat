#pragma once

#include <string>

namespace tank_controller
{

class temperature
{
    private:
    float _value;

    public:
    temperature(float value = 0) : _value(value) { }
    string str() const;
    
    public:
    bool operator< (const temperature& t) { return _value < t._value; }
    bool operator> (const temperature& t) { return _value > t._value; }
    float operator- (const temperature& t) { return _value - t._value; }
};

}