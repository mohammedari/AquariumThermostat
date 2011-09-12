#pragma once
#include "command_base.hpp"
#include "serial_communication_receiver_base.hpp"
#include "linked_list.hpp"
#include <string>

using namespace util;

namespace tank_controller
{

//serial_communicationの受信割り込みに登録して使う
//入力された文字列が登録されたコマンドに渡されて、matchならexecuteされる
class command_manager : private serial_communication_receiver_base
{
    private:
    static const char _new_line = (char)0x0D;
    static const char _separator = ' ';
    linked_list<command_base> _command_list;
    string _line;
    
    private:
    void parse_command(string& line);
    void add_received_character(char c) { _line += c; }
    void clear_received_character() { _line.erase(); }
    
    public:
    command_manager() : _line("") { }
    void register_command(command_base& command);
    void on_received(char c);
};

}