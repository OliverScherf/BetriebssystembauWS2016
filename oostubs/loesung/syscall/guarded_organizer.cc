/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                    G U A R D E D _ O R G A N I Z E R                      */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Systemaufrufschnittstelle zum Organizer.                                  */
/*****************************************************************************/

#include "syscall/guarded_organizer.h"

void Guarded_Organizer::ready(Thread& that)
{
	Secure sec;
	Scheduler::ready(that);
}

void Guarded_Organizer::exit()
{
	Secure sec;
	Scheduler::exit();
}

void Guarded_Organizer::kill(Thread& that)
{
	Secure sec;
	Organizer::kill(that);
}

void Guarded_Organizer::resume()
{
	Secure secure;
	Scheduler::resume();
}
