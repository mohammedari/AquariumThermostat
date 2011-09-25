#pragma once
#include "command_base.hpp"
#include "serial_communication.hpp"
#include "tank_status.hpp"

namespace tank_controller {
namespace commands {
    
class get_command : public util::command_base
{
    private:
    tank_status& _state;
    
    public:
    get_command(tank_status& state) : _state(state) { }
    virtual bool is_match(const string& command) const { return "get" == command; }
    virtual void execute(const util::serial_communication& s, const string& parameter);
};

}}
    