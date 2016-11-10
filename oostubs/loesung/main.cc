/* $Id: main.cc 956 2008-10-19 22:24:23Z hsc $ */
#include "globals.h"
#include "device/cgastr.h"
#include "user/appl.h"

/* Hier muesst ihr selbst Code vervollstaendigen */

using namespace cga_sm;
using namespace globals;

int main()
{
  Application app;
  kout << "Interrupt test!!!";
  kout.flush();
	keyboard.plugin();
  kout.setpos(0, 10);
  kout << "Keyboard: ";
  kout.flush();
  kout.setpos(0, 20);
  kout << "Application: ";
  kout.flush();

	while(true)
  {
    cpu.disable_int();
    app.action();
    cpu.enable_int();
  }
    return 0;
 }
