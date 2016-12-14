/* $Id: main.cc 956 2008-10-19 22:24:23Z hsc $ */
#include "globals.h"
#include "device/cgastr.h"
#include "user/appl.h"

/* Hier muesst ihr selbst Code vervollstaendigen */

using namespace cga_sm;
using namespace globals;

int main()
{
  // Application app;
  // kout << "Interrupt test!!!";
  // kout.flush();
  keyboard.plugin();
  // //pic.allow(pic.timer); /* Handler not implemented, Kernel panic ;-) */
  // kout.setpos(0, 10);
  // kout << "Keyboard: ";
  // kout.flush();
  // kout.setpos(0, 20);
  // kout << "Application: ";
  // kout.flush();
  //cpu.disable_int();
  void* tos = 0;
  Application app(&tos);
  kout << "App created" << endl;
  scheduler.ready(app);
  kout << "App ready" << endl;
  scheduler.go(app);
  //app.action();
  return 0;
 }
