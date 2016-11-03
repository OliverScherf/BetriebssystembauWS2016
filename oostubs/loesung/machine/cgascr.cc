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
    // initialise variables
    this->x = 0;
    this->y = 0;
}


void CGA_Screen::show(int x, int y, char c, unsigned char attrib)
{
    // call setpos with the given x and y parameter
    setpos(x, y);
    // compute the address for where the character c should be placed,
    // the value needs to be multiplied by 2 because the 2nd byte sets the color
    // of the font and background
    char* pos = (char*)CGA_START + 2 * (this->x + this->y * MAX_COLS);
    // whenever a new line needs to be displayed do not print the character
    // but instead set the x position to 0 and increment the y position
    if (c=='\n')
    {
        setpos(0, this->y + 1);
        return;
    }
    // copy the value of c to the computed
    *pos = c;
    // the attrib value is a 1 Byte value divided into :
    // 0-3 bit foreground color
    // 4-6 bit background color
    // 7   bit blinking
    *(pos + 1) = attrib;
    // increment the x position by 1
    setpos(x+1, y);
}

void CGA_Screen::setpos(int x, int y)
{
    this->x = x;
    this->y = y;
    //  x and y need to be between:
    //  0 <= x < MAX_COLS
    //  0 <= y < MAX_ROWS
    if (this->x > MAX_COLS)
    {
        this->x = 0;
        this->y++;
        
    }
    if (this->y >= MAX_ROWS) 
    { // if end of screen
            scroll();
            this->y--;
    }       

    // compute the current position as one int as y * MAX_COLS + x
    int temp_pos = this->y * MAX_COLS  + this->x;

    // the cursor is displayed in a 16bit int, which needs to be saved into 2
    // separate registers:
    // 14 high Byte
    // 15 low Byte
    // cga_index is used in order to set which bit needs to be written / read
    cga_index.outb(15);
    // cga_data is used in order to read/write from the bit defined in index
    cga_data.outb(temp_pos & 0x00FF);
    cga_index.outb(14);
    cga_data.outb(temp_pos>>8);
}

void CGA_Screen::getpos(int &x, int &y)
{
    // read high and low Bytes
    cga_index.outb(14);
    // shift the high Byte 8 bits to the right (new 8 bits are all 0)
    int temp_pos = cga_data.inb() << 8;
    cga_index.outb(15);
    // save low Byte to the last 8 bits
    temp_pos |= cga_data.inb();

    // compute the x position from the read bytes
    this->x = temp_pos % MAX_COLS;
    this->y = temp_pos / MAX_COLS;

    x = this->x;
    y = this->y;
}

void CGA_Screen::print(char* text, int length, unsigned char attrib)
{
    // loop through the text array and send each char to the show method
    for (int i = 0; i < length; i++)
        show(x, y, text[i], attrib);
}

void CGA_Screen::clear()
{
    for (unsigned int i=0; i < MAX_ROWS; i++) // iterate over rows
        for (unsigned int j = 0; j < MAX_COLS; j++) // iterate over cols
            // call show with ' ' and 0x00 in order to replace all existing chars
            // with ' ' and black fore- and background color
            show(j, i, ' ', 0x00);
    setpos(0,0); // set cursor back to x=0 and y=0
}

void CGA_Screen::scroll()
{
    unsigned int bytes_per_row = MAX_COLS * 2; // 2 bytes per pixel (the char + attrib)
    unsigned char buffer; // one byte buffer
    char* pos; // CGA memory pointer
    unsigned int abs_pos; // the absolute pixel position

    for (unsigned int row = 1; row <= MAX_ROWS; row++) // start in the second row up to rows + 1
    {
        for (unsigned int item = 0; item < bytes_per_row; item++)
        {
            abs_pos = row * MAX_COLS + item;
            pos = (char*)CGA_START + 2 * abs_pos;
            buffer = (row != MAX_ROWS) ? *pos : ' '; // Store the value of pos in buffer,
            // or an empty char for the last row.

            abs_pos = (row - 1) * MAX_COLS + item; // the absolute position of the row before
            pos = (char*)CGA_START + 2 * abs_pos;
            *pos = buffer;
        }
    }
}