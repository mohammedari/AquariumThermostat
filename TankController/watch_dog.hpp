#pragma once

namespace util
{

class watch_dog
{
    private:
    bool _is_error_occured_in_previous_execution;
	
	//100ms�������Ȃ���΃��Z�b�g��������
	static const unsigned char _clock_source = 0x0F;	//�����N���b�N ��/8192
	static const unsigned char _write_value = 0x0C;		//����I�ȏ�����WD���W�X�^�ɏ������܂��l
    
    public:
    watch_dog();
    bool is_error_occured_in_previous_execution() const { return _is_error_occured_in_previous_execution; }
    void watch();
    void run();
    void stop();
};

}