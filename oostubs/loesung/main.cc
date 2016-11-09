/* $Id: main.cc 956 2008-10-19 22:24:23Z hsc $ */
#include "globals.h"
#include "device/cgastr.h"
#include "machine/pic.h"


/* Hier muesst ihr selbst Code vervollstaendigen */

using namespace cga_sm;
using namespace globals;

CGA_Stream cga_sm::kout;
CPU globals::cpu;
Plugbox globals::plugbox;

int main()
{
    kout << "Hello world" << endl;
	PIC pic;
	while(true);
    return 0;
 }
