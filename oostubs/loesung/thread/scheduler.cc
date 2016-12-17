/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          S C H E D U L E R                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Implementierung des Schedulers.                                           */
/*****************************************************************************/

#include "thread/scheduler.h"

using namespace cga_sm;
using namespace globals;

void Scheduler::ready(Entrant& that)
{
    readyList.enqueue(&that);
}

void Scheduler::schedule()
{
  	Entrant* next = (Entrant*)readyList.dequeue();
  	go(*next);	
}

void Scheduler::exit()
{
    Entrant* current = (Entrant*) readyList.dequeue();
    current->action();
}

void Scheduler::kill(Entrant& that)
{
    readyList.remove(&that);
}

void Scheduler::resume()
{
	Entrant* next = (Entrant*)readyList.dequeue();
    readyList.enqueue((Entrant*) active());
    dispatch(*next);
}
