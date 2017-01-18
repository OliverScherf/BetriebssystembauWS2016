/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                           S E M A P H O R E                               */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Semaphore werden zur Synchronisation von Threads verwendet.               */
/*****************************************************************************/

#ifndef __Semaphore_include__
#define __Semaphore_include__

        
#include "meeting/waitingroom.h"
#include "syscall/guarded_organizer.h"
#include "thread/customer.h"

extern Guarded_Organizer scheduler;

class Semaphore : public Waitingroom
 {
private:
    Semaphore (const Semaphore &copy); // Verhindere Kopieren
    const int max_counter;
    volatile int counter;
    void p ();
    void v ();
public:
    Semaphore (int c) : max_counter(c), counter(c) {};
    void wait ();
    void signal ();
 };

#endif
