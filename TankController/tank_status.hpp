#pragma once

#include <string>

#include "temperature.hpp"
#include "time.hpp"
#include "light_sequence.hpp"

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
    
    public:
    bool is_crashed;
    
    public:
    temperature current_temperature;
    temperature setting_temperature;
    time current_time;
    light_sequence light_seq;
    bool is_heater_on() { return _is_heater_on; }
    bool is_cooler_on() { return _is_cooler_on; }
    bool is_light_on() { return _is_light_on; }
    
    public:
    tank_status()
        : _is_heater_on(false),
          _is_cooler_on(false),
          _is_light_on(false),
          is_crashed(false)
    {
    }
    string upper_line_str() const;
    string lower_line_str() const;
    void update_switches();
};

}