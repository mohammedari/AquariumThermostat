#include "light_sequence.hpp"
#include "stddef.h"
#include "format_string.hpp"

using namespace util;

namespace tank_controller
{

string light_sequence::str(size_t hour)
{
    if(hour >= arr.size())
        return "";
    
    return format_string("%2d : %s", hour, arr[hour] ? "on" : "off");
}
    
}