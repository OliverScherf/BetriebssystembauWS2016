/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          S C H E D U L E R                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Implementierung des Schedulers.                                           */
/*****************************************************************************/

#ifndef __schedule_include__
#define __schedule_include__

#include "object/queue.h"
#include "thread/dispatch.h"
#include "thread/entrant.h"
#include "guard/guard.h"
#include "device/cgastr.h"

using namespace cga_sm;

extern cga_sm::CGA_Stream cga_sm::kout;
extern Guard guard;

class Scheduler : public Dispatcher
 {
private:
	Scheduler(const Scheduler &copy); // Verhindere Kopieren
	Queue readyList;
	bool isIdling;
public:
	void ready(Entrant& that);
	void schedule();
	void exit();
	void kill(Entrant& that);
	void resume();
    Scheduler(){ isIdling = false;}
 };

#endif
