#pragma once
#include "command_base.hpp"
#include "serial_communication.hpp"
#include "serial_communication_receiver_base.hpp"
#include "linked_list.hpp"
#include <string>

namespace util
{

//serial_communication‚ÌóMŠ„‚è‚İ‚É“o˜^‚µ‚Äg‚¤
//“ü—Í‚³‚ê‚½•¶š—ñ‚ª“o˜^‚³‚ê‚½ƒRƒ}ƒ“ƒh‚É“n‚³‚ê‚ÄAmatch‚È‚çexecute‚³‚ê‚é
class command_manager : public serial_communication_receiver_base
{
    private:
    static const char _separator = ' ';
    linked_list<command_base*> _command_list;
    string _line;
    
    private:
    void echo_back(serial_communication& s, char c) const;
    void parse_command(serial_communication& s, const string& line);
    bool add_received_character(char c);
    void remove_one_character();
    void clear_received_character() { _line.erase(); }
    
    public:
    command_manager() : _line("") { }
    void register_command(const command_base& command) { _command_list.add((command_base*)&command); }
    void show_command_request_character(const serial_communication& s) { s.putc('>'); }
    virtual void on_received(serial_communication& s, char c);		
};

}