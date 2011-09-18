#pragma once

#include <string>
#include "serial_communication.hpp"

namespace util
{
    
class command_base
{
    public:
    virtual bool is_match(const string& command) const = 0;
    virtual void execute(const serial_communication& s, const string& parameter) = 0;
};

}