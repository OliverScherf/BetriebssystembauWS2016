/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                G U A R D                                  */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Mit Hilfe dieser Klasse koennen Aktivitaeten, die einen kritischen        */
/* Abschnitt betreffen, der mit einem Guard-Objekt geschuetzt ist, mit       */
/* Unterbrechungsbehandlungsroutinen synchronisiert werden, die ebenfalls    */
/* auf den kritischen Abschnitt zugreifen.                                   */
/*****************************************************************************/


#include "guard/guard.h"

void Guard::leave()
{
	while(true)
	{
		cpu.disable_int();
		Gate* current = (Gate*)queue.dequeue();

		if(current == 0)
			break;

		current->queued(false);
		cpu.enable_int();
		current->epilogue();
	}
	retne();
	cpu.enable_int();

}

void Guard::relay(Gate* item)
{
	// int x,y;
    // cga_sm::kout.getpos(x, y);
	// cga_sm::kout.setpos(1,1);
	// cga_sm::kout << item->queued() << cga_sm::endl;
	// cga_sm::kout.setpos(x,y);
	if(!(item->queued()))
	{
		// queued++;
		// cga_sm::kout.setpos(40,10);
		// cga_sm::kout << "enqueued, count: " << queued << cga_sm::endl;
		queue.enqueue(item);
		item->queued(true);
	}
}
