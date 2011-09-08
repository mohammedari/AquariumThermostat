#pragma once

#include <string>

namespace tank_controller
{

class temperature
{
    private:
    float _value;

    public:
    temperature()
        : _value(0)
    {
    }
    temperature(unsigned char ad_value);
    string str();
};

}