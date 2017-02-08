/* $Id: main.cc 956 2008-10-19 22:24:23Z hsc $ */
#include "user/appl.h"
#include "machine/cpu.h"
#include "device/cgastr.h"
#include "machine/plugbox.h"
#include "device/panic.h"
#include "syscall/guarded_keyboard.h"
#include "machine/pic.h"
#include "syscall/guarded_organizer.h"
#include "device/watch.h"
#include "guard/guard.h"
#include "syscall/guarded_semaphore.h"
#include "meeting/bellringer.h"
#include "syscall/guarded_buzzer.h"


using namespace cga_sm;

cga_sm::CGA_Stream cga_sm::kout;
CPU cpu;
Plugbox plugbox;
Panic panic;
PIC pic;
Guarded_Keyboard keyboard;
Guarded_Organizer scheduler;
Watch cpu_watch(1000); //max: 53000
Guard guard;
Bellringer bellringer;


Guarded_Semaphore sem(1);

Guarded_Buzzer buzzer;


Application app1(5, 20, &sem, &buzzer);
Application app2(5, 21, &sem, &buzzer);
Application app3(5, 22, &sem, &buzzer);
Application app4(5, 23, &sem, &buzzer);


int main()
{
    keyboard.plugin();
    scheduler.ready(app1);
    scheduler.ready(app2);
    scheduler.ready(app3);
    scheduler.ready(app4);

    guard.enter();

    cpu_watch.windup();
    cpu.enable_int();
    scheduler.Scheduler::schedule();

    return 0;
 }
