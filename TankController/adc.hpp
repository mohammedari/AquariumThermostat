#pragma once

namespace tank_controller
{

//�P�ꃂ�[�h�X�L�����̂�
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