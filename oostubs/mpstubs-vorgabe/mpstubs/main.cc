// Bereits in OO-StuBS vorhandene Header
#include "device/keyboard.h"
#include "device/cgastr.h"
#include "machine/pic.h"
#include "machine/cpu.h"                
#include "machine/plugbox.h"
#include "guard/guard.h"

// Neue Header für MP-StuBS
#include "object/debug.h"
#include "machine/smpsys.h"
#include "machine/lapic.h"
#include "machine/ioapic.h"
#include "machine/spinlock.h"

Plugbox plugbox;                
PIC pic;
CPU cpu;
CGA_Stream kout;
Keyboard keyboard;
Guard guard;

Spinlock kout_lock;


//static unsigned long appl_stack[1024];        
int cpu_stack[ 8 * CPU_MAX]; // 1K Stack fuer max. 8 CPUs


/* main-Funktion für den Bootstrapprozessor */
extern "C" int main()
{
    keyboard.Keyboard::plugin();

    /* Pruefen ob wir ein SMP-System haben.
       Falls ja, werden die anderen CPUs gebootet, sowie
       benötigte Geräteinterrupts im IOAPIC initialisiert */

    bool isSMP = smp.isSMPSystem();
    unsigned int numCPUs = smp.getNumberOfCPUs();
	
    if (isSMP) {
	for (unsigned int i = 0; i < numCPUs; i++)
	    smp.bootCPU(i, &(cpu_stack[(i+1)*256]));

	ioapic.init();
	ioapic.activateKeyboard();
	//ioapic.activateTimer(true); // wenn wir auf echter HW laufen
	//ioapic.activateTimer(false); // wenn wir in qemu laufen
    }
	
		
    LOCK
    DBG << "Number of online CPUs: " << smp.getNumberOfOnlineCPUs() << endl;
    UNLOCK

    cpu.enable_int();

    /*
     * Hier könnt ihr loslegen...
     */

    for (;;);

    return 0;
}


/* main-Funktion für die anderen (Applikations-)Prozessoren */
extern "C" int main_ap()
{
    // Nachdem der Prozessor aufgeweckt wurde
    smp.waitForCallout();

    unsigned char llapic_id = (1 << smp.getAndIncNextLogicalAPICID());
    
    LOCK
    DBG << "CPU " << (int) smp.getCPUID() << " got called out, setting logical APIC ID to " << (int) llapic_id << endl;
    UNLOCK

    lapic.init();
    lapic.setLogicalLAPICID(llapic_id);
	
    /* Nachdem der Prozessor aufgeweckt wurde, meldet er dem ersten, dass er
     * sich 
     * konfiguriert hat und nun bereit ist */

    smp.callin();
    
    cpu.enable_int();

    /*
     * Hier könnt ihr loslegen...
     */

    for (;;);

    return 0;
}

