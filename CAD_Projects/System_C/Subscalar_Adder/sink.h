#ifndef SINK_H_INCLUDED
#define SINK_H_INCLUDED

#include "systemc.h"

class SINK_CONTROL:
public sc_module {

	public:

	// Ports
	sc_in < bool > Input;			// Sink
	sc_in <bool> clk;			// Clock

	// Processes
	void sink_thread(void);

	bool input_data;
	
	// Module constructor
	SC_HAS_PROCESS(SINK_CONTROL);
	SINK_CONTROL(sc_module_name name):
	sc_module(name) {
		SC_THREAD(sink_thread);
		sensitive << clk.neg();
	}
};

class SINK_PAIR:
public sc_module {

	public:

	// Ports
	sc_in < sc_uint < 2 > > Input;		// Sink
	sc_in <bool> clk;			// Clock

	// Processes
	void sink_thread(void);

	sc_uint < 2 > input_data;
	
	// Module constructor
	SC_HAS_PROCESS(SINK_PAIR);
	SINK_PAIR(sc_module_name name):
	sc_module(name) {
		SC_THREAD(sink_thread);
		sensitive << clk.neg();
	}
};

class SINK_NIBBLE:
public sc_module {

	public:

	// Ports
	sc_in < sc_uint < 4 > > Input;		// Sink
	sc_in <bool> clk;			// Clock

	// Processes
	void sink_thread(void);

	sc_uint < 4 > input_data;
	
	// Module constructor
	SC_HAS_PROCESS(SINK_NIBBLE);
	SINK_NIBBLE(sc_module_name name):
	sc_module(name) {
		SC_THREAD(sink_thread);
		sensitive << clk.neg();
	}
};

class SINK_BYTE:
public sc_module {

	public:

	// Ports
	sc_in < sc_uint < 8 > > Input;		// Sink
	sc_in <bool> clk;			// Clock

	// Processes
	void sink_thread(void);

	sc_uint < 8 > input_data;
	
	// Module constructor
	SC_HAS_PROCESS(SINK_BYTE);
	SINK_BYTE(sc_module_name name):
	sc_module(name) {
		SC_THREAD(sink_thread);
		sensitive << clk.neg();
	}
};

class SINK_DATA:
public sc_module {

	public:

	// Ports
	sc_in < sc_int < 32 > > Input;		// Sink
	sc_in <bool> clk;			// Clock

	// Processes
	void sink_thread(void);

	sc_int < 32 > input_data;
	
	// Module constructor
	SC_HAS_PROCESS(SINK_DATA);
	SINK_DATA(sc_module_name name):
	sc_module(name) {
		SC_THREAD(sink_thread);
		sensitive << clk.neg();
	}
};

#endif
