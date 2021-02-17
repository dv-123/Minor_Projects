#include "stimulus.h"

// Processes

void 
STIMULUS::
stimulus_thread(void) {

	wait(0, SC_NS);

	// Initialize and put the results on the output
	addend_data = 0x0;
	Addend.write(addend_data);
	augend_data = 0x0;
	Augend.write(augend_data);

	wait();

	// Forever generate pseudo random numbers and put them on the inputs
	while(true) {

		wait(0, SC_NS);

		addend_data = rand()%65536;
		if (addend_data[15] == 1) {
			addend_data.range(19,16) = 15;
			addend_data.range(23,20) = 15;
			addend_data.range(27,24) = 15;
			addend_data.range(31,28) = 15;
		}
		Addend.write(addend_data);
		augend_data = rand()%65536;
		if (augend_data[15] == 1) {
			augend_data.range(19,16) = 15;
			augend_data.range(23,20) = 15;
			augend_data.range(27,24) = 15;
			augend_data.range(31,28) = 15;
		}
		Augend.write(augend_data);

		wait();
	}
}
