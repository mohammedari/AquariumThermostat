#include "save_command.hpp"
#include "temperature.hpp"

using namespace util;

namespace tank_controller {
namespace commands {
    
void save_command::execute(const serial_communication& s, const string& parameter)
{
    _rom.save<tank_status>(_address, _status);
    s.write_line("Data was saved.");
}

}}