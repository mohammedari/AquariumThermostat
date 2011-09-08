#pragma once

namespace tank_controller
{

//単一モードスキャンのみ
class adc
{
    private:
    static bool _initialized;
    
    protected:
    virtual unsigned char get_channel() = 0;
    
    public:
    adc();
    unsigned int scan();
};
    
}