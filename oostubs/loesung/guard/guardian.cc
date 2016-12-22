/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              G U A R D I A N                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Zentrale Unterbrechungsbehandlungsroutine des Systems.                    */
/* Der Parameter gibt die Nummer des aufgetretenen Interrupts an.            */
/*****************************************************************************/

/* INCLUDES */

/* FUNKTIONEN */
#include "device/cgastr.h"
#include "machine/keyctrl.h"
#include "globals.h"
#include "guard/secure.h"

using namespace cga_sm;
using namespace globals;

extern "C" void guardian (unsigned int slot);

extern Guard guard;

/* GUARDIAN: Low-Level Interrupt-Behandlung. Die Funktion wird spaeter noch */
/*           erweitert.                                                     */

void guardian (unsigned int slot)
{
	// Secure object disables interrupts in constructor
	// after scope is left destructor of secure enables
	// interrupts again
	Gate& gate = plugbox.report(slot);
  	if(gate.prologue())
	{
  		if(guard.avail())
  		{
	  		cpu.enable_int();
	  		gate.epilogue();
  		}
  		else
	  		guard.relay(&plugbox.report(slot));
	}

}
