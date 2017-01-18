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
	scheduler.block(*((Customer*) scheduler.active()), *this);
	counter--;
}

void Semaphore::v()
{
	// man kann ja v() vor p() aufrufen (ist zwar dumm aber kann ein user machen)
	if (counter >= max_counter)
	{
		return;
	}
	counter++;
	scheduler.wakeup(*((Customer*) dequeue()));
}

void Semaphore::wait()
{
	p();
}

void Semaphore::signal()
{
	v();
}
