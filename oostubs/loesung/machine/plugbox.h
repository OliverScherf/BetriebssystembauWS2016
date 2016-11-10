/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              P L U G B O X                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Abstraktion einer Interruptvektortabelle. Damit kann man die Adresse der  */
/* Behandlungsroutine fuer jeden Hardware-, Softwareinterrupt und jede       */
/* Prozessorexception festlegen.                                             */
/*****************************************************************************/

#ifndef __Plugbox_include__
#define __Plugbox_include__

#include "guard/gate.h"
#include "device/cgastr.h"
#include "globals.h"

class Plugbox
 {
private:
    Plugbox(const Plugbox &copy); // Verhindere Kopieren
    static const int PLUGBOX_SIZE = 64;
    Gate* gates[PLUGBOX_SIZE];
public:
	Plugbox();
	void assign(unsigned int slot, Gate& gate);
	Gate& report(unsigned int slot);
	const int TIMER = 32;
	const int KEYBOARD = 33;
 };

#endif
