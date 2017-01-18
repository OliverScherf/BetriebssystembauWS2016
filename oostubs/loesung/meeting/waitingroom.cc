/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                        W A I T I N G R O O M                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Liste von Threads, die auf ein Ereignis warten.                           */
/*****************************************************************************/

/* Hier muesst ihr selbst Code vervollstaendigen */ 

#include "meeting/waitingroom.h"

Waitingroom::~Waitingroom()
{
	kout << "Destruct Waitingroom" << endl;
	Customer* elem = (Customer*) this->dequeue();
	while (elem != 0)
	{
		elem->waiting_in(0x00);
		elem = (Customer*) this->dequeue();
	}
}

void Waitingroom::remove(Customer* customer)
{
	this->remove(customer);
}
