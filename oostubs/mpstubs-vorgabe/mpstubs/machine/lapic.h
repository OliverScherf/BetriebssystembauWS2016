/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                           	  L A P I C                                  */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* System Programming Guide references refer to the Intel System Programming */
/* Guide 3A.                                                                 */
/*****************************************************************************/

#ifndef __LAPIC_H__
#define __LAPIC_H__

class LAPIC
{
private:
	void write(unsigned short reg, unsigned int value);
	unsigned int read(unsigned short reg);

	// System Programming Guide 3A, p. 9-8 - 9-10
	enum {
		// Reserved			= 0x000 - 0x010
		lapicid_reg			= 0x020, // Local APIC ID Register, R/W
		lapicver_reg		= 0x030, // Local APIC Version Register, RO
		// Reserved			= 0x040 - 0x070
		tpr_reg				= 0x080, // Task Priority Register, R/W
		apr_reg				= 0x090, // Arbitration Priority Register, RO
		ppr_reg				= 0x0a0, // Processor Priority Register, RO
		eoi_reg				= 0x0b0, // EOI Register, WO
		// Reserved			= 0x0c0
		ldr_reg				= 0x0d0, // Logical Destination Register, R/W
		dfr_reg				= 0x0e0, // Destination Format Register, bits 0-27 RO, bits 28-31 R/W
		spiv_reg			= 0x0f0, // Spurious Interrupt Vector Register, bits 0-8 R/W, bits 9-1 R/W
		isr_reg				= 0x100, // In-Service Register, 256 bits RO
		tmr_reg				= 0x180, // Trigger Mode Register, 256 bits RO
		irr_reg				= 0x200, // Interrupt Request Register, 256 bits RO
		es_reg				= 0x280, // Error Status Register, RO
		// Reserved			= 0x290 - 0x2e0
		lvtcmci_reg			= 0x2f0, // LVT CMCI Register, R/W
		icr1_reg			= 0x300, // Interrupt Command Register 1, R/W
		icr2_reg			= 0x310, // Interrupt Command Register 2, R/W
		lvttimer_reg		= 0x320, // LVT Timer Register, R/W
		lvtthermal_reg		= 0x330, // LVT Thermal Sensor Register, R/W
		lvtpmc_reg			= 0x340, // LVT Performance Monitoring Counters Register, R/W
		lvtlint0_reg		= 0x350, // LVT LINT0 Register, R/W
		lvtlint1_reg		= 0x360, // LVT LINT1 Register, R/W
		lvterror_reg		= 0x370, // LVT Error Register, R/W
		timerinit_reg		= 0x380, // LVT Timer Initial Count Register, R/W
		timercurrent_reg	= 0x390, // LVT Timer Current Count Register, RO
		// Reserved			= 0x3a0 - 0x3d0
		timerdivide_reg		= 0x3e0 // LVT Timer Divide Configuration Register, R/W
		// Reserved			= 0x3f0
	};

public:
	LAPIC() {}
	unsigned char getLAPICID();
	unsigned char getCPUID() {
		return getLAPICID();
	}
	unsigned char getMaxLVTEntry();
	unsigned char getVersion();
	void init();
	void ackIRQ();
	void setLogicalLAPICID(unsigned char id);
	void sendIPI(unsigned char destination, struct ICR1 data);
	unsigned char getIPIDeliveryStatus();
	bool isExternalAPIC();
	bool isLocalAPIC();
	bool isPentium4();
};

// System Programming Guide 3A, p. 9-6
#define LAPIC_BASE 0xfee00000

// System Programming Guide 3A, p. 9-24
#define DESTINATION_SHORTHAND_NO			0x0
#define DESTINATION_SHORTHAND_SELF			0x1
#define DESTINATION_SHORTHAND_ALLINCSELF	0x2
#define DESTINATION_SHORTHAND_ALLEXCSELF	0x3

// System Programming Guide 3A, p. 9-24
#define TRIGGER_MODE_EDGE					0x0
#define TRIGGER_MODE_LEVEL					0x1

