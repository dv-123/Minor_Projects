#ifndef REGISTER_H_INCLUDED 
#define REGISTER_H_INCLUDED

#include "systemc.h"

class REGISTER_CONTROL:
public sc_module {

	public:

	// Ports
	sc_in < bool > Input;		// Control input
	sc_out < bool > Output;		// Control output
	sc_in < bool > clk;		// Clock

	// Process declaration
	void register_thread(void);

	// Internal data
	bool data;

	// Module Constructor
	SC_HAS_PROCESS(REGISTER_CONTROL);
	REGISTER_CONTROL(sc_module_name) {
		SC_THREAD(register_thread);
		sensitive << clk.neg();
	}
};

class REGISTER_PAIR:
public sc_module {

	public:

	// Ports
	sc_in < sc_uint < 2 > > Input;		// Data input
	sc_out < sc_uint < 2 > > Output;	// Data output
	sc_in < bool > clk;			// Clock

	// Process declaration
	void register_thread(void);

	// Internal data
	sc_uint < 2 > data;

	// Module Constructor
	SC_HAS_PROCESS(REGISTER_PAIR);
	REGISTER_PAIR(sc_module_name) {
		SC_THREAD(register_thread);
		sensitive << clk.neg();
	}
};

class REGISTER_PAIR_SPLIT:
public sc_module {

	public:

	// Ports
	sc_in < sc_uint < 32 > > Input;		// Data input
	sc_out < sc_uint < 2 > > Output[16];	// Data outputs
	sc_in < bool > clk;			// Clock

	// Process declaration
	void register_thread(void);

	// Internal data
	sc_uint < 32 > data;

	// Module Constructor
	SC_HAS_PROCESS(REGISTER_PAIR_SPLIT);
	REGISTER_PAIR_SPLIT(sc_module_name) {
		SC_THREAD(register_thread);
		sensitive << clk.neg();
	}
};

class REGISTER_NIBBLE:
public sc_module {

	public:

	// Ports
	sc_in < sc_uint < 4 > > Input;		// Data input
	sc_out < sc_uint < 4 > > Output;	// Data output
	sc_in < bool > clk;			// Clock

	// Process declaration
	void register_thread(void);

	// Internal data
	sc_uint < 4 > data;

	// Module Constructor
	SC_HAS_PROCESS(REGISTER_NIBBLE);
	REGISTER_NIBBLE(sc_module_name) {
		SC_THREAD(register_thread);
		sensitive << clk.neg();
	}
};

class REGISTER_NIBBLE_SPLIT:
public sc_module {

	public:

	// Ports
	sc_in < sc_uint < 32 > > Input;		// Data input
	sc_out < sc_uint < 4 > > Output[8];	// Data outputs
	sc_in < bool > clk;			// Clock

	// Process declaration
	void register_thread(void);

	// Internal data
	sc_uint < 32 > data;

	// Module Constructor
	SC_HAS_PROCESS(REGISTER_NIBBLE_SPLIT);
	REGISTER_NIBBLE_SPLIT(sc_module_name) {
		SC_THREAD(register_thread);
		sensitive << clk.neg();
	}
};

class REGISTER_BYTE:
public sc_module {

	public:

	// Ports
	sc_in < sc_uint < 8 > > Input;		// Data input
	sc_out < sc_uint < 8 > > Output;	// Data output
	sc_in < bool > clk;			// Clock

	// Process declaration
	void register_thread(void);

	// Internal data
	sc_uint < 8 > data;

	// Module Constructor
	SC_HAS_PROCESS(REGISTER_BYTE);
	REGISTER_BYTE(sc_module_name) {
		SC_THREAD(register_thread);
		sensitive << clk.neg();
	}
};

class REGISTER_BYTE_SPLIT:
public sc_module {

	public:

	// Ports
	sc_in < sc_uint < 32 > > Input;		// Data input
	sc_out < sc_uint < 8 > > Output[4];	// Data outputs
	sc_in < bool > clk;			// Clock

	// Process declaration
	void register_thread(void);

	// Internal data
	sc_uint < 32 > data;

	// Module Constructor
	SC_HAS_PROCESS(REGISTER_BYTE_SPLIT);
	REGISTER_BYTE_SPLIT(sc_module_name) {
		SC_THREAD(register_thread);
		sensitive << clk.neg();
	}
};

class REGISTER_DATA:
public sc_module {

	public:

	// Ports
	sc_in < sc_int < 32 > > Input;		// Data input
	sc_out < sc_int < 32 > > Output;	// Data output
	sc_in < bool > clk;			// Clock

	// Process declaration
	void register_thread(void);

	// Internal data
	sc_int < 32 > data;

	// Module Constructor
	SC_HAS_PROCESS(REGISTER_DATA);
	REGISTER_DATA(sc_module_name) {
		SC_THREAD(register_thread);
		sensitive << clk.neg();
	}
};

#endif
