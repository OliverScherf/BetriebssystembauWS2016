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

using namespace globals;
using namespace cga_sm;

Keyboard::Keyboard()
{

}

void Keyboard::plugin()
{
  plugbox.assign(plugbox.KEYBOARD, *this);
  pic.allow(pic.keyboard);
}

void Keyboard::trigger()
{
    Key triggered_key = key_hit();
    if (!triggered_key.valid()) // if key invalid
      return;

    if (triggered_key.ctrl())
      if(triggered_key.alt())
        if (triggered_key.scancode() == Key::scan::del)
          reboot();

    // TEST FOR PART B!
    kout.setpos(20, 10);
    kout << triggered_key;
    kout.flush();
}
