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
Watch cpu_watch(1000000); //set the timer to 1 second
Guard guard;

int main()
{
    guard.enter();
    keyboard.plugin();

    const int STACK_SIZE = 1024;
    char stack[STACK_SIZE];

    void* tos  = &stack + STACK_SIZE - 1;
    void* tos2 = &stack + STACK_SIZE - 400;
    void* tos3 = &stack + STACK_SIZE - 800;


    Application app(tos, 20, 20);
    Application app2(tos2, 20, 21);
    Application app3(tos3, 20, 22);

    scheduler.ready(app);
    scheduler.ready(app2);
    scheduler.ready(app3);


    kout << "Apps ready" << endl;

    cpu_watch.windup();
    scheduler.schedule();

    return 0;
 }
