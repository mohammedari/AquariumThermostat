#include "save_command.hpp"
#include "temperature.hpp"

using namespace util;

namespace tank_controller {
namespace commands {
    
void save_command::execute(const serial_communication& s, const string& parameter)
{
    _rom.save<temperature>(_address, _status.setting_temperature);
    s.write_line("Data was saved.");
}

}}