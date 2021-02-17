#ifndef RESPONSE_H_INCLUDED
#define RESPONSE_H_INCLUDED

#include "systemc.h"

class RESPONSE:
public sc_module {

	public:

	// Ports
	sc_in < sc_uint < 4 > > Sum[8];		// Sums
	sc_in < bool > clk;			// Clock

	// Process declaration
	void response_thread(void);

	// Internal data
	sc_uint < 4 > sum_data[8];

	// Module Constructor
	SC_HAS_PROCESS(RESPONSE);
	RESPONSE(sc_module_name name):
	sc_module(name) {
		SC_THREAD(response_thread);
			sensitive << clk.neg();
	}
};

#endif
