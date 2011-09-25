#include <string>
#include "tank_status.hpp"
#include "format_string.hpp"

using namespace util;

namespace tank_controller
{
    
string tank_status::upper_line_str() const
{        
    return format_string<_line_length + 1>("%s%c%s  %c", 
		current_temperature.str().c_str(), 
		_arrow, 
		setting_temperature.str().c_str(), 
		_is_crashed ? 'E' : ' ');
}

string tank_status::lower_line_str() const
{    	
	return format_string<_line_length + 1>("%s H%cC%cL%c", 
		current_time.str().c_str(),
		_is_heater_on ? _on : _off, 
		_is_cooler_on ? _on : _off, 
		_is_light_on  ? _on : _off);
}

void tank_status::update_switches()
{
    if(current_temperature > setting_temperature)
        _is_heater_on = false;
    if(current_temperature < setting_temperature)
        _is_cooler_on = false; 
    
    if(1.0 < setting_temperature - current_temperature)
        _is_heater_on = true;
    if(1.0 < current_temperature - setting_temperature)
        _is_cooler_on = true;
        
    //lightのスイッチについてもココで操作
        
}

}