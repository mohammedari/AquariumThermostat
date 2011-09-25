#include "help_command.hpp"

using namespace util;

namespace tank_controller {
namespace commands {
    
void help_command::execute(const serial_communication& s, const string& parameter)
{
    if("get" == parameter)
    {
        s.write_line("usage: get <parameter>");
        s.write_line("<parameter> = status, time");
    }
    else
    {
        s.write_line("Do you need a help?");
        s.write_line("Please check \"help <command>\" for more information.");
        s.write_line("<command> = get, set");
    }
}

}}