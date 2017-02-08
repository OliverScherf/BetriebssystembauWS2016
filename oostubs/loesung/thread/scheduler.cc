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
  	go(*next);
}


void Scheduler::exit()
{
    Entrant* current;
    while (!(current = (Entrant*) readyList.dequeue())) {
    	//kout << "readylIst was empty" << endl;
    	isIdling = true;
    	guard.leave();
    	cpu.idle();
    	guard.enter();
    }
    isIdling = false;

    //kout << "r12312312312321312323eadylIst was NOT empty" << endl;
    dispatch(*current);
}

void Scheduler::kill(Entrant& that)
{
    readyList.remove(&that);
}

// 1 Anwendung in exit() -> wakeup der selben Anwendung
void Scheduler::resume()
{
	if (isIdling)
		return;

	readyList.enqueue((Entrant*) active());
		Entrant* next = (Entrant*)readyList.dequeue();
		dispatch(*next);
}

