#include "padd.h"

// Processes

void
PADD::
padd_thread(void) {

	while (true) {

		wait (0, SC_NS);

		// Read inputs
		addend_data = Addend.read();
		augend_data = Augend.read();
		carry_in_data = Carry_in.read();

		// Wait for next event
		wait();

		// Determine output
		temporary_data = addend_data + augend_data + carry_in_data;
		sum_data = temporary_data.range(3, 0);
		carry_out_data = temporary_data.range(7, 4);

		// Put the results on output
		Sum.write(sum_data);
		Carry_out.write(carry_out_data);
        }
}
