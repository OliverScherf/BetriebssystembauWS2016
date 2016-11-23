/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                  G A T E                                  */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Klasse von Objekten, die in der Lage sind, Unterbrechungen zu behandeln.  */
/*****************************************************************************/

#ifndef __Gate_include__
#define __Gate_include__

#include "object/chain.h"

/* Hier muesst ihr selbst Code vervollstaendigen */
class Gate : public Chain
{
private:
	bool isQueued;

public:
//	virtual void trigger() = 0;
	virtual void epilogue() {};
	virtual bool prologue() = 0;

	void queued(bool q)
	{
		isQueued = q;
	}
	bool queued()
	{
		return isQueued;
	}
};


#endif
