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
	cpu.enable_int();
	while(true)
	{
		cpu.disable_int();
		Gate* current = (Gate*)queue.dequeue();

		if(current == 0)
			break;

		cpu.enable_int();
		current->epilogue();
		current->queued(false);

	}
	retne();
	cpu.enable_int();

}

void Guard::relay(Gate* item)
{
	if(!item->queued())
	{
		queue.enqueue(item);
		item->queued(true);
	}
}
