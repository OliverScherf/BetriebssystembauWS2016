#ifndef __DEBUG_H__
#define __DEBUG_H__

#include "device/cgastr.h"
extern CGA_Stream kout;

#include "machine/spinlock.h"
extern Spinlock kout_lock;

#ifdef DEBUG
	#define LOCK \
		/*Interrupts sperren und Zustand speichern*/ \
		{ unsigned int oldflags; \
		asm volatile("pushf\n" \
			     "pop %0\n" \
			     "cli\n" \
			     :"=r" (oldflags)::); \
		/*Spinlock holen*/ \
		kout_lock.lock();

	#define DBG kout << "DEBUG: "

	#define UNLOCK \
		/*Spinlock freigeben*/ \
		kout_lock.unlock(); \
		/*Interrupts erlauben, wenn sie vorher erlaubt waren*/ \
		if ( oldflags & (1<<9) ) \
			asm volatile("sti\n"); }

#else
	#define LOCK
	#define DBG if (false) kout
	#define UNLOCK
#endif

// static assertions
#define ct_assert(e) extern char (*ct_assert(void)) [sizeof(char[1 - 2*!(e)])]

#endif // __DEBUG_H__
