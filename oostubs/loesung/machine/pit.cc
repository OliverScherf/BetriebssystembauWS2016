/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                  P I T                                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Programmable Interval Timer.                                              */
/*****************************************************************************/

#include "pit.h"

using namespace cga_sm;

int PIT::interval()
{
	return inter;
}

void PIT::interval(int us)
{
	inter = us;
	pit1_ctrl.outb(0b00101100);
	kout << "Before timer" << endl;
	float interval_f = us / 0.838f;
	kout << "After float" << endl;
	unsigned int interval = interval_f;
	kout << "After timer" << interval << endl;
	int highByte = (interval >> 8) & 0xFF;
	int lowByte  = interval & 0xFF;
	pit1_count0.outb(lowByte);
	pit1_count0.outb(highByte);
}

PIT::PIT (int us) : pit1_ctrl(0x43), pit1_count0(0x40)
{
	interval(us);
}
