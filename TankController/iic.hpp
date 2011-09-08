#pragma once

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
    void send(unsigned char* bytes, size_t size);
    size_t receive(unsigned char* bytes, size_t buffer_size);
};

}