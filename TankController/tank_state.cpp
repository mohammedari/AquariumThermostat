#include <string>
#include "tank_state.hpp"
#include "format_string.hpp"

using namespace util;

namespace tank_controller
{
    
string tank_state::upper_line_str() const
{        
    return format_string<_line_length + 1>("%s%c%s  %c", 
		current_temperature.str().c_str(), 
		_arrow, 
		setting_temperature.str().c_str(), 
		is_crashed ? 'E' : ' ');
}

string tank_state::lower_line_str() const
{    	
	return format_string<_line_length + 1>("%s H%cC%cL%c", 
		current_time.str().c_str(),
		is_heater_on ? _on : _off, 
		is_cooler_on ? _on : _off, 
		is_light_on  ? _on : _off);
}

}