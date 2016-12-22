/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                         A P P L I C A T I O N                             */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die Klasse Application definiert die einzige Anwendung von OO-Stubs.      */
/*****************************************************************************/

/* INCLUDES */

#include "user/appl.h"

using namespace cga_sm;
/* GLOBALE VARIABLEN */

void Application::action() {
	while (true)
	{
		current_symbol = (current_symbol + 1) % NUM_RUN_SYMBOLS;
		{
			Secure secure;
			kout.setpos(x, y);
			kout << "Applicationat y : " << y << " is running: "
					<< RUN_SYMBOLS[current_symbol];
			kout.flush();
		}
	}
}
