#include "help_command.hpp"

using namespace util;

namespace tank_controller {
namespace commands {
    
void help_command::execute(const serial_communication& s, const string& parameter)
{
    s.write_line(string("Do you need a help?"));
}

}}