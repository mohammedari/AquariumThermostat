#include <string>
#include "time.hpp"
#include "format_string.hpp"

using namespace util;

namespace tank_controller
{
    
string time::str() const
{
    return format_string<9>("%.2d:%.2d:%.2d", hour, minute, second);
}

}