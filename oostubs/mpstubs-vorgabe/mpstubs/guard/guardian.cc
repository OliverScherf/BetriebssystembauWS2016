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

#include "machine/plugbox.h"
#include "machine/smpsys.h"
#include "machine/lapic.h"
#include "object/debug.h"
extern Plugbox plugbox;

//#include "guard/guard.h"        
//extern Guard guard;



/* FUNKTIONEN */
               
extern "C" void guardian (unsigned int slot);

/* GUARDIAN: Low-Level Interrupt-Behandlung. Die Funktion wird spaeter noch */
/*           erweitert.                                                     */

void guardian (unsigned int slot)
 {

  LOCK
  DBG << "IRQ " << slot << " on CPU " << (int) smp.getCPUID() << endl;
  UNLOCK

  Gate* gate;
         
  gate = &(plugbox.report (slot));
  gate->prologue();
  lapic.ackIRQ();

//  bool wantsEpilogue = gate->prologue();
//  if (wantsEpilogue) {
//    guard.relay (gate);
//  }
 }
