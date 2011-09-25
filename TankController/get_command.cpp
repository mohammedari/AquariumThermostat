#include "get_command.hpp"

using namespace util;

namespace tank_controller {
namespace commands {
    
void get_command::execute(const serial_communication& s, const string& parameter)
{
    if("time" == parameter)
        s.write_line("Current time is " + _state.current_time.str());
    else if("status" == parameter)
    {
        s.write_line(_state.upper_line_str());
        s.write_line(_state.lower_line_str());
    }
    else
        s.write_line("Invalid parameter was entered. Please check \"help get\".");
}

}}