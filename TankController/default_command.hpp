#pragma once
#include "command_base.hpp"
#include "serial_communication.hpp"

namespace tank_controller {
namespace commands {
    
class default_command : public util::command_base
{
    public:
    virtual bool is_match(const string& command) const { return true; }
    virtual void execute(const util::serial_communication& s, const string& parameter);
};

}}