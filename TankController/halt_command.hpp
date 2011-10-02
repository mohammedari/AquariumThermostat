#pragma once
#include "command_base.hpp"
#include "serial_communication.hpp"
#include "wait.hpp"

namespace tank_controller {
namespace commands {
    
class halt_command : public util::command_base
{
    public:
    virtual bool is_match(const string& command) const { return "halt" == command; }
    virtual void execute(const util::serial_communication& s, const string& parameter) { while(true); } 
};

}}
    