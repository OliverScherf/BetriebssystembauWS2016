/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                 P A N I C                                 */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Standard Unterbrechungsbehandlung.                                        */
/*****************************************************************************/

#ifndef __panic_include__
#define __panic_include__

/* INCLUDES */

#include "guard/gate.h"
#include "device/cgastr.h"

using namespace globals;
using namespace cga_sm;

class Panic : public Gate
/* Hier muesst ihr selbst Code vervollstaendigen */         
{
private:
    Panic (const Panic &copy); // Verhindere Kopieren
public:
    Panic () {}
    void trigger();
/* Hier muesst ihr selbst Code vervollstaendigen */                  
          
};

#endif

