#pragma once

#include "suicide.hpp"

namespace tank_controller
{

//マスタモード専用
class iic
{
    public:
    iic();
    
    void start(unsigned char address);
    void end();
    void send(unsigned char* bytes, size_t size);
    size_t receive(unsigned char* bytes, size_t buffer_size);
};

}