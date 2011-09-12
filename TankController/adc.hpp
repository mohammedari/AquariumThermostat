#pragma once

namespace tank_controller
{

//単一モードスキャンのみ
class adc
{
    private:
    static bool _initialized;
    unsigned char _mask;
    
    public:
    adc(unsigned char mask);
    unsigned int scan();
};
    
}