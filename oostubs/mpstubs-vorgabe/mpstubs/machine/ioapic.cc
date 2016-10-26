#include "ioapic.h"
#include "smpsys.h"

// global object definition
IOAPIC ioapic;

void IOAPIC::write(unsigned char reg, unsigned int value)
{
	IOREGSEL_REG = reg;
	IOWIN_REG = value;
}

unsigned int IOAPIC::read(unsigned char reg)
{
	IOREGSEL_REG = reg;
	return IOWIN_REG;
}

unsigned char IOAPIC::getID()
{
	unsigned int value = read(ioapicid_reg);
	return ((struct IOAPICID *) &value)->ID;
}

void IOAPIC::setID(unsigned char id)
{
	unsigned int value = read(ioapicid_reg);
	((struct IOAPICID *) &value)->ID = id;
	write(ioapicid_reg, value);
}

unsigned char IOAPIC::getVersion()
{
	unsigned int value = read(ioapicver_reg);
	return ((struct IOAPICVER *) &value)->version;
}

unsigned char IOAPIC::getMaximumRedirectionEntry()
{
	unsigned int value = read(ioapicver_reg);
	return ((struct IOAPICVER *) &value)->entry;
}

unsigned char IOAPIC::getArbitrationID()
{
	unsigned int value = read(ioapicarb_reg);
	return ((struct IOAPICARB *) &value)->arbitration;
}

void IOAPIC::setArbitrationID(unsigned char id)
{
	unsigned int value = read(ioapicarb_reg);
	((struct IOAPICARB *) &value)->arbitration = id;
	write(ioapicarb_reg, value);
}

struct IOREDTBL IOAPIC::getRedirectionTableEntry(unsigned char slot)
{
	struct IOREDTBL result;
	unsigned int word1 = read(ioredtbl_reg + 2*slot + 0);
	unsigned int word2 = read(ioredtbl_reg + 2*slot + 1);
	* (((unsigned int *) &result) + 0) = word1;
	* (((unsigned int *) &result) + 1) = word2;
	return result;
}

void IOAPIC::setRedirectionTableEntry(unsigned char slot, struct IOREDTBL entry)
{
	unsigned int word1 = *(((unsigned int *) &entry) + 0);
	unsigned int word2 = *(((unsigned int *) &entry) + 1);
	write(ioredtbl_reg + 2*slot + 0, word1);
	write(ioredtbl_reg + 2*slot + 1, word2);
}

void IOAPIC::enableRedirectionTableEntry(unsigned char slot)
{
	struct IOREDTBL entry = getRedirectionTableEntry(slot);
	entry.mask = MASK_ENABLED;
	setRedirectionTableEntry(slot, entry);
}

void IOAPIC::disableRedirectionTableEntry(unsigned char slot)
{
	struct IOREDTBL entry = getRedirectionTableEntry(slot);
	entry.mask = MASK_DISABLED;
	setRedirectionTableEntry(slot, entry);
}

unsigned char IOAPIC::getRedirectionTableDeliveryStatus(unsigned char slot)
{
	struct IOREDTBL entry = getRedirectionTableEntry(slot);
	return entry.delivery_status;
}

void IOAPIC::init()
{
	// set 4-bit ID to correct IO-APIC value, determined at startup
	unsigned char ioapicID = smp.getIOAPICID();
	setID(ioapicID);

	// set all redirection table entries and their R/W fields to default values
	struct IOREDTBL entry;

	for (unsigned char i = 0; i < 24; i++) {
		entry = getRedirectionTableEntry(i);
		entry.vector = 0x20; // vector 32
		entry.delivery_mode = DELIVERY_MODE_LOWESTPRI;
		entry.destination_mode = DESTINATION_MODE_LOGICAL;
		entry.polarity = POLARITY_HIGH;
		entry.trigger_mode = TRIGGER_MODE_EDGE;
		entry.mask = MASK_DISABLED;
		entry.destination.logical_mode.logical_destination = 0xff; // all CPUs
		setRedirectionTableEntry(i, entry);
	}
}

void IOAPIC::activateKeyboard()
{
	struct IOREDTBL entry = getRedirectionTableEntry(keyboard_slot);
	entry.vector = keyboard_vector;
	entry.mask = MASK_ENABLED;
	setRedirectionTableEntry(keyboard_slot, entry);
}

void IOAPIC::activateTimer(bool onHardware)
{
	unsigned char slot = (onHardware == true) ? timer_slot_hw : timer_slot_qemu;
	struct IOREDTBL entry = getRedirectionTableEntry(slot);
	entry.vector = timer_vector;
	entry.mask = MASK_ENABLED;
	setRedirectionTableEntry(slot, entry);
}
