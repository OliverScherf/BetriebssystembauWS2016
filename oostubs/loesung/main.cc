/* $Id: main.cc 956 2008-10-19 22:24:23Z hsc $ */
#include "globals.h"
#include "device/cgastr.h"
#include "user/appl.h"

/* Hier muesst ihr selbst Code vervollstaendigen */

using namespace cga_sm;
using namespace globals;

int main()
{

  keyboard.plugin();
  // //pic.allow(pic.timer); /* Handler not implemented, Kernel panic ;-) */
  const int STACK_SIZE = 1024;
  char stack[STACK_SIZE];

  void* tos  = &stack + STACK_SIZE - 1;
  void* tos2 = &stack + STACK_SIZE - 33;
  void* tos3 = &stack + STACK_SIZE - 65;
  void* tos4 = &stack + STACK_SIZE - 97;
  void* tos5 = &stack + STACK_SIZE - 129;

  Application app(tos, 20, 4);
  Application app2(tos2, 20, 5);
  Application app3(tos3, 20, 6);
  Application app4(tos4, 20, 7);
  Application app5(tos5, 20, 8);


  kout << "App created" << endl;

  scheduler.ready(app);
  scheduler.ready(app2);
  scheduler.ready(app3);
  scheduler.ready(app4);
  scheduler.ready(app5);


  kout << "App ready" << endl;
  scheduler.schedule();
  //app.action();
  return 0;
 }
