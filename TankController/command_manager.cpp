#include <string>
#include "iodefine.h"
#include "command_manager.hpp"
#include "list.hpp"
#include "command_base.hpp"
#include "wait.hpp"
#include "serial_communication.hpp"
#include "stddef.h"
#include "split_string.hpp"

namespace util
{

void command_manager::parse_command(serial_communication& s, const string& line)
{
    string command_str, parameter_str;
    split_string(line, _separator, command_str, parameter_str);

    for(list<command_base*>::iterator i = _command_list.begin(); i != _command_list.end(); ++i)
        if((*i)->is_match(command_str))
        {
            (*i)->execute(s, parameter_str);
            break;
        }
}

bool command_manager::add_received_character(char c)
{
    //����������ǂݎ̂�
    if(_line.size() + 1 > _line.max_size())
        return false;

    _line += c;
    return true;
}

void command_manager::remove_one_character()
{
    size_t s = _line.size();
    if(0 < s)
        _line.resize(s - 1);
}

void command_manager::on_received(serial_communication& s, char c)
{    
    if(!serial_communication::is_control_character(c))
    {
        if(add_received_character(c))
            s.putc(c);
            
        return;
    }
    
    //����R�[�h��M
    if(serial_communication::is_new_line(c))
    {
        s.putc(c);
        _queue.push_back(_line);
        clear_received_character();
    }
    else if(serial_communication::is_back_space(c))
    {
        if(0 < _line.size())
        {
            remove_one_character();
            s.putc(c); s.putc(' '); s.putc(c);  //�߂��ď㏑�����Ė߂�
        }
    }
}

void command_manager::execute(serial_communication& s)
{
    while(!_queue.empty())
    {
        parse_command(s, _queue.front());
        show_command_request_character(s);
        _queue.pop_front();
    }
}
    
}
