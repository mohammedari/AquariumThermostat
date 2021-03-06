#pragma once

#include <string>
#include "iodefine.h"
#include "list.hpp"
#include "serial_communication_receiver_base.hpp"

namespace util
{

class serial_communication
{
    private:
    static const char new_line = (char)0x0A;        //LF
    static const char back_space = (char)0x08;      //BS
    
    private:
    static const unsigned char _baud_rate = 0x0F;   //38400
    static serial_communication* _instance;
    list<serial_communication_receiver_base*> _receiver_list;
    
    private:
    serial_communication();
    serial_communication(const serial_communication& s) { }
    
    public:
    static serial_communication& get_instance();
    static void delete_instance();
    
    public:
    void putc(char c) const;
    
    public:
    void register_receiver(const serial_communication_receiver_base& receiver) { _receiver_list.push_back((serial_communication_receiver_base*)&receiver); }
    void write(const string& str) const;
	void write_line(const string& str) const;
    
    public:
    static bool is_control_character(char c) { return 0x1F > c || 0x7F == c; }
    static bool is_back_space(char c) { return back_space == c; }
    static bool is_new_line(char c) { return new_line == c; }
    
    //これを受信割り込み関数から呼んでください…
    void receive_intrrupt()
    {        
		//エラーが起きたらクリア
		//エラー処理は特にしない
		if(SCI3.SSR.BIT.OER || SCI3.SSR.BIT.PER || SCI3.SSR.BIT.FER)
		{
			SCI3.SSR.BIT.OER = 0; SCI3.SSR.BIT.PER = 0; SCI3.SSR.BIT.FER = 0;
            SCI3.SSR.BIT.RDRF = 0;
			return;
		}
		
		while(!SCI3.SSR.BIT.RDRF)
			;
			
        //一文字受信
		char c = SCI3.RDR;
        
        //すべての受信イベントを起動
        for(list<serial_communication_receiver_base*>::iterator itr = (*_instance)._receiver_list.begin();
            itr != (*_instance)._receiver_list.end(); ++itr)
            (**itr).on_received(*_instance, c);
    }
};

}