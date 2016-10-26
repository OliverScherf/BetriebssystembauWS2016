#include "machine/acpi.h"

/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                       A C P I _ S U B S Y S T E M                         */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* In diesem Namespace finden sich einige Klassen, die der Interpretation    */
/* der ACPI-Tabellen dienen, die sich zu Beginn im Speicher befinden und     */
/* unter Umständen zur Erkennung der Prozessoren und APICs benutzt werden.   */
/*****************************************************************************/

namespace ACPI_Subsystem {


bool sums_to_zero( void *start, int len) {
       	int sum = 0;
	char* start_addr = (char *) start;
	if ( len == 0)
		return false;
       	while (len--)
		sum += *start_addr++;
	return !(sum & 0xff);
}


//For the following lines, "spec" means the ACPI specification v. 3.0
//spec 5.2.5.1
//maybe doesn't work for all systems (only EISA/MCA systems according to spec)
RSDP *RSDP::find()
{
	void *ebda_ptr = *( (void **) ( (0x40<<4)+0x0e) );
	void *bios_ro_memspace = (void *) (0xe0000);
	RSDP *found;

	if ( ( found = find( ebda_ptr, 0x400 ) ) )
		return found;

	if ( ( found = find( bios_ro_memspace, 0x20000 ) ) )
		return found;

	LOCK
	DBG << "ACPI: No root system description pointer found" << endl;
	UNLOCK
	return 0;
}

RSDP *RSDP::find( void *start, int len )
{
	int *search = (int *) start;
	int *end = ( search + len / 4);
	RSDP *found;

	for (; search < end; search+=4 )
	{
		
		if ( search[0] != CHARS_TO_UINT32('R','S','D',' ') )
			continue;

		if ( search[1] != CHARS_TO_UINT32('P','T','R',' ') ) 
			continue;

		found = (RSDP *) search;
		if ( found->check_sum() )
			return found;

		LOCK
		DBG << "ACPI: found RDSP signature at" << (void *) found
		    << ", but RDSP checksum is wrong" << endl;
		UNLOCK
	}

	return 0;
}


} // ACPI_Subsystem

