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
/* GLOBALE VARIABLEN */

/* Hier muesst ihr selbst Code vervollstaendigen */

Application::Application()
{

}

void Application::action ()
 {
 	
 	while(true)
  	{
	  	Secure secure;
	    kout.setpos(20, 20);
	    kout << "Application!!!";
	    kout.flush();
	}
 }
