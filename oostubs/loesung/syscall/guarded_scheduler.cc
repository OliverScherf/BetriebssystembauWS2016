/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                    G U A R D E D _ S C H E D U L E R                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Systemaufrufschnittstelle zum Scheduler.                                  */
/*****************************************************************************/

#include "syscall/guarded_scheduler.h"

void Guarded_Scheduler::ready(Thread& that)
{
	Secure sec;
	Scheduler::ready(that);
}

void Guarded_Scheduler::exit()
{
	Secure sec;
	Scheduler::exit();
}

void Guarded_Scheduler::kill(Thread& that)
{
	Secure sec;
	Scheduler::kill(that);
}

void Guarded_Scheduler::resume()
{
	Secure sec;
	Scheduler::resume();
}
