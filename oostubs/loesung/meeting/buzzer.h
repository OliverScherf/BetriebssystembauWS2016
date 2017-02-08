/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                               B U Z Z E R                                 */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Mit Hilfe des "Weckers" koennen Prozesse eine bestimmte Zeit lang         */
/* schlafen und sich dann wecken lassen.                                     */
/*****************************************************************************/

#ifndef __Buzzer_include__
#define __Buzzer_include__

#include "meeting/bell.h"
#include "meeting/waitingroom.h"
#include "syscall/guarded_organizer.h"
#include "meeting/bellringer.h"
/* Hier muesst ihr selbst Code vervollstaendigen */



extern Guarded_Organizer scheduler;
extern Bellringer bellringer;


class Buzzer : public Bell, public Waitingroom
/* Hier muesst ihr selbst Code vervollstaendigen */
{
private:
    Buzzer(const Buzzer &copy); // Verhindere Kopieren
public:
    Buzzer();
    virtual ~Buzzer();
    virtual void ring();
    void set(int ms);
    void sleep();
};

#endif
