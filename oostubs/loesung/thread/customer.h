/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                         C U S T O M E R                                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Ein Thread, der auf ein Ereignis warten kann.                             */
/*****************************************************************************/

#ifndef __customer_include__
#define __customer_include__

#include "thread/entrant.h"
#include "meeting/waitingroom.h"

class Waitingroom;

class Customer : public Entrant
 {
private:
    Customer (const Customer &copy); // Verhindere Kopieren
    Waitingroom *waitingroom;
public:
    Customer(void* tos) : Entrant(tos)
	{
    	waitingroom = 0x00;
    }
    void waiting_in(Waitingroom *w)
    {
    	waitingroom = w;
    }

    Waitingroom* waiting_in()
    {
   		return waitingroom;
    }

 };


#endif
