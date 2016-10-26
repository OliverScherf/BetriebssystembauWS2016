/* $Id: main.cc 956 2008-10-19 22:24:23Z hsc $ */
#include "machine/cgascr.h"

/* Hier muesst ihr selbst Code vervollstaendigen */ 
        
int main()
{
    CGA_Screen screen;
    screen.print("Hello\n World!", 13, 0x0f);
    return 0;
 }
