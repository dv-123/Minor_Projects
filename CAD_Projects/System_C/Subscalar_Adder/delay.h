#ifndef DELAY_H_INCLUDED
#define DELAY_H_INCLUDED

#include "systemc.h"
#include "register.h"

class DELAY_CONTROL:
public sc_module {

	public:

	char stdbuf[265];

	// Ports
	sc_in < bool > Input;			// Input
	sc_out < bool > Output;			// Output
	sc_in < bool >	clk;			// Clock

	// Signals
	sc_signal < bool >* signal_delay;

	// Module declarations
	REGISTER_CONTROL** reg;

	// Module constructor
	DELAY_CONTROL(sc_module_name name, int cycles):
	sc_module(name) {

		// Module instantiations
		reg = new REGISTER_CONTROL*[cycles];
		for (int i = 0; i < cycles; i++) {
			sprintf (stdbuf, "reg(%d)", i);
			reg[i] = new REGISTER_CONTROL(stdbuf);
		}
		signal_delay = new sc_signal < bool >[cycles];

		// Connections
		reg[0]->Input(Input);
		for (int i = 0; i < cycles-1; i++) {
			reg[i]->Output(signal_delay[i]);
		}
		for (int i = 1; i < cycles; i++) {
			reg[i]->Input(signal_delay[i-1]);
		}
		reg[cycles-1]->Output(Output);
		for (int i = 0; i < cycles; i++) {
			reg[i]->clk(clk);
		}
	}
};

class DELAY_PAIR:
public sc_module {

	public:

	char stdbuf[265];

	// Ports
	sc_in < sc_uint < 2 > > Input;		// Input
	sc_out < sc_uint < 2 > > Output;	// Output
	sc_in < bool >	clk;			// Clock

	// Signals
	sc_signal < sc_uint < 2 > >* signal_delay;

	// Module declarations
	REGISTER_PAIR** reg;

	// Module constructor
	DELAY_PAIR(sc_module_name name, int cycles):
	sc_module(name) {

		// Module instantiations
		reg = new REGISTER_PAIR*[cycles];
		for (int i = 0; i < cycles; i++) {
			sprintf (stdbuf, "reg(%d)", i);
			reg[i] = new REGISTER_PAIR(stdbuf);
		}
		signal_delay = new sc_signal < sc_uint < 2 > >[cycles];

		// Connections
		reg[0]->Input(Input);
		for (int i = 0; i < cycles-1; i++) {
			reg[i]->Output(signal_delay[i]);
		}
		for (int i = 1; i < cycles; i++) {
			reg[i]->Input(signal_delay[i-1]);
		}
		reg[cycles-1]->Output(Output);
		for (int i = 0; i < cycles; i++) {
			reg[i]->clk(clk);
		}
	}
};

class DELAY_NIBBLE:
public sc_module {

	public:

	char stdbuf[265];

	// Ports
	sc_in < sc_uint < 4 > > Input;		// Input
	sc_out < sc_uint < 4 > > Output;	// Output
	sc_in < bool >	clk;			// Clock

	// Signals
	sc_signal < sc_uint < 4 > >* signal_delay;

	// Module declarations
	REGISTER_NIBBLE** reg;

	// Module constructor
	DELAY_NIBBLE (sc_module_name name, int cycles):
	sc_module (name) {

		// Module instantiations
		reg = new REGISTER_NIBBLE*[cycles];
		for (int i = 0; i < cycles; i++) {
			sprintf (stdbuf, "reg(%d)", i);
			reg[i] = new REGISTER_NIBBLE(stdbuf);
		}
		signal_delay = new sc_signal < sc_uint < 4 > >[cycles];

		// Connections
		reg[0]->Input(Input);
		for (int i = 0; i < cycles-1; i++) {
			reg[i]->Output(signal_delay[i]);
		}
		for (int i = 1; i < cycles; i++) {
			reg[i]->Input(signal_delay[i-1]);
		}
		reg[cycles-1]->Output(Output);
		for (int i = 0; i < cycles; i++) {
			reg[i]->clk(clk);
		}
	}
};

class DELAY_BYTE:
public sc_module {

	public:

	char stdbuf[265];

	// Ports
	sc_in < sc_uint < 8 > > Input;		// Input
	sc_out < sc_uint < 8 > > Output;	// Output
	sc_in < bool >	clk;			// Clock

	// Signals
	sc_signal < sc_uint < 8 > >* signal_delay;

	// Module declarations
	REGISTER_BYTE** reg;

	// Module constructor
	DELAY_BYTE(sc_module_name name, int cycles):
	sc_module(name) {

		// Module instantiations
		reg = new REGISTER_BYTE*[cycles];
		for (int i = 0; i < cycles; i++) {
			sprintf (stdbuf, "reg(%d)", i);
			reg[i] = new REGISTER_BYTE(stdbuf);
		}
		signal_delay = new sc_signal < sc_uint < 8 > >[cycles];

		// Connections
		reg[0]->Input(Input);
		for (int i = 0; i < cycles-1; i++) {
			reg[i]->Output(signal_delay[i]);
		}
		for (int i = 1; i < cycles; i++) {
			reg[i]->Input(signal_delay[i-1]);
		}
		reg[cycles-1]->Output(Output);
		for (int i = 0; i < cycles; i++) {
			reg[i]->clk(clk);
		}
	}
};

class DELAY_DATA:
public sc_module {

	public:

	char stdbuf[265];

	// Ports
	sc_in < sc_int < 32 > > Input;		// Input
	sc_out < sc_int < 32 > > Output;	// Output
	sc_in < bool >	clk;			// Clock

	// Signals
	sc_signal < sc_int < 32 > >* signal_delay;

	// Module declarations
	REGISTER_DATA** reg;

	// Module constructor
	DELAY_DATA(sc_module_name name, int cycles):
	sc_module(name) {

		// Module instantiations
		reg = new REGISTER_DATA*[cycles];
		for (int i = 0; i < cycles; i++) {
			sprintf (stdbuf, "reg(%d)", i);
			reg[i] = new REGISTER_DATA(stdbuf);
		}
		signal_delay = new sc_signal < sc_int < 32 > >[cycles];

		// Connections
		reg[0]->Input(Input);
		for (int i = 0; i < cycles-1; i++) {
			reg[i]->Output(signal_delay[i]);
		}
		for (int i = 1; i < cycles; i++) {
			reg[i]->Input(signal_delay[i-1]);
		}
		reg[cycles-1]->Output(Output);
		for (int i = 0; i < cycles; i++) {
			reg[i]->clk(clk);
		}
	}
};

#endif
