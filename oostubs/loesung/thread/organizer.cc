/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          O R G A N I Z E R                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Ein Organizer ist ein spezieller Scheduler, der zusaetzlich das Warten    */
/* von Threads (Customer) auf Ereignisse erlaubt.                            */
/*****************************************************************************/

#include "thread/organizer.h"

void Organizer::block(Customer& customer, Waitingroom& waitingroom) {
	customer.waiting_in(&waitingroom);
	waitingroom.enqueue(&customer);
	Scheduler::kill(customer); // kill entfernt den Prozess aus der ReadyList
	resume();
}

void Organizer::wakeup(Customer& customer) {
	//Waitingroom* w = that.waiting_in();
	/*if (w)
	{
		w->remove(&that);
	}*/
	customer.waiting_in(0x00);
	ready(customer);
}

void Organizer::kill(Customer& that) {
	Waitingroom* w = that.waiting_in();
	if (w)
	{
		w->remove(&that);
	}
	that.waiting_in(0x00);
	Scheduler::kill(that);
}
