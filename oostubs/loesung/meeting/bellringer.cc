/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          B E L L R I N G E R                              */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Der "Gloeckner" wird im Rahmen der Timer-Epilog Bearbeitung aktiviert.    */
/* Er prueft, ob irgendwelche Glocken (Bell-Objekte) laeuten muessen. Die    */
/* Glocken befinden sich in einer Queue, die der Gloeckner verwaltet.        */
/*****************************************************************************/

/* Hier muesst ihr selbst Code vervollstaendigen */

#include "meeting/bellringer.h"

void Bellringer::check()
{
    Bell* item = (Bell*)first();
    while(item)
    {
        item->tick();
        if(item->run_down())
        {
            kout << "check!!" << endl;
            remove(item);
            kout << "check2!!" << endl;
            item->ring();
        }
        item = (Bell*)item->next;
    }

}

void Bellringer::job(Bell* bell, int ticks)
{
    bell->wait(ticks);
    enqueue(bell);
}

void Bellringer::cancel(Bell* bell)
{
    remove(bell);
}
