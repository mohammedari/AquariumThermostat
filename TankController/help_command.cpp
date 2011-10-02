#include "help_command.hpp"

using namespace util;

namespace tank_controller {
namespace commands {
    
void help_command::execute(const serial_communication& s, const string& parameter)
{
    if("get" == parameter)
    {
        s.write_line("usage: get <parameter>");
        s.write_line("<parameter> = status, time, light");
    }
    else if("set" == parameter)
    {
        s.write_line("usage: set <parameter> <value>");
        s.write_line("<parameter> <value> = time xx:xx:xx, temperature xx.x, light xx (on|off)");
    }
    else if("save" == parameter)
    {
        s.write_line("usage: save");
        s.write_line("This command saves parameters to eeprom.");
    }
    else
    {
        s.write_line("Do you need a help?");
        s.write_line("Available commands are \"get\", \"set\", \"save\".");
        s.write_line("Please check \"help <command>\" for more information.");
    }
}

}}