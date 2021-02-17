#include "register.h"

// Processes

void
REGISTER_CONTROL::
register_thread(void) {

	while (true) {
	
		wait (0, SC_NS);

		// Read data from input
		data = Input.read();

		// Wait for next clock
		wait();

		// Write data to output
		Output.write(data);
	}
}

void
REGISTER_PAIR::
register_thread(void) {

	while (true) {
	
		wait (0, SC_NS);

		// Read data from input
		data = Input.read();

		// Wait for next clock
		wait();

		// Write data to output
		Output.write(data);
	}
}

void
REGISTER_PAIR_SPLIT::
register_thread(void) {

	while (true) {
	
		wait (0, SC_NS);

		// Read data from input
		data = Input.read();

		// Wait for next clock
		wait();

		// Write data to output
		Output[ 0].write(data.range( 1,  0));
		Output[ 1].write(data.range( 3,  2));
		Output[ 2].write(data.range( 5,  4));
		Output[ 3].write(data.range( 7,  6));
		Output[ 4].write(data.range( 9,  8));
		Output[ 5].write(data.range(11, 10));
		Output[ 6].write(data.range(13, 12));
		Output[ 7].write(data.range(15, 14));
		Output[ 8].write(data.range(17, 16));
		Output[ 9].write(data.range(19, 18));
		Output[10].write(data.range(21, 20));
		Output[11].write(data.range(23, 22));
		Output[12].write(data.range(25, 24));
		Output[13].write(data.range(27, 26));
		Output[14].write(data.range(29, 28));
		Output[15].write(data.range(31, 30));
	}
}

void
REGISTER_NIBBLE::
register_thread(void) {

	while (true) {
	
		wait (0, SC_NS);

		// Read data from input
		data = Input.read();

		// Wait for next clock
		wait();

		// Write data to output
		Output.write(data);
	}
}

void
REGISTER_NIBBLE_SPLIT::
register_thread(void) {

	while (true) {
	
		wait (0, SC_NS);

		// Read data from input
		data = Input.read();

		// Wait for next clock
		wait();

		// Write data to output
		Output[0].write(data.range( 3,  0));
		Output[1].write(data.range( 7,  4));
		Output[2].write(data.range(11,  8));
		Output[3].write(data.range(15, 12));
		Output[4].write(data.range(19, 16));
		Output[5].write(data.range(23, 20));
		Output[6].write(data.range(27, 24));
		Output[7].write(data.range(31, 28));
	}
}

void
REGISTER_BYTE::
register_thread(void) {

	while (true) {
	
		wait (0, SC_NS);

		// Read data from input
		data = Input.read();

		// Wait for next clock
		wait();

		// Write data to output
		Output.write(data);
	}
}

void
REGISTER_BYTE_SPLIT::
register_thread(void) {

	while (true) {
	
		wait (0, SC_NS);

		// Read data from input
		data = Input.read();

		// Wait for next clock
		wait();

		// Write data to output
		Output[0].write(data.range( 7,  0));
		Output[1].write(data.range(15,  8));
		Output[2].write(data.range(23, 16));
		Output[3].write(data.range(31, 24));
	}
}

void
REGISTER_DATA::
register_thread(void) {

	while (true) {
	
		wait (0, SC_NS);

		// Read data from input
		data = Input.read();

		// Wait for next clock
		wait();

		// Write data to output
		Output.write(data);
	}
}
