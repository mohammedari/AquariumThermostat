#pragma once

#include <string>

namespace tank_controller
{
    
class command_base
{
    public:
    virtual bool is_match(const string& command) const = 0;
    virtual void execute(const string& parameter) = 0;
};

}