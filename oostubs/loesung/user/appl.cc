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
			count++;
			Key triggered_key;
			if(y == 21)
				triggered_key = keyboard.getkey();

			if (y == 20 || y == 22)
			{
				buzzer->set(100);
				buzzer->sleep();
			}

			semaphore->wait();
			kout.setpos(x, y);
			if(y == 21)
				kout << "Application at y : " << y << " is running: "
					<< RUN_SYMBOLS[current_symbol] << "; Count: " << count
					<< "; Char: \"" << triggered_key << "\""<< endl;
			else
				kout << "Application at y : " << y << " is running: "
				<< RUN_SYMBOLS[current_symbol] << "; Count: " << count
				<< endl;
			//kout << "a" << endl;
			kout.flush();

			semaphore->signal();
		}
	}
}
