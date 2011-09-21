#pragma once

#include "iodefine.h"
#include "lcd.hpp"
#include "tank_state.hpp"

namespace tank_controller
{
	
class display : public util::lcd
{
	private:
	static bool _initialized;
	
	public:
	display();
	void update(const tank_state& state);
	
	protected:
	virtual void set_register_select(bool bit) { IO.PDR1.BIT.B1 = bit ? 1 : 0; }
	virtual void set_read_write(bool bit) { IO.PDR1.BIT.B0 = bit ? 1 : 0; }
	virtual void set_enable(bool bit) { IO.PDR1.BIT.B2 = bit ? 1 : 0; }
	virtual void set_b4(bool bit) { IO.PDR5.BIT.B3 = bit ? 1 : 0; }
	virtual void set_b5(bool bit) { IO.PDR5.BIT.B2 = bit ? 1 : 0; }
	virtual void set_b6(bool bit) { IO.PDR5.BIT.B1 = bit ? 1 : 0; }
	virtual void set_b7(bool bit) { IO.PDR5.BIT.B0 = bit ? 1 : 0; }
};
	
}