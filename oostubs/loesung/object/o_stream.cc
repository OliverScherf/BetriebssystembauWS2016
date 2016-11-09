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

namespace cga_sm
{
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
        int buffer_size = sizeof(short) * 8 + 1;
        char buffer[buffer_size];
        *this << ltoa(number, buffer, current_number_system);
        return *this;
    }

    O_Stream& O_Stream::operator<<(short number)
    {
        int buffer_size = sizeof(short) * 8 + 1;
        char buffer[buffer_size];
        *this << ltoa(number, buffer, current_number_system);
        return *this;
    }

    O_Stream& O_Stream::operator<<(int number)
    {
        int buffer_size = sizeof(int) * 8 + 1;
        char buffer[buffer_size];
        *this << ltoa(number, buffer, current_number_system);
        return *this;
    }

    O_Stream& O_Stream::operator<<(unsigned int number)
    {
        int buffer_size = sizeof(int) * 8 + 1;
        char buffer[buffer_size];
        *this << ltoa(number, buffer, current_number_system);
        return *this;
    }

    O_Stream& O_Stream::operator<<(long number)
    {
        unsigned int buffer_size = sizeof(long) * 8 + 1;
        char buffer[buffer_size];
        *this << ltoa(number, buffer, current_number_system);
        return *this;
    }

    O_Stream& O_Stream::operator<<(unsigned long number)
    {
        unsigned int buffer_size = sizeof(long) * 8 + 1;
        char buffer[buffer_size];
        *this << ltoa(number, buffer, current_number_system);
        return *this;
    }

    O_Stream& O_Stream::operator<<(void *pointer)
    {
        unsigned int tmp = current_number_system;
        current_number_system = HEX_SYSTEM;
        *this << "0x";
        *this << (unsigned int)pointer;
        current_number_system = tmp;
        return *this;
    }

    O_Stream& O_Stream::operator<<(char *text)
    {
        while (*text != '\0')
        {
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
        os.flush();
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

    /* Functions for "minor" number types. */

    char* ltoa(short number, char* str)
    {
        return ltoa(number, str);
    }

    char* ltoa(short number, char* str, unsigned int base)
    {
        int num_bits = sizeof(short) * 8;
        long tmp = 0L;
        switch (base)
        {
            case BIN_SYSTEM:
            case OCT_SYSTEM:
            case HEX_SYSTEM:
                for(int i = 0; i < num_bits; i++)
                    tmp |= ((1<<i) & number);
                return ltoa(tmp, str, base);
            case DEC_SYSTEM:
            default:
                return ltoa((long)number, str);
        }
    }

    char* ltoa(unsigned short number, char* str)
    {
        return ltoa((long)number, str);
    }

    char* ltoa(unsigned short number, char* str, unsigned int base)
    {
        return ltoa((long)number, str, base);
    }

    char* ltoa(int number, char* str)
    {
        return ltoa(number, str);
    }

    char* ltoa(int number, char* str, unsigned int base)
    {
        int num_bits = sizeof(int) * 8;
        long tmp = 0L;
        switch (base)
        {
            case BIN_SYSTEM:
            case OCT_SYSTEM:
            case HEX_SYSTEM:
                for(int i = 0; i < num_bits; i++)
                    tmp |= ((1<<i) & number);
                return ltoa(tmp, str, base);
            case DEC_SYSTEM:
            default:
                return ltoa((long)number, str);
        }
    }

    char* ltoa(unsigned int number, char* str)
    {
        return ltoa((long)number, str);
    }

    char* ltoa(unsigned int number, char* str, unsigned int base)
    {
        return ltoa((long)number, str, base);
    }


    /* "Real" functions. */

    char* ltoa(long number, char* str)
    {
        /* CONVERTS TO DEC SYSTEM! */

        /* All available digits- */
        const char digits[] = "0123456789";
        /* The pointer to the buffer position. */
        char* position = str;

        position = str;
        if (number < 0)
        {
            *position++ = '-';
            number *= -1;
        }
        // Define string end.
        long digit_count = number;
        // Move to where representation ends.
        do
        {
            ++position;
            digit_count = digit_count / 10;
        } while (digit_count);
        *position = '\0';

        // Move back, inserting digits as you go.
        do
        {
            *--position = digits[number % 10];
            number /= 10;
        } while (number);
        return str;
    }

    char* ltoa(long number, char* str, unsigned int base)
    {
        /* All available digits- */
        const char digits[] = "0123456789abcdef";
        /* The pointer to the buffer position. */
        char* position = str;
        /* The number of bytes of the number. */
        unsigned int number_of_bytes = sizeof(long);
        /* The number of 'bits' (or digits) of the output. */
        unsigned long number_of_bits = number_of_bytes * 8L;  // 8 chars are required to represent a byte.


        unsigned int mask;
        unsigned int shifter;

        /* Bool for DEC_SYSTEM or unknown systems. */
        bool dec_or_default = false;
        switch (base)
        {
            case BIN_SYSTEM:
                mask = 0b1;
                shifter = 1;
                break;
            case OCT_SYSTEM:
                mask = 0b111;                           // An oct digit can have up to 3 bit, therefore 0b111.
                shifter = 3;                            // Shift 3 bit for the next number.
                break;
            case HEX_SYSTEM:
                mask = 0b1111;                          // A oct digit can have up to 4 bit, therefore 0b1111.
                shifter = 4;                            // Shift 4 bit for the next number.
                break;
            case DEC_SYSTEM:
            default:
                dec_or_default = true;                  // Trigger default implementation.
        }

        if (dec_or_default)
            return ltoa(number, str);

        // find the leftmost bit
        bool first_one_found = false;
        while(number_of_bits > 0 && !first_one_found)
            if (!first_one_found)
            {
                if ((number & (1<<(number_of_bits - 1))) != 0)
                {
                    first_one_found = true;
                    position += number_of_bits;
                    // Define string end.
                    *position = '\0';
                }
                else
                    number_of_bits--;
            }

        // Translate the digits.
        do
        {
            if (number_of_bits < shifter)
            {
                mask >>= shifter - number_of_bits;
                shifter = number_of_bits;
            }
            *--position = digits[number & mask];
            number >>= shifter;
            number_of_bits -= shifter;
        } while (number_of_bits > 0);

        return position;
    }

    char* ltoa(unsigned long number, char* str)
    {
        /* CONVERTS TO DEC SYSTEM! */

        /* All available digits- */
        const char digits[] = "0123456789";
        /* The pointer to the buffer position. */
        char* position = str;

        position = str;
        // Define string end.
        long digit_count = number;
        // Move to where representation ends.
        do
        {
            ++position;
            digit_count = digit_count / 10;
        } while (digit_count);
        *position = '\0';

        // Move back, inserting digits as you go.
        do
        {
            *--position = digits[number % 10];
            number /= 10;
        } while (number);
        return position;
    }

    char* ltoa(unsigned long number, char* str, unsigned int base)
    {
        switch (base)
        {
            case BIN_SYSTEM:
            case OCT_SYSTEM:
            case HEX_SYSTEM:
                return ltoa(((long)number), str, base);
            case DEC_SYSTEM:
            default:
                return ltoa(number, str);
        }
    }
}
