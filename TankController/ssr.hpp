#pragma once

namespace tank_controller
{

class ssr
{
    private:
    bool _is_on;
    static bool _initialized;
    
    protected:
    virtual unsigned char get_mask() = 0;
    
    public:
    ssr();
    void on();
    void off();
    bool is_on() { return _is_on; }
    bool is_off() { return !_is_on; }
};

}