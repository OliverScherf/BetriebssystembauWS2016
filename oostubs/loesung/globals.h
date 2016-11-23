#ifndef __globals_include__
#define __globals_include__

#include "machine/cpu.h"
#include "device/cgastr.h"
#include "machine/plugbox.h"
#include "device/panic.h"
#include "device/keyboard.h"
#include "machine/pic.h"
#include "guard/guard.h"

// forward declaration
class Panic;
class Plugbox;
class Keyboard;
class PIC;
class Guard;

namespace globals
{
	extern Plugbox plugbox;
    extern CPU cpu;
	extern Panic panic;
	extern PIC pic;
	extern Keyboard keyboard;
	extern Guard guard;
}

#endif
