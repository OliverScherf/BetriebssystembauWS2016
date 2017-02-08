/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                 B E L L                                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Eine "Glocke" ist eine abstrakte Basisklasse, die das Ausloesen einer     */
/* Aktivitaet nach einer bestimmten Wartezeit erlaubt.                       */
/* Dazu besitzt sie einen Zaehler, der vom "Gloeckner" (Bellringer) ver-     */
/* waltet wird.                                                              */
/*****************************************************************************/

#ifndef __Bell_include__
#define __Bell_include__

#include "object/chain.h"


#include "device/cgastr.h"

/* Hier muesst ihr selbst Code vervollstaendigen */

using namespace cga_sm;

class Bell : public Chain
/* Hier muesst ihr selbst Code vervollstaendigen */
 {
private:
    Bell(const Bell &copy); // Verhindere Kopieren
    int counter;
public:
    inline Bell() { counter = 0; }
    inline void wait(int val) { counter = val; }
    inline int wait() { return counter; }
    inline void tick() { counter--;}
    inline bool run_down() { return counter <= 0; }
    virtual void ring() = 0;
/* Hier muesst ihr selbst Code vervollstaendigen */

};

#endif
