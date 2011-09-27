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
#include "eeprom.hpp"
#include "rtc.hpp"
#include "thermometer.hpp"
#include "watch_dog.hpp"
#include "heater.hpp"
#include "cooler.hpp"
#include "light.hpp"
#include "tank_status.hpp"
#include "wait.hpp"
#include <string>

using namespace util;
using namespace tank_controller;
using namespace tank_controller::commands;

void main(void);
#ifdef __cplusplus
extern "C" {
void abort(void);
}
#endif

void measure(tank_status& status, const rtc& clock, const thermometer& thermo)
{
    status.current_time = clock.get();
	status.current_temperature = thermo.measure();
}

void main(void)
{   
	//SSR
	heater h;
	cooler c;
	light l;
	
    //ウォッチドッグ
    watch_dog dog;
	
    //温度計
	thermometer thermo;
    
    //EEPROMとRTC
    i2c& i = i2c::get_instance();
    eeprom rom(i);
    rtc clock(i);
    
    //水槽の状態
    tank_status status(dog.is_error_occured_in_previous_execution());
	measure(status, clock, thermo);
    
    //LCD
    //display d;
    //d.write_line(0, string("Hello!"));
    
    //シリアル通信とコマンド管理
    serial_communication& s = serial_communication::get_instance();
    command_manager cm;
    
    get_command gc(status);
    help_command hc;
    default_command dc;
    
    s.register_receiver(cm);
    cm.register_command(gc);
    cm.register_command(hc);
    cm.register_command(dc); 
    
    //初期化完了
    s.write_line(string("Hello! Please enter a command."));
    cm.show_command_request_character(s);
    
    while(true)
    {
		dog.watch();
        s.write_line("loop");
        
        //状態の更新
		measure(status, clock, thermo);
		
		//SSRの切り替え
		status.update_switches();
		status.is_heater_on() ? h.on() : h.off();
		status.is_cooler_on() ? c.on() : c.off();
		status.is_light_on() ? l.on() : l.off();
		
        wait(500);
    }
    
    serial_communication::delete_instance();
    i2c::delete_instance();
}

#ifdef __cplusplus
void abort(void)
{
    suicide();
}
#endif
