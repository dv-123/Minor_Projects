#include "constant.h"

// Processes

void
CONSTANT_CONTROL::
constant_thread (void) {

	while (true) {

		wait (0, SC_NS);

		// Wait for next clock
		wait();

		// Put the results on the output
		Output.write (value);
	}
}

void
CONSTANT_PAIR::
constant_thread (void) {

	while (true) {

		wait (0, SC_NS);

		// Wait for next clock
		wait();

		// Put the results on the output
		Output.write (value);
	}
}

void
CONSTANT_NIBBLE::
constant_thread (void) {

	while (true) {

		wait (0, SC_NS);

		// Wait for next clock
		wait();

		// Put the results on the output
		Output.write (value);
	}
}

void
CONSTANT_BYTE::
constant_thread (void) {

	while (true) {

		wait (0, SC_NS);

		// Wait for next clock
		wait();

		// Put the results on the output
		Output.write (value);
	}
}

void
CONSTANT_DATA::
constant_thread (void) {

	while (true) {

		wait (0, SC_NS);

		// Wait for next clock
		wait();

		// Put the results on the output
		Output.write (value);
	}
}
