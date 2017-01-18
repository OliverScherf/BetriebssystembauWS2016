/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                   G U A R D E D _ S E M A P H O R E                       */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Systemaufrufschnittstelle zum Semaphor.                                   */
/*****************************************************************************/

/* Hier muesst ihr selbst Code vervollstaendigen */ 

#include "syscall/guarded_semaphore.h"

void Guarded_Semaphore::wait()
{
	Secure sec;
	Semaphore::wait();
}

void Guarded_Semaphore::signal()
{
	Secure sec;
	Semaphore::signal();
}
