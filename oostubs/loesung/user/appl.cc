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

/* Hier muesst ihr selbst Code vervollstaendigen */

using namespace cga_sm;
using namespace globals;
/* GLOBALE VARIABLEN */

/* Hier muesst ihr selbst Code vervollstaendigen */

void Application::action ()
 {
	while(true)
  	{
  		{
  			count++;
  			Secure secure;
		    kout.setpos(x, y);
		    kout << "Application!!!" << count;
		    for (int i = 0; i < 100000; ++i);
		    kout.flush();
  		}
  		scheduler.resume();
	}
 }
