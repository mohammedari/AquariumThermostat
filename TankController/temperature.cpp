#include <string>
#include <stdio.h>
#include "temperature.hpp"

namespace tank_controller
{
    
string temperature::str() const
{
    char ret[7];
    
    string format("%4.1f");
    format += (char)0xDF;
    format += 'C';
    
    sprintf(ret, format.c_str(), _value);
    
    return string(ret);
}

}