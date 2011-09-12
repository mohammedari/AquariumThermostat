#pragma once

namespace tank_controller
{

class ssr
{
    private:
    bool _is_on;
    static bool _initialized;
    unsigned char _mask;
    
    public:
    ssr(unsigned char _mask);
    void on();
    void off();
    bool is_on() { return _is_on; }
    bool is_off() { return !_is_on; }
};

}