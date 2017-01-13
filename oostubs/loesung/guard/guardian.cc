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
#include "guard/secure.h"
#include "machine/plugbox.h"

using namespace cga_sm;

extern "C" void guardian (unsigned int slot);

extern Guard guard;
extern Plugbox plugbox;

/* GUARDIAN: Low-Level Interrupt-Behandlung. Die Funktion wird spaeter noch */
/*           erweitert.                                                     */

void guardian (unsigned int slot)
{
	Gate& gate = plugbox.report(slot);
  	if(gate.prologue())
	{
  		if(guard.avail())
  		{
			guard.enter();
	  		cpu.enable_int();
	  		gate.epilogue();
			guard.leave();
  		}
  		else
	  		guard.relay(&plugbox.report(slot));
	}

}
