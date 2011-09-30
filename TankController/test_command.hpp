#pragma once
#include "command_base.hpp"
#include "serial_communication.hpp"
#include "wait.hpp"

namespace tank_controller {
namespace commands {
    
class test_command : public util::command_base
{
    public:
    virtual bool is_match(const string& command) const { return "test" == command; }
    virtual void execute(const util::serial_communication& s, const string& parameter) { util::wait(1000); } 
};

}}
    