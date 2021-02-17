#include "response.h"

// Processes
void 
RESPONSE::
response_thread(void) {

	wait();
	
	while (true) {
	
		wait(0, SC_NS);
		
		// Read the input
		for (int i = 0; i < 8; i++) {
			sum_data[i] = Sum[i].read();
		}

		// Wait for next clock
		wait();
	}
}
