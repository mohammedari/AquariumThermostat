#include "get_command.hpp"
#include "stddef.h"

using namespace util;

namespace tank_controller {
namespace commands {
    
void get_command::execute(const serial_communication& s, const string& parameter)
{
    if("time" == parameter)
        s.write_line("Current time is " + _status.current_time.str());
    else if("status" == parameter)
    {
        s.write_line(_status.upper_line_str());
        s.write_line(_status.lower_line_str());
    }
    else if("light" == parameter)
    {
        for(size_t i = 0; i < _status.light_seq.size; ++i)
            s.write_line(_status.light_seq.str(i));
    }
    else
        s.write_line("Invalid parameter was entered. Please check \"help get\".");
}

}}