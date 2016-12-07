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

void Scheduler::ready(Entrant& that)
{
    readyList.enqueue(&that);
}

void Scheduler::schedule()
{
    Entrant* next = (Entrant*)readyList.dequeue();
    readyList.enqueue((Entrant*)next);
    dispatch(*next);
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
    readyList.enqueue((Entrant*)active());
    schedule();
}
