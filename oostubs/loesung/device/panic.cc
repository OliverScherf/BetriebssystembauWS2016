/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                 P A N I C                                 */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Standard Unterbrechungsbehandlung.                                        */
/*****************************************************************************/
/* Hier muesst ihr selbst Code vervollstaendigen */
/* Hier muesst ihr selbst Code vervollstaendigen */

#include "device/panic.h"

using namespace cga_sm;

// void Panic::trigger()
// {

// }

bool Panic::prologue()
{
	kout << "Error: Kernel Panic!" << endl;
	cpu.halt();
	return false;
}
