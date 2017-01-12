/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                               L O C K E R                                 */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die Klasse Locker implementiert eine Sperrvariable, die verwendet wird,   */
/* um kritische Abschnitte zu schuetzen. Die Variable zeigt allerdings nur   */
/* an, ob der kritische Abschnitt frei ist. Ein eventuelles Warten und der   */
/* Schutz der fuer diese Klasse notwendigen Zaehlfunktion muss ausserhalb    */
/* erfolgen.                                                                 */
/*****************************************************************************/

#ifndef __Locker_include__
#define __Locker_include__

#include "machine/cpu.h"
#include "device/cgastr.h"

extern CPU cpu;
extern cga_sm::CGA_Stream cga_sm::kout;

class Locker
{
private:
	Locker(const Locker &copy); // Verhindere Kopieren
	volatile bool locked;
	int enterc;
	int retnec;
public:
	Locker () { locked = false; enterc = 0; retnec = 0;}
	inline void enter()
	{
		// enterc++;
		// cga_sm::kout.setpos(50,10);
		// cga_sm::kout << "e: " << enterc << cga_sm::endl;
		if(locked)
		{
			cga_sm::kout << "Enter error" << cga_sm::endl;
			cpu.halt();
		}
		locked = true;

	}
	inline void retne()
	{
		// retnec++;
		// cga_sm::kout.setpos(50,11);
		// cga_sm::kout << "r: " << retnec << cga_sm::endl;
		if(!locked)
		{
			cga_sm::kout << "retne error" << cga_sm::endl;
			cpu.halt();
		}
		locked = false;
	}
	inline bool avail(){ return !locked; }

};

#endif
