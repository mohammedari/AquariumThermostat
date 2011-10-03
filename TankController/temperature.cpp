#include <string>
#include "temperature.hpp"
#include "format_string.hpp"

using namespace util;

namespace tank_controller
{
    
const float temperature::min = 20.0;
const float temperature::max = 35.0;
    
string temperature::str() const
{
    if(!is_valid())
        return "Error!";
	return format_string("%4.1f%c%c", _value, (char)0xDF, 'C');	//
}

}