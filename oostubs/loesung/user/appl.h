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
#include "syscall/guarded_semaphore.h"
#include "syscall/guarded_keyboard.h"

using namespace cga_sm;

//extern CGA_Stream kout;
extern Guarded_Keyboard keyboard;

class Application : public Thread
{
private:
    Application (const Application &copy); // Verhindere Kopieren
    int x;
    int y;
    int current_symbol;
    static const int STACK_SIZE = 1024;
    char stack[STACK_SIZE];
    int count;
    Guarded_Semaphore* semaphore;
public:
    Application (int x, int y, Guarded_Semaphore* semaphore) : Thread(&stack + STACK_SIZE - 1), x(x), y(y),
															   semaphore(semaphore) { current_symbol = 0; count = 0;}
    const char* RUN_SYMBOLS = "-/*\\";
    const int NUM_RUN_SYMBOLS = 4;
    Application();
    void action ();
 };

#endif
