#pragma once

#include <string>

namespace tank_controller
{

class temperature
{
    private:
    float _value;
    
    public:
    static const float min;
    static const float max;

    public:
    temperature(float value = 0) : _value(value) { }
    string str() const;
    bool is_valid() const { return min < _value && _value < max; }
    
    public:
    bool operator< (const temperature& t) { return _value < t._value; }
    bool operator> (const temperature& t) { return _value > t._value; }
    float operator- (const temperature& t) { return _value - t._value; }
};

}