#ifndef CONSTANT_H_INCLUDED
#define CONSTANT_H_INCLUDED

#include "systemc.h"

class CONSTANT_CONTROL:
public sc_module {

	public:

	// Ports
	sc_out < bool > Output;			// Output
	sc_in < bool >	clk;			// Clock

	// Process declaration
	void constant_thread(void);

	// Internal data
	bool value;

	// Module constructor
	SC_HAS_PROCESS(CONSTANT_CONTROL);
	CONSTANT_CONTROL(sc_module_name name, bool Value):
	sc_module(name) {
		SC_THREAD(constant_thread);
		sensitive << clk.neg();
		value = Value;
	}
};

class CONSTANT_PAIR:
public sc_module {

	public:

	// Ports
	sc_out < sc_uint < 2 > > Output;	// Output
	sc_in < bool >	clk;			// Clock

	// Process declaration
	void constant_thread(void);

	// Internal data
	sc_uint < 2 > value;

	// Module constructor
	SC_HAS_PROCESS(CONSTANT_PAIR);
	CONSTANT_PAIR(sc_module_name name, sc_int < 2 > Value):
	sc_module(name){
		SC_THREAD(constant_thread);
		sensitive << clk.neg();
		value = Value;
	}
};

class CONSTANT_NIBBLE:
public sc_module {

	public:

	// Ports
	sc_out < sc_uint < 4 > > Output;	// Output
	sc_in < bool >	clk;			// Clock

	// Process declaration
	void constant_thread(void);

	// Internal data
	sc_uint < 4 > value;

	// Module constructor
	SC_HAS_PROCESS (CONSTANT_NIBBLE);
	CONSTANT_NIBBLE (sc_module_name name, sc_int < 4 > Value):
	sc_module(name) {
		SC_THREAD(constant_thread);
		sensitive << clk.neg();
		value = Value;
	}
};

class CONSTANT_BYTE:
public sc_module {

	public:

	// Ports
	sc_out < sc_uint < 8 > > Output;	// Output
	sc_in < bool >	clk;			// Clock

	// Process declaration
	void constant_thread(void);

	// Internal data
	sc_uint < 8 > value;

	// Module constructor
	SC_HAS_PROCESS(CONSTANT_BYTE);
	CONSTANT_BYTE(sc_module_name name, sc_int < 8 > Value):
	sc_module(name){
		SC_THREAD(constant_thread);
		sensitive << clk.neg();
		value = Value;
	}
};

class CONSTANT_DATA:
public sc_module {

	public:

	// Ports
	sc_out < sc_int < 32 > > Output;	// Output
	sc_in < bool >	clk;			// Clock

	// Process declaration
	void constant_thread(void);

	// Internal data
	sc_int < 32 > value;

	// Module constructor
	SC_HAS_PROCESS(CONSTANT_DATA);
	CONSTANT_DATA(sc_module_name name, sc_int < 32 > Value):
	sc_module(name) {
		SC_THREAD(constant_thread);
		sensitive << clk.neg();
		value = Value;
	}
};

#endif
