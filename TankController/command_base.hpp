#pragma once

#include <string>

namespace tank_controller
{
    
class command_base
{
    public:
    virtual bool is_match(string command) = 0;
    virtual void execute(string parameter) = 0;
};

}