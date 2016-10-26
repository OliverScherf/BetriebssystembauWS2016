/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                          S M P S Y S T E M                                */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Intel-MP-Spec references refer to the document "Intel MultiProcessor      */
/* Specification", version 1.4, May 1997.                                    */
/*****************************************************************************/

#ifndef __SMPSystem__
#define __SMPSystem__

#include "object/debug.h"

// maximum number of CPUs
#define CPU_MAX 8

class SMPSystem
{
	bool queryACPI(); //use ACPI to detect SMP system
	void disablePICs(); //disable PIC compatibility mode
public:
	unsigned int onlineCPUs; // running CPUs
	unsigned int numberOfCPUs; // number of CPUs present in the system
	unsigned int bspID; // local APIC ID of the bootstrap CPU
	unsigned char ioapicID; // the ID of the detected I/O APIC, needed for programming its ID register (default: 1)
	int compatibilityMode; // the compatibility mode that was detected (PIC, virtual wire, symmetric I/O)
	int cpuFamily[CPU_MAX]; // the CPU family per CPU
	int cpuModel[CPU_MAX]; // the CPU model per CPU
	unsigned int lapicID[CPU_MAX]; // local APIC IDs per CPU
	unsigned int lapicVersion[CPU_MAX]; // the version of the local APICs per CPU
	volatile char calloutVector[CPU_MAX]; // set by BSP to allow APs to init
	volatile char callinVector[CPU_MAX]; // set by APs to tell BSP they are running
	volatile unsigned char nextLogicalLAPICID; // the next logical ID set upon LAPIC setup (the ID, not the bitmask)

public:
	SMPSystem() : onlineCPUs(0), numberOfCPUs(0), bspID(0), ioapicID(1), nextLogicalLAPICID(0) {}

	bool isSMPSystem();
	bool bootCPU(unsigned int cpu_id, void *top_of_stack);
	unsigned char getCPUID();
	const char *getCPUModel(unsigned int cpuID);

	inline unsigned int getNumberOfCPUs() {
		return numberOfCPUs;
	}

	inline unsigned int getNumberOfOnlineCPUs() {
		return onlineCPUs;
	}

	inline unsigned char getIOAPICID() {
		return ioapicID;
	}

	inline void callin() {
		callinVector[getCPUID()] = 1;
	}

	inline void waitForCallout() {
		while (calloutVector[getCPUID()] == 0);
	}

	inline unsigned char getAndIncNextLogicalAPICID() {
		unsigned char res = nextLogicalLAPICID;
		nextLogicalLAPICID++;
		return res;
	}

private:
	bool mpbChecksumOK(unsigned char *start_address, int len);
	void readMPCT(struct mpcth *mpcth);
	bool searchConfig(unsigned long base, unsigned long length);
	void delay(unsigned int wraparounds);
};

// Intel MP Spec, p. 4-3
#define MPFPS_ID_SIGNATURE		(('_'<<24)|('P'<<16)|('M'<<8)|'_')

// Intel MP Spec, p. 4-4
#define COMPATIBILITY_PIC		(1 << 7)
#define COMPATIBILITY_VIRTWIRE		0x0

// Intel MP Spec, p. 4-7
#define MPCT_PROCESSOR			0x0
#define MPCT_BUS				0x1
#define MPCT_IOAPIC				0x2
#define MPCT_IOINT				0x3
#define MPCT_LINT				0x4

// Intel MP Spec, p. 4-8
#define CPU_ENABLED				0x1
#define CPU_BOOTPROCESSOR		0x2

// MP floating pointer structure
// Intel MP Spec, p. 4-3
struct mpfps
{
	char signature[4]; // signature "_MP_"
	unsigned int physptr; // physical address pointer (MP config table address)
	unsigned char length; // length of the structure in 16-byte units
	unsigned char spec_rev; // MP version (0x01 = 1.1; 0x04 = 1.4)
	unsigned char checksum;	// checksum (overall sum must be 0)
	unsigned char feature1; // =0: there is an MP config table; otherwise: default config
	unsigned char feature2;	// bit 7 set: IMCR and PIC mode; otherwise: virtual wire mode
	unsigned char feature3; // reserved (0)
	unsigned char feature4; // reserved (0)
	unsigned char feature5; // reserved (0)
};
ct_assert(sizeof(struct mpfps) == 4*4);

// MP config table header
// Intel MP Spec, p. 4-5
struct mpcth
{
	char signature[4]; // signature"PCMP"
	unsigned short length; // table length in bytes
	char spec_rev;
	char checksum;
	char oemid[8]; // system manufacturer ID
	char productid[12]; // product family ID
	unsigned int oemptr; // pointer to an OEM config table (0 if non-existent)
	unsigned short oemsize; // length of the OEM config table in bytes
	unsigned short count; // number of entries in the base table
	unsigned int lapic; // memory-mapped address of local APIC
	unsigned short exttbllen; // length of the extended entries in bytes
	char exttblchksum;
	char reserved; // reserved (0)
};
ct_assert(sizeof(struct mpcth) == 4*11);

// Intel MP Spec, p. 4-7
struct mpct_processor
{
	unsigned char type; // type = 0
	unsigned char lapicid;
	unsigned char lapicver;
	unsigned char cpuflag; // bit 0 (EN): enable/disable; bit 1 (BP): BSP/AP
	unsigned int cpusignature;
	unsigned int featureflags;
	unsigned int reserved[2];
};
ct_assert(sizeof(struct mpct_processor) == 4*5);

// Intel MP Spec, p. 4-10
struct mpct_bus
{
	unsigned char type; // type = 1
	unsigned char busid;
	unsigned char bustype[6];
};
ct_assert(sizeof(struct mpct_bus) == 4*2);

// Intel MP Spec, p. 4-12
struct mpct_ioapic
{
	unsigned char type; // type = 2
	unsigned char apicid;
	unsigned char apicver;
	unsigned char flags;
	unsigned int apicaddr;
};
ct_assert(sizeof(struct mpct_ioapic) == 4*2);

// Intel MP Spec, p. 4-13
struct mpct_int
{
	unsigned char type; // type = 3/4
	unsigned char irqtype;
	unsigned short irqflag;
	unsigned char srcbus;
	unsigned char srcbusirq;
	unsigned char dstapic;
	unsigned char dstirq;
};
ct_assert(sizeof(struct mpct_int) == 4*2);

// global object declaration
extern SMPSystem smp;

#endif
