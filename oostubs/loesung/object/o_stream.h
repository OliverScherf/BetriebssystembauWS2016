/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                            O _ S T R E A M                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die Klasse O_Stream enthaelt die Definition des << Operators fuer die     */
/* wichtigsten der vordefinierten Datentypen und realisiert somit die        */
/* bekannte Ausgabefunktion der C++ iO_Stream Bibliothek. Zur Zeit wird die  */
/* Darstellung von Zeichen, Zeichenketten und ganzen Zahlen unterstuetzt.    */
/* Ein weiterer << Operator erlaubt die Verwendung von Manipulatoren.        */
/*                                                                           */
/* Neben der Klasse O_Stream sind hier auch die Manipulatoren hex, dec, oct  */
/* und bin fuer die Wahl der Basis bei der Zahlendarstellung, sowie endl     */
/* fuer den Zeilenumbruch definiert.                                         */
/*****************************************************************************/

#ifndef __o_stream_include__
#define __o_stream_include__

#include "object/strbuf.h"

namespace o_sm
{
    const unsigned int BIN_SYSTEM = 2;
    const unsigned int OCT_SYSTEM = 8;
    const unsigned int DEC_SYSTEM = 10; // default
    const unsigned int HEX_SYSTEM = 16;
    class O_Stream;

    O_Stream& endl (O_Stream& os);
    O_Stream& bin (O_Stream& os);
    O_Stream& oct (O_Stream& os);
    O_Stream& dec (O_Stream& os);
    O_Stream& hex (O_Stream& os);

    char* ltoa(long number, char* str, unsigned int base);
}

class o_sm::O_Stream : public Stringbuffer
{
private:
    O_Stream(const O_Stream &copy); // Verhindere Kopieren
    void number_to_bin(long number, char* output_buffer, unsigned short &lenght_of_buffer);
    unsigned int current_number_system;
protected:

public:
    O_Stream();
    O_Stream& operator<< (unsigned char c);
    O_Stream& operator<< (char c);
    O_Stream& operator<< (unsigned short number);
    O_Stream& operator<< (short number);
    O_Stream& operator<< (unsigned int number);
    O_Stream& operator<< (int number);
    O_Stream& operator<< (unsigned long number);
    O_Stream& operator<< (long number);
    O_Stream& operator<< (void* pointer);
    O_Stream& operator<< (char* text);
    O_Stream& operator<< (O_Stream& (*fkt) (O_Stream&));

    void set_number_system_binary();
    void set_number_system_octal();
    void set_number_system_decimal();
    void set_number_system_hexadecimal();
};


/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          M A N I P U L A T O R E N                        */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die folgenden Funktionen erhalten und liefern jeweils eine Referenz auf   */
/* ein O_Stream Objekt. Da die Klasse O_Stream einen Operator << fuer        */
/* derartige Funktionen definiert, koennen sie mit Hilfe dieses Operators    */
/* aufgerufen und sogar in weitere Eingaben eingebettet werden.              */
/* Aufgabe der Manipulatoren ist, die Darstellung der nachfolgenden Ausgaben */
/* zu beeinflussen, z.B durch die Wahl des Zahlensystems.                    */
/*---------------------------------------------------------------------------*/

// ENDL: fuegt einen Zeilenumbruch in die Ausgabe ein.
/* Hier muesst ihr selbst Code vervollstaendigen */ 

// BIN: waehlt das binaere Zahlensystem aus.
/* Hier muesst ihr selbst Code vervollstaendigen */ 
        
// OCT: waehlt das oktale Zahlensystem aus.
/* Hier muesst ihr selbst Code vervollstaendigen */ 
        
// DEC: waehlt das dezimale Zahlensystem aus.
/* Hier muesst ihr selbst Code vervollstaendigen */ 
        
// HEX: waehlt das hexadezimale Zahlensystem aus.
/* Hier muesst ihr selbst Code vervollstaendigen */ 

#endif

