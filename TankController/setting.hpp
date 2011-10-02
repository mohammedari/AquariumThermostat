#pragma once

#include "temperature.hpp"
#include "light_sequence.hpp"

namespace tank_controller
{
    
class setting
{
    public:
    temperature setting_temperature;
    light_sequence light_seq;
};
    
}