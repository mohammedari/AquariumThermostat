#pragma once

#include "temperature.hpp"
#include "adc.hpp"

namespace tank_controller
{

class thermometer : public adc
{
    public:
    thermometer() : adc(0x00) { }
    temperature measure();
};

}