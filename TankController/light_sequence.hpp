#pragma once

#include "time.hpp"

namespace tank_controller
{
    
class light_sequence
{
    private:
    bool arr[24];
    
    public:
    void set_on(unsigned char hour) { if(0 <= hour && hour <= 23){ arr[hour] = true; } }
    void set_off(unsigned char hour) { if(0 <= hour && hour <= 23){ arr[hour] = false; } }
    bool is_on(const time& t) { return arr[t.hour]; }
};

}