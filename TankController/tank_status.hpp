#pragma once

#include <string>

#include "temperature.hpp"
#include "time.hpp"

namespace tank_controller
{

class tank_status
{
	private:
	static const char _on = (char)0xFF;	//Å°
	static const char _off = ' ';
	static const char _arrow = (char)0x7E;	//Å®
	static const char _line_length = 16;
	
    private:
    bool _is_heater_on;
    bool _is_cooler_on;
    bool _is_light_on;
    bool _is_crashed;
    
    public:
    temperature current_temperature;
    temperature setting_temperature;
    time current_time;
    bool is_heater_on() { return _is_heater_on; }
    bool is_cooler_on() { return _is_cooler_on; }
    bool is_light_on() { return _is_light_on; }
    bool is_crashed() { return _is_crashed; }
    
    public:
    tank_status(bool crashed)
        : _is_heater_on(false),
          _is_cooler_on(false),
          _is_light_on(false),
          _is_crashed(crashed)
    {
    }
    string upper_line_str() const;
    string lower_line_str() const;
    void update_switches();
};

}