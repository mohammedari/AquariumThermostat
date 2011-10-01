#pragma once
#include "command_base.hpp"
#include "serial_communication.hpp"
#include "serial_communication_receiver_base.hpp"
#include "list.hpp"
#include <string>

namespace util
{

//serial_communication�̎�M���荞�݂ɓo�^���Ďg��
//���͂��ꂽ�����񂪍s���ƂɃL���[�ɒ~������
//execute���Ă΂��Ɠo�^���ꂽ�R�}���h�ɓn����āAmatch�Ȃ�execute�����
class command_manager : public serial_communication_receiver_base
{
    private:
    static const char _separator = ' ';
    list<command_base*> _command_list;
    list<string> _queue;
    string _line;
    
    private:
    void echo_back(serial_communication& s, char c) const;
    void parse_command(serial_communication& s, const string& line);
    bool add_received_character(char c);
    void remove_one_character();
    void clear_received_character() { _line.erase(); }
    
    public:
    command_manager() : _line("") { }
    void register_command(const command_base& command) { _command_list.push_back((command_base*)&command); }
    void show_command_request_character(const serial_communication& s) { s.putc('>'); }
    
    //�V���A���ʐM�N���X����Ă΂�܂�
    virtual void on_received(serial_communication& s, char c);
    
    //���C�����[�v���炱�̃��\�b�h���Ăяo���Ă�������
    void execute(serial_communication& s);
};

}