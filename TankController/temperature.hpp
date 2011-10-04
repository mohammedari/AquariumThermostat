#pragma once

#include <string>

namespace tank_controller
{

class temperature
{
    public:
    float value;
    
    public:
    static const float min;
    static const float max;

    public:
    temperature(float value = 0) : value(value) { }
    string str() const;
    bool is_valid() const { return min < value && value < max; }
    
    public:
    bool operator< (const temperature& t) { return value < t.value; }
    bool operator> (const temperature& t) { return value > t.value; }
    float operator- (const temperature& t) { return value - t.value; }
};

}