/* $Id: main.cc 956 2008-10-19 22:24:23Z hsc $ */
#include "user/appl.h"
#include "machine/cpu.h"
#include "device/cgastr.h"
#include "machine/plugbox.h"
#include "device/panic.h"
#include "device/keyboard.h"
#include "machine/pic.h"
#include "syscall/guarded_scheduler.h"
#include "device/watch.h"
#include "guard/guard.h"

using namespace cga_sm;

cga_sm::CGA_Stream cga_sm::kout;
CPU cpu;
Plugbox plugbox;
Panic panic;
PIC pic;
Keyboard keyboard;
Guarded_Scheduler scheduler;
Watch cpu_watch(1000); //max: 53000
Guard guard;

Application app(5, 20);
Application app2(5, 21);
Application app3(5, 22);


int main()
{
    keyboard.plugin();

    scheduler.ready(app);
    scheduler.ready(app2);
    scheduler.ready(app3);

    guard.enter();

    cpu_watch.windup();
    cpu.enable_int();
    scheduler.Scheduler::schedule();

    return 0;
 }
