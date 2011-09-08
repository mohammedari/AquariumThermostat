#include <string>
#include "tank_state.hpp"

namespace tank_controller
{
    
string tank_state::upper_line_str()
{        
    string ret;
    ret += current_temperature.str();
    ret += (char)0x7E; //'¨'
    ret += setting_temperature.str();
    if(is_crashed)
        ret += "   ";
    else
        ret += "  E";
    return ret;
}

string tank_state::lower_line_str()
{
    string ret;
    ret += current_time.str();
    ret += "  H";
    if(is_heater_on)
        ret += (char)0xFF;  //¡
    else
        ret += ' ';
    ret += 'C';
    if(is_cooler_on)
        ret += (char)0xFF;  //¡
    else
        ret += ' ';
    ret += 'L';
    if(is_light_on)
        ret += (char)0xFF;  //¡
    else
        ret += ' ';
    
    return ret;
}

}