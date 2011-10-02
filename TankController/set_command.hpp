#pragma once
#include "command_base.hpp"
#include "serial_communication.hpp"
#include "setting.hpp"
#include "rtc.hpp"

namespace tank_controller {
namespace commands {
    
class set_command : public util::command_base
{
    private:
    setting& _set;
    rtc& _clock;
    
    public:
    set_command(setting& set, rtc& clock) : _set(set), _clock(clock) { }
    virtual bool is_match(const string& command) const { return "set" == command; }
    virtual void execute(const util::serial_communication& s, const string& parameter);
};

}}
    