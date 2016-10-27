/* $Id: main.cc 956 2008-10-19 22:24:23Z hsc $ */
#include "machine/cgascr.h"

/* Hier muesst ihr selbst Code vervollstaendigen */

int main()
{
    CGA_Screen screen;
    screen.clear();
    for (int i = 0; i < 300; i++)
    {
        for (unsigned int i = 0; i < 655306; i++); // dirty sleep
        screen.print("Hello World!", 12, 0x0f);
    }
    return 0;
 }
