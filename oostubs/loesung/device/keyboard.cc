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

void Keyboard::plugin()
{
  plugbox.assign(plugbox.KEYBOARD, this);
  pic.allow(pic.keyboard);
}

void Keyboard::trigger()
{

}
