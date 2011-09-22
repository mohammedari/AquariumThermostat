/***********************************************************************/
/*                                                                     */
/*  FILE        :TankController.cpp                                    */
/*  DATE        :Mon, Sep 05, 2011                                     */
/*  DESCRIPTION :Main Program                                          */
/*  CPU TYPE    :H8/3694F                                              */
/*                                                                     */
/*  This file is generated by Renesas Project Generator (Ver.4.16).    */
/*                                                                     */
/***********************************************************************/

#include "suicide.hpp"
#include "serial_communication.hpp"
#include "command_manager.hpp"
#include "commands.hpp"
#include "display.hpp"
#include <string>

#include "alert.hpp"

using namespace util;
using namespace tank_controller;
using namespace tank_controller::commands;

void main(void);
#ifdef __cplusplus
extern "C" {
void abort(void);
}
#endif

void main(void)
{  
    serial_communication s;
    command_manager cm;
    help_command hc;
    default_command dc;
    
    s.register_receiver(cm);
    cm.register_command(hc);
    cm.register_command(dc); 
        
    s.write_line(string("Hello! Please enter a command."));
    cm.show_command_request_character(s);
    
    display d;
    d.write_line(0, string("Hello!"));
    
    while(true);
}

#ifdef __cplusplus
void abort(void)
{
    suicide();
}
#endif
