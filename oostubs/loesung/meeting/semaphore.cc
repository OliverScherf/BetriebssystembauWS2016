/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                           S E M A P H O R E                               */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Semaphore werden zur Synchronisation von Threads verwendet.               */
/*****************************************************************************/

/* Hier muesst ihr selbst Code vervollstaendigen */

#include "meeting/semaphore.h"


void Semaphore::p()
{
	if (counter > 0)
	{
		counter--;
		return;
	}
	scheduler.Organizer::block(*((Customer*) scheduler.active()), *this);
	//counter--;
}

void Semaphore::v()
{
	// man kann ja v() vor p() aufrufen (ist zwar dumm aber kann ein user machen)
	if (counter >= max_counter)
	{
		return;
	}
	// counter++;
	Customer* customer = (Customer*) dequeue();
	if (customer != 0) {
		scheduler.Organizer::wakeup(*customer);
	}
	else
	{
		counter++;
		//kout << "waitingroom empty " << counter << endl;
		if (counter == 0)
		{
			kout << "Semaphore counter error!" << counter << endl;
			cpu.halt();
		}
	}
}

void Semaphore::wait()
{
	p();
}

void Semaphore::signal()
{
	v();
}
