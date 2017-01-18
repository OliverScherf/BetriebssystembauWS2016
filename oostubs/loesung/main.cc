/* $Id: main.cc 956 2008-10-19 22:24:23Z hsc $ */
#include "user/appl.h"
#include "machine/cpu.h"
#include "device/cgastr.h"
#include "machine/plugbox.h"
#include "device/panic.h"
#include "device/keyboard.h"
#include "machine/pic.h"
#include "syscall/guarded_organizer.h"
#include "device/watch.h"
#include "guard/guard.h"
#include "syscall/guarded_semaphore.h"

using namespace cga_sm;

cga_sm::CGA_Stream cga_sm::kout;
CPU cpu;
Plugbox plugbox;
Panic panic;
PIC pic;
Keyboard keyboard;
Guarded_Organizer scheduler;
Watch cpu_watch(1000); //max: 53000
Guard guard;

Guarded_Semaphore sem(1);

Application app(5, 20, &sem);
Application app2(5, 21, &sem);
Application app3(5, 22, &sem);


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
