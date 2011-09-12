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
    string str();
};

}