#ifndef STIMULUS_H_INCLUDED
#define STIMULUS_H_INCLUDED

#include "systemc.h"

class STIMULUS:
public sc_module {

	public:

	// Ports
	sc_out < sc_uint < 32 > > Addend;			// Addend
	sc_out < sc_uint < 32 > > Augend;			// Augend
	sc_in < bool > clk;					// Clock

	// Process declaration
	void stimulus_thread(void);

	// Internal data
	sc_uint < 32 > addend_data;
	sc_uint < 32 > augend_data;
    
	// Module constructor
	SC_HAS_PROCESS (STIMULUS);
	STIMULUS (sc_module_name name):
	sc_module (name) {
		SC_THREAD(stimulus_thread);
		sensitive << clk.neg();
	}
};

#endif
