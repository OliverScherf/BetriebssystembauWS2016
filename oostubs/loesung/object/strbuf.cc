/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                       S T R I N G B U F F E R                             */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die Klasse Stringbuffer stellt einen Puffer fuer die Sammlung von Zeichen */
/* zur Darstellung auf dem Bildschirm oder anderen Ausgabegeraeten bereit.   */
/* Die Ausgabe der Zeichen erfolgt, sobald der Puffer voll ist oder wenn     */
/* explizit die Methode flush() aufgerufen wird.                             */
/* Da Stringbuffer geraeteunabhaengig sein soll, ist flush() eine virtuelle  */
/* Methode, die von den abgeleiteten Klassen definiert werden muss.          */
/*****************************************************************************/

#include "object/strbuf.h"


Stringbuffer::Stringbuffer()
{
    for(unsigned short i = 0; i < BUFFER_SIZE; i++)
        buffer[i] = ' ';
    buffer_index = 0;
}

unsigned int Stringbuffer::get_length()
{
    return buffer_index; // The index of the next free space in the buffer is equal to the length.
}

void Stringbuffer::put(char c)
{
    buffer[buffer_index++] = c;
    if (buffer_index >= BUFFER_SIZE) // if buffer full
    {
        flush();
        buffer_index = 0;
    }
}