// System Programming Guide 3A, p. 9-24
#define LEVEL_DEASSERT						0x0
#define LEVEL_ASSERT						0x1

// System Programming Guide 3A, p. 9-24
#define DELIVERY_STATUS_IDLE				0x0
#define DELIVERY_STATUS_SEND_PENDING		0x1

// System Programming Guide 3A, p. 9-24
#define DESTINATION_MODE_PHYSICAL			0x0
#define DESTINATION_MODE_LOGICAL			0x1

// System Programming Guide 3A, p. 9-24
#define DELIVERY_MODE_FIXED					0x0
#define DELIVERY_MODE_LOWESTPRI				0x1
#define DELIVERY_MODE_SMI					0x2
// Reserved			 						0x3
#define DELIVERY_MODE_NMI					0x4
#define DELIVERY_MODE_INIT					0x5
#define DELIVERY_MODE_STARTUP				0x6
// Reserved									0x7

// System Programming Guide 3A, p. 9-31
#define DESTINATION_MODEL_CLUSTER			0x0
#define DESTINATION_MODEL_FLAT				0xf

// System Programming Guide 3A, p. 9-45
#define FOCUS_CPU_ENABLED					0x0
#define FOCUS_CPU_DISABLED					0x1

// System Programming Guide 3A, p. 9-45
#define LAPIC_DISABLED						0x0
#define LAPIC_ENABLED						0x1

// System Programming Guide 3A, p. 9-13
struct LAPICID_P // Pentium CPUs
{
	int	reserved_1:24,
		apic_id:4, // APIC ID
		reserved_2:4;
} __attribute__((packed));

// System Programming Guide 3A, p. 9-13
struct LAPICID_P4 // Pentium 4 and Xeon CPUs
{
	int	reserved_1:24,
		apic_id:8; // APIC ID
} __attribute__((packed));

// System Programming Guide 3A, p. 9-15
struct LAPICVER
{
	int	version:8, // Version (0x14 for P4s and Xeons)
		reserved_1:8,
		max_lvt_entry:8, // Maximum LVT Entry
		reserved_2:8;
} __attribute__((packed));

// System Programming Guide 3A, p. 9-24
struct ICR1
{
	int	vector:8, // Vector
		delivery_mode:3, // Delivery Mode
		destination_mode:1, // Destination Mode
		delivery_status:1, // Delivery Status
		reserved_1:1,
		level:1, // Level
		trigger_mode:1, // Trigger Mode
		reserved_2:2,
		destination_shorthand:2, // Destination Shorthand
		reserved_3:12;
} __attribute__((packed));

// System Programming Guide 3A, p. 9-24
struct ICR2
{
	int	reserved:24,
		destination_field:8; // Destination Field
} __attribute__((packed));

// System Programming Guide 3A, p. 9-31
struct LDR
{
	int reserved:24,
		lapic_id:8; // Logical APIC ID
} __attribute__((packed));

// System Programming Guide 3A, p. 9-31
struct DFR
{
	int reserved:28,
		model:4; // Model (Flat vs. Cluster)
} __attribute__((packed));

// System Programming Guide 3A, p. 9-33
struct APR
{
	int	arb_prio_sub:4, // Arbitration Priority Sub-Class
		arb_prio:4, // Arbitration Priority
		reserved:24;
} __attribute__((packed));

// System Programming Guide 3A, p. 9-39
struct TPR
{
	int task_prio_sub:4, // Task Priority Sub-Class
		task_prio:4, // Task Priority
		reserved:24;
} __attribute__((packed));

// System Programming Guide 3A, p. 9-39
struct PPR
{
	int processor_prio_sub:4, // Processor Priority Sub-Class
		processor_prio:4, // Processor Priority
		reserved:24;
} __attribute__((packed));

// System Programming Guide 3A, p. 9-45
struct SPIVR
{
	int spurious_vector:8, // Spurious Vector
		apic_enable:1, // APIC Software Enable/Disable
		focus_processor_checking:1, // Focus Processor Checking
		reserved:22;
} __attribute__((packed));

// global object declaration
extern LAPIC lapic;

#endif
