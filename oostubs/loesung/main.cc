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

	kout << "Int -1337 (bin): " << o_sm::bin << -1337 <<o_sm::endl;
	kout << "Int -1337 (oct): " << o_sm::oct << -1337 <<o_sm::endl;
	kout << "Int -1337 (dec): " << o_sm::dec << -1337 <<o_sm::endl;
	kout << "Int -1337 (hex): " << o_sm::hex << -1336 <<o_sm::endl;
	kout << o_sm::endl;

	kout << "long 1234567890L (bin): " << o_sm::bin << 1234567890L <<o_sm::endl;
	kout << "long 1234567890L (oct): " << o_sm::oct << 1234567890L <<o_sm::endl;
	kout << "long 1234567890L (dec): " << o_sm::dec << 1234567890L <<o_sm::endl;
	kout << "long 1234567890L (hex): " << o_sm::hex << 1234567890L <<o_sm::endl;
	kout << "char* 0xb8000: " << o_sm::dec << (int*)0xb8000 << o_sm::endl;

	kout.flush();

	for (unsigned int i = 0; i < 5000000; ++i);

    kout.clear();

    //Demo for screen clearing and scrolling
    for(unsigned int i=1; i<=100; i++)
    {
        kout << o_sm::dec << i << ". Scrolling Scrolling test" << o_sm::endl;
        kout.flush();
        for (int j = 0; j < 100000; ++j);
    }

    for (unsigned int i = 0; i < 5000000; ++i);

    kout.clear();


    //Demo Keyboard application
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
