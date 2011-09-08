#pragma once

#include <string>

#include "temperature.hpp"
#include "time.hpp"

namespace tank_controller
{

class tank_state
{
    public:
    temperature current_temperature;
    temperature setting_temperature;
    time current_time;
    bool is_heater_on;
    bool is_cooler_on;
    bool is_light_on;
    bool is_crashed;
    
    public:
    tank_state(bool crashed)
        : is_heater_on(false),
          is_cooler_on(false),
          is_light_on(false),
          is_crashed(crashed)
    {
    }
    string upper_line_str();
    string lower_line_str();
};

}