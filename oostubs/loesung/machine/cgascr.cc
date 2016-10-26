/* $Id: cgascr.cc 5834 2013-10-08 17:04:08Z os $ */

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

#include "machine/cgascr.h"

CGA_Screen::CGA_Screen() : cga_index(0x3d4), cga_data(0x3d5)
{
    this->pos = 0x00;
    this->x = 0;
    this->y = 0;
}


void CGA_Screen::show(int x, int y, char c, unsigned char attrib)
{
    setpos(x, y);
    pos = (char*)CGA_START + 2 * (this->x + this->y * MAX_COLS);
    if (c=='\n')
    {
        setpos(0, this->y + 1);
        return;
    }
    *pos = c;
    *(pos + 1) = attrib;
    setpos(x+1, y);
}

void CGA_Screen::setpos(int x, int y)
{
    this->x = x;
    this->y = y;
    // 0 <= x <= 79
    // 0 <= y <= 24
    if (this->x > MAX_COLS)
    {
        this->x = 0;
        this->y++;
        this->y %= MAX_ROWS;
    }

    int temp_pos = this->y * MAX_COLS  + this->x;

    cga_index.outb(15);
    cga_data.outb(temp_pos & 0x00FF);
    cga_index.outb(14);
    cga_data.outb(temp_pos>>8);
}

void CGA_Screen::getpos(int &x, int &y)
{

    cga_index.outb(14);
    int temp_pos = cga_data.inb() << 8;
    cga_index.outb(15);
    temp_pos |= cga_data.inb();

    this->x = temp_pos % MAX_COLS;
    this->y = temp_pos / MAX_COLS;

    x = this->x;
    y = this->y;
}

void CGA_Screen::print(char* text, int length, unsigned char attrib)
{
    for (int i = 0; i < length; i++)
        show(x, y, text[i], attrib);
}