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
#include "syscall/thread.h"
#include "globals.h"

class Application : public Thread
{

private:
    Application (const Application &copy); // Verhindere Kopieren
    int x;
    int y;
    int current_symbol;
public:
    Application (void* tos, int x, int y) : Thread(tos), x(x), y(y) { current_symbol = 0; }
    const char* RUN_SYMBOLS = "-/*\\";
    const int NUM_RUN_SYMBOLS = 4;
    Application();
    void action ();
 };

#endif
