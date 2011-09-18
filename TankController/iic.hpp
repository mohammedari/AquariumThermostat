#pragma once
#include "stddef.h"
#include "suicide.hpp"

namespace tank_controller
{

//�}�X�^���[�h��p
class iic
{
    public:
    iic();
    
    void start(unsigned char address);
    void end();
    void send(const unsigned char* bytes, size_t size);
    size_t receive(unsigned char* bytes, size_t buffer_size);
};

}