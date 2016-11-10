#ifndef __globals_include__
#define __globals_include__

#include "machine/cpu.h"
#include "device/cgastr.h"
#include "machine/plugbox.h"
#include "device/panic.h"

// forward declaration
class Panic;
class Plugbox;

namespace globals
{
		extern Plugbox plugbox;
    extern CPU cpu;
		extern Panic panic;
}

#endif
