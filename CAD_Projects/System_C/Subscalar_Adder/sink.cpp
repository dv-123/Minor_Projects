#include "sink.h"

// Processes

void 
SINK_CONTROL::
sink_thread(void) {

	while (true) {

		wait (0, SC_NS);

		// Read input
		input_data = Input.read();

		// Wait for new event
		wait();
	}
}

void 
SINK_PAIR::
sink_thread(void) {

	while (true) {

		wait (0, SC_NS);

		// Read input
		input_data = Input.read();

		// Wait for new event
		wait();
	}
}

void 
SINK_NIBBLE::
sink_thread(void) {

	while (true) {

		wait (0, SC_NS);

		// Read input
		input_data = Input.read();

		// Wait for new event
		wait();
	}
}

void 
SINK_BYTE::
sink_thread(void) {

	while (true) {

		wait (0, SC_NS);

		// Read input
		input_data = Input.read();

		// Wait for new event
		wait();
	}
}

void 
SINK_DATA::
sink_thread(void) {

	while (true) {

		wait (0, SC_NS);

		// Read input
		input_data = Input.read();

		// Wait for new event
		wait();
	}
}
