/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              P L U G B O X                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Abstraktion einer Interruptvektortabelle. Damit kann man die Behandlungs- */
/* routine fuer jeden Hardware-, Softwareinterrupt und jede Prozessor-       */
/* exception festlegen.                                                      */
/*****************************************************************************/

#include "machine/plugbox.h"

using namespace cga_sm;

Plugbox::Plugbox()
{
	for (int i = 0; i < PLUGBOX_SIZE; ++i)
		gates[i] = &panic;
}

void Plugbox::assign(unsigned int slot, Gate& gate)
{
	gates[slot] = &gate;
}

Gate& Plugbox::report(unsigned int slot)
{
	return *gates[slot];
}
