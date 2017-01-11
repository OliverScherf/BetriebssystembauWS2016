#ifndef __kickoff_include__
#define __kickoff_include__

#include "thread/coroutine.h"
#include "guard/guard.h"
#include "device/cgastr.h"

extern Guard guard;
extern cga_sm::CGA_Stream cga_sm::kout;

void kickoff (Coroutine* object);

#endif
