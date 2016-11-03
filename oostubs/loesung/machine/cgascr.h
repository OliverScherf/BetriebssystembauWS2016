#ifndef __screen_include__
#define __screen_include__

/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                             C G A _ S C R E E N                           */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Mit Hilfe dieser Klasse kann man auf den Bildschirm des PCs zugreifen.    */
/* Der Zugriff erfolgt direkt auf der Hardwareebene, d.h. ueber den Bild-    */
/* schirmspeicher bzw. die I/O-Ports der Grafikkarte.                        */
/*****************************************************************************/

#include "machine/io_port.h"
#include "io_port.h"

class CGA_Screen
 {
private:
    CGA_Screen(const CGA_Screen &copy); // Verhindere Kopieren
    //const char* CGA_START = (const char*)0xb8000;
    const char* CGA_START;
    unsigned int x;
    unsigned int y;
    IO_Port cga_index;
    IO_Port cga_data;
    void scroll();
public:
    const static unsigned int MAX_COLS = 80;
    const static unsigned int MAX_ROWS = 25;
    CGA_Screen();
    void show(int x, int y, char c, unsigned char attrib);
    void setpos(int x, int y);
    void getpos(int &x, int &y);
    void print(char* text, int length, unsigned char attrib);
    void clear();
 };

#endif
