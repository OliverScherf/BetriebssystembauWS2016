/* $Id: main.cc 956 2008-10-19 22:24:23Z hsc $ */
#include "device/cgastr.h"
#include "machine/keyctrl.h"

/* Hier muesst ihr selbst Code vervollstaendigen */

int main()
{
    CGA_Stream kout;
    kout.clear();
    kout << "Number Test!" << o_sm::endl;
    kout << "Unsigned Short 255 (bin): " << o_sm::bin << (unsigned short)255 <<o_sm::endl;
    kout << "Unsigned Short 255 (oct): " << o_sm::oct << (unsigned short)255 <<o_sm::endl;
    kout << "Unsigned Short 255 (dec): " << o_sm::dec << (unsigned short)255 <<o_sm::endl;
    kout << "Unsigned Short 255 (hex): " << o_sm::hex << (unsigned short)255 <<o_sm::endl;
    kout << o_sm::endl;
    kout << "Long -13 (bin): " << o_sm::bin << (long)-13 <<o_sm::endl;
    kout << "Short -13 (bin): " << o_sm::bin << (short)-13 <<o_sm::endl;
    //kout.flush();
    kout << "Long -1337 (oct): " << o_sm::oct << (long)-1337 <<o_sm::endl;
    //kout.flush();
    kout << "Long -1337 (dec): " << o_sm::dec << (long)-1337 <<o_sm::endl;
    //kout.flush();
    kout << "Long -1337 (hex): " << o_sm::hex << (long)-1336 <<o_sm::endl;
    //kout.flush();
    kout << o_sm::endl;
    kout << "long 1234567890L (bin): " << o_sm::bin << 1234567890L <<o_sm::endl;
    kout << "long 1234567890L (oct): " << o_sm::oct << 1234567890L <<o_sm::endl;
    kout << "long 1234567890L (dec): " << o_sm::dec << 1234567890L <<o_sm::endl;
    kout << "long 1234567890L (hex): " << o_sm::hex << 1234567890L <<o_sm::endl;
    kout << "char* 0xb8000: " << o_sm::dec << (int*)0xb8000 << o_sm::endl;
    kout.flush();

    kout.clear();

    Keyboard_Controller keyctl;
    Key tmp;
    for (;;) {
    	tmp = keyctl.key_hit();
    	if (tmp.valid()) {
			kout << tmp.ascii();
			kout.flush();
    	}
    }
    return 0;
 }
