#pragma once

#include "iodefine.h"
#include "linked_list.hpp"
#include "serial_communication_receiver_base.hpp"

namespace util
{

class serial_communication
{
    private:
    static const unsigned char _baud_rate = 0x0F;   //38400
    static bool _initialized;
    static linked_list<serial_communication*> _instances;
    linked_list<serial_communication_receiver_base*> _receiver_list;
    
    public:
    serial_communication();
    void register_receiver(const serial_communication_receiver_base& receiver) { _receiver_list.add((serial_communication_receiver_base*)&receiver); }
	
	class hoge : public serial_communication_receiver_base
	{
		virtual void on_received(char c) { }
	};
	void fuck()
	{
		hoge c;
		_receiver_list.add(&c);
	}
	
	
    //�������M���荞�݊֐�����Ă�ł��������c
    static void receive_intrrupt()
    {
		//�G���[���N������N���A
		//�G���[�����͓��ɂ��Ȃ�
		if(SCI3.SSR.BIT.OER || SCI3.SSR.BIT.PER || SCI3.SSR.BIT.FER)
		{
			SCI3.SSR.BIT.OER = 1; SCI3.SSR.BIT.PER = 1; SCI3.SSR.BIT.FER = 1;
			return;
		}
		
		while(SCI3.SSR.BIT.RDRF)
			;
			
        //�ꕶ����M
		char c = SCI3.RDR;
        
        //���ׂẴC���X�^���X�̂��ׂĂ̎�M�C�x���g���N��
        for(linked_list<serial_communication*>::iterator itc = _instances.begin(); 
            itc != _instances.end(); ++itc)
            for(linked_list<serial_communication_receiver_base*>::iterator itr = (**itc)._receiver_list.begin();
                itr != (**itc)._receiver_list.end(); ++itr)
                (**itr).on_received(c);
    }
};

}