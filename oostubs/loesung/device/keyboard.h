/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                            K E Y B O A R D                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Tastaturtreiber.                                                          */
/*****************************************************************************/

#ifndef __Keyboard_include__
#define __Keyboard_include__

#include "machine/keyctrl.h"
#include "guard/gate.h"
#include "machine/key.h"
#include "device/cgastr.h"
#include "machine/plugbox.h"
#include "machine/pic.h"
#include "meeting/semaphore.h"

extern Plugbox plugbox;
extern PIC pic;

class Keyboard : public Gate, public Keyboard_Controller
{
private:
      Keyboard (const Keyboard &copy); // Verhindere Kopieren
      Key triggered_key;
      Semaphore semaphore;
      Key buffer;
public:
      Keyboard() : semaphore(1){ semaphore.wait(); }
      // PLUGIN: 'Anstoepseln' der Tastatur. Ab sofort werden Tasten erkannt.
      void plugin();
      // void trigger();

      bool prologue();
      void epilogue();
      Key getkey();
 };

#endif
