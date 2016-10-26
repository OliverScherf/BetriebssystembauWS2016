/*****************************************************************************/
/* Betriebssysteme                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                         S P I N L O C K                                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/* Implementierung einer Klasse fuer Spinlocks.                              */
/*****************************************************************************/

#ifndef __Spinlock_include__
#define __Spinlock_include__

class Spinlock 
{
private:
	volatile unsigned int lock_status;

public: 	
	Spinlock() : lock_status(0) {}
	
	void lock() {
        	while ( !take_if_free() ) {
			; // spin
		}
	}
	
	void unlock() {
		lock_status = 0;
	}
	
	unsigned int get_status() {
		return lock_status;
	}

	bool take_if_free() {	// returns true if successful, otherwise false
		return ( __sync_lock_test_and_set(&lock_status,1) == 0 );
	}
	
};
 
#endif
