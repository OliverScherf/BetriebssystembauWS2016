/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                            K E Y B O A R D                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Tastaturtreiber.                                                          */
/*****************************************************************************/

/* Hier muesst ihr selbst Code vervollstaendigen */
/* Hier muesst ihr selbst Code vervollstaendigen */
#include "device/keyboard.h"

using namespace cga_sm;

void Keyboard::plugin()
{
  plugbox.assign(plugbox.KEYBOARD, *this);
  pic.allow(pic.keyboard);
}


/* Mit dieser Methode wird auf die Unterbrechungen durch die Tastatur reagiert.
 * Da bei jedem Tastendruck mehrere Unterbrechungen ausgelöst werden,
 * ist nicht in jedem Fall mit einem verwertbaren ASCII-Code zu rechnen.
 * Nur wenn die Methode key_hit der Basisklasse Keyboard_Controller einen
 * gültigen Key liefert, konnte ein vollständiger Scancode ermittelt werden.
 * Für "normale" Tasten existiert dann auch ein ASCII-Code ungleich Null.
 * Falls Ctrl-Alt-Delete gedrückt wurde, soll ein Reboot ausgelöst werden.
 * Außerdem soll die Ausführung eines Epilogs angefordert werden. */
bool Keyboard::prologue()
{
  triggered_key = key_hit();
  if (triggered_key.valid())
    buffer = triggered_key;
  return triggered_key.valid(); // if key invalid
}

/* Hier wird das im Rahmen der Prolog-Behandlung ausgelesene Zeichen auf
 * dem Bildschirm mit Hilfe des globalen CGA_Stream Objekts kout ausgegeben.*/
void Keyboard::epilogue ()
{
    if (triggered_key.ctrl())
        if(triggered_key.alt())
          if (triggered_key.scancode() == Key::scan::del)
            reboot();
    semaphore.signal();
}

Key Keyboard::getkey()
{
    semaphore.wait();
    //kout << triggered_key << endl;
    return buffer;
}
