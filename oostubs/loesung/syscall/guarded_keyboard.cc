/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                   G U A R D E D _ K E Y B O A R D                         */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Systemaufrufschnittstelle zur Tastatur.                                   */
/*****************************************************************************/

/* Hier muesst ihr selbst Code vervollstaendigen */

#include "syscall/guarded_keyboard.h"

Key Guarded_Keyboard::getkey()
{
    Secure secure;
    return Keyboard::getkey();
}
