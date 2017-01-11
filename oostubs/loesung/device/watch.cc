/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              W A T C H                                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/*****************************************************************************/

#include "device/watch.h"

// WINDUP: "zieht die Uhr auf". Danach laeuft sie los und loest in
//         regelmaessigen Abstaenden Unterbrechungen aus.
void Watch::windup()
{
	  plugbox.assign(plugbox.TIMER, *this);
	  pic.allow(pic.timer);
}

// PROLOGUE: Prologue der Uhrenunterbrechung
bool Watch::prologue()
{
	return true;
}

// EPILOGUE: Epilogue der Uhrenunterbrechung
void Watch::epilogue()
{
	cga_sm::kout << "scheduler.resume()" << cga_sm::endl;
	scheduler.resume();
}
