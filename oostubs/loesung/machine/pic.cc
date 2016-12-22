/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                                  P I C                                    */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Programmable Interrupt Controller.                                        */
/* Mit Hilfe des PICs koennen Hardware-Unterbrechungen einzeln zugelassen    */
/* oder unterdrueckt werden. Auf diese Weise wird also bestimmt, ob die      */
/* Unterbrechung eines Geraetes ueberhaupt an den Prozessor weitergegeben    */
/* wird. Selbst dann erfolgt eine Aktivierung der Unterbrechungsroutine nur, */
/* wenn der Prozessor bereit ist, auf Unterbrechungen zu reagieren. Dies     */
/* kann mit Hilfe der Klasse CPU festgelegt werden.                          */
/*****************************************************************************/

/** ACCESS PORTS ON PIC!
* Port 0x21 / 0xa1 ->     interrupt mask register (IRM) -> suppresses
*                         selective Interrupts
* Port 0x20 / 0xa0 ->     interrupt request register (IRR) -> PIC saves interrut
*                             requests
*                         interrupt service register (ISR) -> if there is more
*                             than one interrupt PIC should forward the most
*                             important. PIC sends INT to CPU and CPU needs to
*                             answer with 2 INTA (interrupt accept). After
*                             receiving 2 INTA signals the PIC sends the interrupt
*                             number on D0-D7. Additionally the corresponding bit
*                             in ISR is set. Bit is removed from IRR. Whenever a
*                             new interrupt is received PIC can decide with the
*                             ISR if the new interrupt is more important than the
*                             old one. If so, a new INT is send to the CPU.
*                         Interrupt vector (Int.Vek) -> contains the routine which
*                             should be called for the specified interrupt.
*                             guardian() is called with this information
*                             afterwards.
**/

#include "machine/pic.h"

PIC::PIC() : imr_low(0x21) , imr_high(0xa1)
{
    cpu.enable_int(); //enable interrupts on the cpu
}

void PIC::allow(int interrupt_device)
{
	char buffer;
	//read current state of 0x21
	buffer = imr_low.inb();
	//the interrupt_device bit needs to be set to 0 in order to activate interrupt
    imr_low.outb(buffer & ~(1 << interrupt_device));
}


void PIC::forbid(int interrupt_device)
{
	char buffer;
	//read current state of 0x21
	buffer = imr_low.inb();
	//the interrupt_device bit needs to be set to 1 in order to deactivate interrupt
    imr_low.outb(buffer | (1 << interrupt_device));
}
