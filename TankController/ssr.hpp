#pragma once

namespace tank_controller
{

class ssr
{
    private:
    static bool _initialized;
    unsigned char _mask;
    
    public:
    ssr(unsigned char _mask);
    void on() const;
    void off() const;
    bool is_on() const;
    bool is_off() const;
};

}