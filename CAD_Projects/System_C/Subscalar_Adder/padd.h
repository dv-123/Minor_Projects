#ifndef PADD_H_INCLUDED
#define PADD_H_INCLUDED

#include "systemc.h"

class PADD:
public sc_module {

	public:

	// Ports
	sc_in < sc_uint < 4 > > Addend;		// Addend
	sc_in < sc_uint < 4 > > Augend;		// Augend
	sc_in < sc_uint < 4 > > Carry_in;	// Carry in
	sc_out < sc_uint < 4 > > Sum;		// Sum
	sc_out < sc_uint < 4 > > Carry_out;	// Carry out
	sc_in < bool > clk;			// Clock

	// Processes
	void padd_thread(void);

	// Internal data
	sc_uint < 4 > addend_data;
	sc_uint < 4 > augend_data;
	sc_uint < 4 > carry_in_data;
	sc_uint < 4 > sum_data;
	sc_uint < 4 > carry_out_data;
	sc_uint < 8 > temporary_data;

	// Module constructor
	SC_HAS_PROCESS(PADD);
	PADD(sc_module_name name):
	sc_module(name) {
		SC_THREAD(padd_thread);
		sensitive << clk.neg();
	}
};

#endif
