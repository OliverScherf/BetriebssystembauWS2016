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
  void* tos2 = &stack + STACK_SIZE - 400;
  void* tos3 = &stack + STACK_SIZE - 800;


  Application app(tos, 20, 20);
  Application app2(tos2, 20, 21);
  Application app3(tos3, 20, 22);

  scheduler.ready(app);
  scheduler.ready(app2);
  scheduler.ready(app3);


  kout << "Apps ready" << endl;
  scheduler.schedule();
  //app.action();
  return 0;
 }
