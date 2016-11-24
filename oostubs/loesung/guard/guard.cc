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

using namespace globals;

void Guard::leave()
{	
	cpu.enable_int();
	while(true)
	{
		cpu.disable_int();
		Gate* current = (Gate*)queue.dequeue();
		cpu.enable_int();

		if(current == 0)
			break;

		current->epilogue();
		current->queued(false);
		
	}
	retne();

}

void Guard::relay(Gate* item)
{
	if(!item->queued())
	{
		queue.enqueue(item);
		item->queued(true);
	}
}
		