/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                  P I T                                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Programmable Interval Timer.                                              */
/*****************************************************************************/

#ifndef __pit_include__
#define __pit_include__

#include "io_port.h"

class PIT
 {
private:
    PIT(const PIT &copy); // Verhindere Kopieren
    int inter;
    IO_Port pit1_ctrl;
    IO_Port pit1_count0;

/* Hier muesst ihr selbst Code vervollstaendigen */ 
public:
    PIT (int us);
    int interval ();
    void interval (int us);
};

#endif
