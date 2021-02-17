#ifndef ADD_H_INCLUDED
#define ADD_H_INCLUDED

#include "constant.h"
#include "padd.h"
#include "sink.h"

class ADD:
public sc_module {
	public:

	char stdbuf[256];

	// Ports
	sc_in < sc_uint < 4 > > Addend[8];	// Addends
	sc_in < sc_uint < 4 > > Augend[8];	// Augends
	sc_out < sc_uint < 4 > > Sum[8];	// Sums
	sc_in < bool > clk;			// clock

	// Signals
	sc_signal < sc_uint < 4 > > signal_padd[8];
	sc_signal < sc_uint < 4 > > signal_const_0;

	// Module declarations
	PADD* padd[8];
	CONSTANT_NIBBLE* const_0;
	SINK_NIBBLE* sink;

	ADD(sc_module_name name):
	sc_module(name) {

		// Module instantiations
		for (int i = 0; i < 8; i++) {
			sprintf(stdbuf, "padd(%d)", i);
			padd[i] = new PADD(stdbuf);
		}
		const_0 = new CONSTANT_NIBBLE("const_0", 0);
		sink = new SINK_NIBBLE("sink");

		// Connections
		padd[0]->Addend(Addend[0]);
		padd[0]->Augend(Augend[0]);
		padd[0]->Carry_in(signal_const_0);
		padd[0]->Sum(Sum[0]);
		padd[0]->Carry_out(signal_padd[0]);
		padd[0]->clk(clk);
		for (int i = 1; i < 8; i++) {
			padd[i]->Addend(Addend[i]);
			padd[i]->Augend(Augend[i]);
			padd[i]->Carry_in(signal_padd[i-1]);
			padd[i]->Sum(Sum[i]);
			padd[i]->Carry_out(signal_padd[i]);
			padd[i]->clk(clk);
		}
		const_0->Output(signal_const_0);
		const_0->clk(clk);
		sink->Input(signal_padd[7]);
		sink->clk(clk);
	}
};

#endif
