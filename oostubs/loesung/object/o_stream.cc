/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                            O _ S T R E A M                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Die Klasse O_Stream enthaelt die Definition des << Operators fuer die     */
/* wichtigsten der vordefinierten Datentypen und realisiert somit die        */
/* bekannte Ausgabefunktion der C++ IO_Stream Bibliothek. Zur Zeit wird die  */
/* Darstellung von Zeichen, Zeichenketten und ganzen Zahlen unterstuetzt.    */
/* Ein weiterer << Operator erlaubt die Verwendung von Manipulatoren.        */
/*                                                                           */
/* Neben der Klasse O_Stream sind hier auch die Manipulatoren hex, dec, oct  */
/* und bin fuer die Wahl der Basis bei der Zahlendarstellung, sowie endl     */
/* fuer den Zeilenumbruch definiert.                                         */
/*****************************************************************************/

#include "object/o_stream.h"

namespace o_sm {

    O_Stream::O_Stream()
    {
        current_number_system = DEC_SYSTEM;
    }

    O_Stream& O_Stream::operator<<(unsigned char c)
    {
        put(c);
        return *this;
    }

    O_Stream& O_Stream::operator<<(char c)
    {
        put(c);
        return *this;
    }

    O_Stream& O_Stream::operator<<(unsigned short number)
    {
        return *this;
    }

    O_Stream& O_Stream::operator<<(short number)
    {
        return *this;
    }

    O_Stream& O_Stream::operator<<(unsigned int number)
    {
        return *this;
    }

    O_Stream& O_Stream::operator<<(int number)
    {
        return *this;
    }

    O_Stream& O_Stream::operator<<(unsigned long number)
    {
        return *this;
    }

    O_Stream& O_Stream::operator<<(long number)
    {
        unsigned int buffer_size = sizeof(long) * 8 + 1;
        char buffer[buffer_size];
        put('c');
        *this << ltoa(number, buffer, current_number_system);
        put('c');
        flush();
        return *this;
    }

    O_Stream& O_Stream::operator<<(void *pointer)
    {
        return *this;
    }

    O_Stream& O_Stream::operator<<(char *text)
    {
        while (*text != '\0') {
            put(*text);
            text++;
        }
        return *this;
    }

    O_Stream& O_Stream::operator<<(O_Stream& (*fkt) (O_Stream&))
    {
        return fkt(*this);
    }


    void O_Stream::set_number_system_binary()
    {
        current_number_system = BIN_SYSTEM;
    }

    void O_Stream::set_number_system_octal()
    {
        current_number_system = OCT_SYSTEM;
    }

    void O_Stream::set_number_system_decimal()
    {
        current_number_system = DEC_SYSTEM;
    }

    void O_Stream::set_number_system_hexadecimal()
    {
        current_number_system = HEX_SYSTEM;
    }

    /* Manipulator functions */
    O_Stream& endl (O_Stream& os)
    {
        os << '\n';
        return os;
    }

    O_Stream& bin (O_Stream& os)
    {
        os.set_number_system_binary();
        return os;
    }

    O_Stream& oct (O_Stream& os)
    {
        os.set_number_system_octal();
        return os;
    }

    O_Stream& dec (O_Stream& os)
    {
        os.set_number_system_decimal();
        return os;
    }

    O_Stream& hex (O_Stream& os)
    {
        os.set_number_system_hexadecimal();
        return os;
    }

    /* Namespace functions */

    char* ltoa(long number, char* str, unsigned int base)
    {
        char* position = str;
        unsigned int number_of_bytes = sizeof(long);
        unsigned long number_of_bits = number_of_bytes * 8L;

        const char digits[] = "0123456789abcdef";
        // find the leftmost bit
        bool first_one_found = false;
        while(number_of_bits > 0 && !first_one_found)
        {
            if (!first_one_found)
            {
                if ((number & (1<<number_of_bits - 1)) != 0)
                {
                    first_one_found = true;
                    position += number_of_bits;
                    // define string end
                    *position = '\0';
                }
                else
                    number_of_bits--;
            }
        }
        int mask;
        int shifter;
        bool dec_or_default = false;
        switch (base)
        {
            case BIN_SYSTEM:
                mask = 1;
                shifter = 1;
                break;
            case OCT_SYSTEM:
                mask = 7;
                shifter = 3;
                break;
            case HEX_SYSTEM:
                mask = 15;
                shifter = 4;
                break;
            case DEC_SYSTEM:
            default:
                dec_or_default = true;
        }
        if (dec_or_default)
        {
            position = str;
            if (number < 0)
            {
                *position++ = '-';
                number *= -1;
            }
            // define string end
            long digit_count = number;
            do
            { //Move to where representation ends
                ++position;
                digit_count = digit_count / 10;
            } while (digit_count);
            *position = '\0';

            //Move back, inserting digits as you go
            do
            {
                *--position = digits[number % 10];
                number /= 10;
            } while (number);
        }
        else
        {
            do
            {
                if (number_of_bits < shifter)
                {
                    mask >>= shifter - number_of_bits;
                    shifter = number_of_bits;
                }
                //position -= shifter;
                *--position = digits[number & mask];
                number >>= shifter;
                number_of_bits -= shifter;
            } while (number_of_bits > 0);
        }
        return position;

    }
}