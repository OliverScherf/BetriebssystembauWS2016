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

/* INCLUDES */

#include "meeting/buzzer.h"

Buzzer::Buzzer()
{

}

Buzzer::~Buzzer()
{
    bellringer.cancel(this);
}

void Buzzer::ring()
{
    Customer* customer;
	while ((customer = (Customer*) dequeue()))
    {
		scheduler.Organizer::wakeup(*customer);
	}
}

void Buzzer::set(int ms)
{
	if (wait() <= 0)
		bellringer.job(this, ms);
	else
		wait(ms);
}

void Buzzer::sleep()
{
	scheduler.Organizer::block(*((Customer*) scheduler.active()), *this);

}
