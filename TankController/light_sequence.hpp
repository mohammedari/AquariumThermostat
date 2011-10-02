#pragma once

#include "time.hpp"
#include "array.hpp"

namespace tank_controller
{
    
class light_sequence
{
    public:
    static const size_t size = 24;
    
    private:
    util::array<bool, size> arr;
    
    public:
    void set_on(unsigned char hour) { if(hour < arr.size()){ arr[hour] = true; } }
    void set_off(unsigned char hour) { if(hour < arr.size()){ arr[hour] = false; } }
    bool is_on(const time& t) { return arr[t.hour]; }
    string str(size_t hour);
};

}