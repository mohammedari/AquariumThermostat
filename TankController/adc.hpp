#pragma once

namespace util
{

//�P�ꃂ�[�h�̂�
class adc
{
    private:
    static bool _initialized;
    unsigned char _channel;
    
    public:
	//channel��000-111�̂�AN0�`AN7��I��
    adc(unsigned char channel);
    unsigned int scan() const;
};
    
}