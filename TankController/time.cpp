#include <string>
#include <stdio.h>
#include "time.hpp"

namespace tank_controller
{
    
string time::str() const
{
    char ret[9];
    sprintf(ret, "%2d:%2d:%2d", hour, minute, second);
    
    return string(ret);
}

}