#pragma once
#include "command_base.hpp"
#include "serial_communication.hpp"
#include "tank_status.hpp"
#include "rtc.hpp"

namespace tank_controller {
namespace commands {
    
class set_command : public util::command_base
{
    private:
    tank_status& _status;
    rtc& _clock;
    
    public:
    set_command(tank_status& status, rtc& clock) : _status(status), _clock(clock) { }
    virtual bool is_match(const string& command) const { return "set" == command; }
    virtual void execute(const util::serial_communication& s, const string& parameter);
};

}}
    