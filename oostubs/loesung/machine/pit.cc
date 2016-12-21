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

int PIT::interval()
{
	return inter;
}

void PIT::interval(int us)
{
	inter = us;
	pit1_ctrl.outb(0b00101100);
	int interval = (int) us / 0.838;
	int highByte = (interval >> 8) & 0xFF;
	int lowByte  = interval & 0xFF;
	pit1_count0.outb(lowByte);
	pit1_count0.outb(highByte);
}

PIT::PIT (int us) : pit1_ctrl(0x43), pit1_count0(0x40)
{
	interval(us);
}
