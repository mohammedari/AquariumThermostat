#pragma once

#include "i2c.hpp"
#include "time.hpp"

namespace tank_controller
{
    
class rtc
{
    private:
    static const unsigned char _address = 0xA2; //1010 0010
    util::i2c& _i2c;
    
    static const unsigned char _control_address;
    static const unsigned char _seconds_address;
    
    public:
    rtc(util::i2c& com);
    
    void set(const time& t);
    time get();
    
    private:
    unsigned char _convert_to_bcd(unsigned char integer);
    unsigned char _convert_from_bcd(unsigned char bcd);
};

}