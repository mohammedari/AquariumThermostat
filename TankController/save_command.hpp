#pragma once
#include "command_base.hpp"
#include "serial_communication.hpp"
#include "setting.hpp"
#include "eeprom.hpp"

namespace tank_controller {
namespace commands {
    
class save_command : public util::command_base
{
    private:
    const unsigned int _address;
    setting& _set;
    eeprom& _rom;
    
    public:
    save_command(setting& set, eeprom& rom, unsigned int address) : _set(set), _rom(rom), _address(address) { }
    virtual bool is_match(const string& command) const { return "save" == command; }
    virtual void execute(const util::serial_communication& s, const string& parameter);
};

}}
    