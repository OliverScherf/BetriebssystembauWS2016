/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                         A P P L I C A T I O N                             */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die Klasse Application definiert die einzige Anwendung von OO-Stubs.      */
/*****************************************************************************/

#ifndef __application_include__
#define __application_include__

#include "device/cgastr.h"
#include "guard/secure.h"
#include "thread/entrant.h"
#include "globals.h"

class Application : public Entrant
{

private:
    Application (const Application &copy); // Verhindere Kopieren
    int x;
    int y;
    int count;
public:
    Application (void* tos, int x, int y) : Entrant(tos), x(x), y(y) {count = 0;}
    Application();
    void action ();
 };

#endif
