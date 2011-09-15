#pragma once

#include <string>

namespace tank_controller
{

class time
{
    public:
    unsigned char hour;
    unsigned char minute;
    unsigned char second;
    
    public:
    time()
        : hour(0), minute(0), second(0) { }
    time(unsigned char hour, unsigned char minute, unsigned char second)
        : hour(hour), minute(minute), second(second)
    {
    }
    string str() const;
};

}