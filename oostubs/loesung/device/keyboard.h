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
#include "globals.h"

class Keyboard : public Gate, public Keyboard_Controller
{
private:
      Keyboard (const Keyboard &copy); // Verhindere Kopieren
      Key triggered_key;

public:
      Keyboard();
      // PLUGIN: 'Anstoepseln' der Tastatur. Ab sofort werden Tasten erkannt.
      void plugin();
      // void trigger();

      bool prologue();
      void epilogue();
 };

#endif
