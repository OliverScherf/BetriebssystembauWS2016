/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                             T H R E A D                                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Benutzerschnittstelle eines Threads.                                      */
/*****************************************************************************/

#ifndef __thread_include__
#define __thread_include__

/* Hier muesst ihr selbst Code vervollstaendigen */ 

#include "thread/entrant.h"

class Thread : public Entrant
 {
private:
      Thread (const Thread &copy); // Verhindere Kopieren
public:
      Thread(void* tos) : Entrant(tos) {}
 };

#endif
