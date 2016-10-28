/* $Id: main.cc 956 2008-10-19 22:24:23Z hsc $ */
#include "device/cgastr.h"

/* Hier muesst ihr selbst Code vervollstaendigen */

int main()
{
    CGA_Stream stream;
    stream.clear();
    stream << "Hello\n World!" << o_sm::dec << 1234567890L;
    stream.flush();
    return 0;
 }
