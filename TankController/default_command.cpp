#include "default_command.hpp"
#include "serial_communication.hpp"

using namespace util;

namespace tank_controller {
namespace commands {    
    
void default_command::execute(const util::serial_communication& s, const string& parameter)
{
    s.write_line(string("Invalid command was entered. Please type \"help\" and check command list."));
}

}}