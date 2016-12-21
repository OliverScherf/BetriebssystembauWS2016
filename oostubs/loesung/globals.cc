#include "globals.h"

// Define global variables.
cga_sm::CGA_Stream cga_sm::kout;
CPU globals::cpu;
Plugbox globals::plugbox;
Panic globals::panic;
PIC globals::pic;
Keyboard globals::keyboard;
Guarded_Scheduler globals::scheduler;
Watch globals::cpu_watch(1000000);
