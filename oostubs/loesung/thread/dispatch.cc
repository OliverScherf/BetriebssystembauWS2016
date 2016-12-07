/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          D I S P A T C H E R                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Implementierung des Dispatcher.                                           */
/* Der Dispatcher verwaltet den life-Pointer, der die jeweils aktive         */
/* Koroutine angibt. mit go() wird der life Pointer initialisiert und die    */
/* erste Koroutine gestartet, alle weiteren Kontextwechsel werden mit        */
/* dispatch() ausgeloest. active() liefert den life Pointer zurueck.         */
/*****************************************************************************/

/* Hier muesst ihr selbst Code vervollstaendigen */

#include "thread/dispatch.h"

Dispatcher::Dispatcher()
{
    live = 0;
}

void Dispatcher::go(Coroutine& first)
{
    live = &first;
    live->go();
}

void Dispatcher::dispatch(Coroutine& next)
{
    live->resume(next);
    live = &next;
}

Coroutine* Dispatcher::active()
{
    return live;
}
