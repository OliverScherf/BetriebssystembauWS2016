/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                           	I O A P I C                                  */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* IO-APIC-manual references refer to the document "82093AA I/O Advanced     */
/* Programmable Interrupt Controller (IOAPIC)".                              */
/*****************************************************************************/

#ifndef __IOAPIC_H__
#define __IOAPIC_H__

class IOAPIC
{
private:
	void write(unsigned char reg, unsigned int value);
	unsigned int read(unsigned char reg);

	// IOAPIC manual, p. 8
	enum {
		ioapicid_reg	=	0x00,
		ioapicver_reg	=	0x01,
		ioapicarb_reg	=	0x02,
		ioredtbl_reg	=	0x10
	};

	enum {
		keyboard_vector	= 0x21,
		timer_vector	= 0x20
	};

	enum {
		keyboard_slot	= 1,
		timer_slot_hw	= 2, // 2 on real hardware
		timer_slot_qemu	= 0 // 0 in qemu
	};

public:
	IOAPIC() {}
	unsigned char getID();
	void setID(unsigned char id);
	unsigned char getVersion();
	unsigned char getMaximumRedirectionEntry();
	unsigned char getArbitrationID();
	void setArbitrationID(unsigned char id);
	struct IOREDTBL getRedirectionTableEntry(unsigned char slot);
	void setRedirectionTableEntry(unsigned char slot, struct IOREDTBL entry);
	void enableRedirectionTableEntry(unsigned char slot);
	void disableRedirectionTableEntry(unsigned char slot);
	unsigned char getRedirectionTableDeliveryStatus(unsigned char slot);
	void init();
	void activateKeyboard();
	void activateTimer(bool onHardware);
};

// IOAPIC manual, p. 8
#define IOREGSEL_REG (*((volatile unsigned int *) 0xfec00000))
#define IOWIN_REG (*((volatile unsigned int *) 0xfec00010))

// IOAPIC manual, p. 11, 12
#define DESTINATION_MODE_PHYSICAL	0x0
#define DESTINATION_MODE_LOGICAL	0x1

// IOAPIC manual, p. 12
#define TRIGGER_MODE_EDGE			0x0 			
#define TRIGGER_MODE_LEVEL			0x1 			

// IOAPIC manual, p. 12
#define POLARITY_HIGH				0x0
#define POLARITY_LOW				0x1

// IOAPIC manual, p. 12
#define MASK_ENABLED				0x0
#define MASK_DISABLED				0x1

// IOAPIC manual, p. 13
#define DELIVERY_MODE_FIXED			0x0
#define DELIVERY_MODE_LOWESTPRI		0x1
#define DELIVERY_MODE_SMI			0x2
// Reserved			 				0x3
#define DELIVERY_MODE_NMI			0x4
#define DELIVERY_MODE_INIT			0x5
// Reserved							0x6
#define DELIVERY_MODE_EXTINT		0x7

// IOAPIC manual, p. 9
struct IOAPICID
{
	int reserved_2:24,
		ID:4, // IOAPIC Identification, R/W
		reserved_1:4;
} __attribute__((packed));

// IOAPIC manual, p. 10
struct IOAPICVER
{
	int version:8, // APIC Version, RO
		reserved_2:8,
		entry:8, // Maximum Redirection Entry, RO
		reserved_1:8;
} __attribute__((packed));

// IOAPIC manual, p. 10
struct IOAPICARB
{
	int reserved_2:24,
		arbitration:4, // IOAPIC Arbitration ID, R/W
		reserved_1:4;
} __attribute__((packed));

// IOAPIC manual, p. 11-13
struct IOREDTBL
{
	int vector:8, // Interrupt Vector, R/W
		delivery_mode:3, // Delivery Mode, R/W
		destination_mode:1, // Destination Mode, R/W
		delivery_status:1, // Delivery Status, RO
		polarity:1, // Interrupt Input Pin Polarity, R/W
		remote_irr:1, // Remote IRR (for level-triggered interrupts only), RO
		trigger_mode:1, // Trigger Mode, R/W
		mask:1, // Interrupt Mask, R/W
		reserved:15;
	union {
		struct {
			long reserved_1:24,
			physical_destination:4, // APIC ID
			reserved_2:4;
		} physical_mode;
		struct {
			long reserved:24,
			logical_destination:8; // Potential set of processors
		} logical_mode;
	} destination; // Destination Field, R/W
} __attribute__((packed));

// global object declaration
extern IOAPIC ioapic;

#endif
