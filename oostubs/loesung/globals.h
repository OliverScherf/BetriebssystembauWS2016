#ifndef __globals_include__
#define __globals_include__

#include "machine/cpu.h"
#include "device/cgastr.h"
#include "machine/plugbox.h"
#include "device/panic.h"
#include "device/keyboard.h"
#include "machine/pic.h"

// forward declaration
class Panic;
class Plugbox;
class Keyboard;
class PIC;

namespace globals
{
		extern Plugbox plugbox;
    extern CPU cpu;
		extern Panic panic;
		extern PIC pic;
		extern Keyboard keyboard;
}

#endif
