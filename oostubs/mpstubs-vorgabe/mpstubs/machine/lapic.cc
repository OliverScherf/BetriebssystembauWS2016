#include "lapic.h"

// global object definition
LAPIC lapic;

void LAPIC::write(unsigned short reg, unsigned int value)
{
	*((volatile unsigned int *) (LAPIC_BASE + reg)) = value;
}

unsigned int LAPIC::read(unsigned short reg)
{
	return *((volatile unsigned int *) (LAPIC_BASE + reg));
}

unsigned char LAPIC::getLAPICID()
{
	unsigned int value = read(lapicid_reg);
	if (isPentium4()) {
		// Pentium 4 or Xeon
		return ((struct LAPICID_P4 *) &value)->apic_id;
	} else {
		// Pentium
		return ((struct LAPICID_P *) &value)->apic_id;
	}
}

unsigned char LAPIC::getMaxLVTEntry()
{
	unsigned int value = read(lapicver_reg);
	return ((struct LAPICVER *) &value)->max_lvt_entry;
}

unsigned char LAPIC::getVersion()
{
	unsigned int value = read(lapicver_reg);
	return ((struct LAPICVER *) &value)->version;
}

void LAPIC::init()
{
	unsigned int value;

	// reset logical destination ID
	// can be set using setLogicalLAPICID()
	value = read(ldr_reg);
	((struct LDR *) &value)->lapic_id = 0;
	write(ldr_reg, value);

	// set task priority to 0 -> accept all interrupts
	value = read(tpr_reg);
	((struct TPR *) &value)->task_prio = 0;
	((struct TPR *) &value)->task_prio_sub = 0;
	write(tpr_reg, value);

	// set flat delivery mode
	value = read(dfr_reg);
	((struct DFR *) &value)->model = DESTINATION_MODEL_FLAT;
	write(dfr_reg, value);

	// enable APIC and disable focus processor
	value = read(spiv_reg);
	((struct SPIVR *) &value)->apic_enable = LAPIC_ENABLED;
	((struct SPIVR *) &value)->focus_processor_checking = FOCUS_CPU_DISABLED;
	write(spiv_reg, value);
}

void LAPIC::ackIRQ()
{
	// dummy read
	read(spiv_reg);

	// signal end of interrupt
	write(eoi_reg, 0);
}

void LAPIC::setLogicalLAPICID(unsigned char id)
{
	unsigned int value = read(ldr_reg);
	((struct LDR *) &value)->lapic_id = id;
	write(ldr_reg, value);
}

void LAPIC::sendIPI(unsigned char destination, struct ICR1 data)
{
	// set destination in ICR2 register
	unsigned int value = read(icr2_reg);
	((struct ICR2 *) &value)->destination_field = destination;
	write(icr2_reg, value);

	// write data to ICR register
	// write triggers the IPI send
	value = *((unsigned int *) &data);
	write(icr1_reg, value);
}

unsigned char LAPIC::getIPIDeliveryStatus()
{
	unsigned int value = read(icr1_reg);
	return ((struct ICR1 *) &value)->delivery_status;
}

bool LAPIC::isExternalAPIC()
{
	// System Programming Guide 3A, p. 9-6
	unsigned char version = getVersion();
	if ((version & 0xf0) == 0x00) {
		return true;
	} else {
		return false;
	}
}

bool LAPIC::isLocalAPIC()
{
	// System Programming Guide 3A, p. 9-6
	unsigned char version = getVersion();
	if ((version & 0xf0) == 0x10) {
		return true;
	} else {
		return false;
	}
}

bool LAPIC::isPentium4()
{
	// System Programming Guide 3A, p. 9-6
	unsigned char version = getVersion();
	if (version == 0x14) {
		return true;
	} else {
		return false;
	}
}
