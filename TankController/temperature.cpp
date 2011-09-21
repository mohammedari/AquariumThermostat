#include <string>
#include "temperature.hpp"
#include "format_string.hpp"

using namespace util;

namespace tank_controller
{
    
string temperature::str() const
{
	return format_string<7>("%4.1f%c%c", _value, (char)0xDF, 'C');	//
}

}