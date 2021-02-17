#include "stimulus.h"
#include "delay.h"
#include "add.h"
#include "response.h"

int
sc_main(int argc, char *argv[])
{
	char stdbuf[256];
	
	sc_report_handler::
	set_actions("/IEEE_Std_1666/deprecated", SC_DO_NOTHING);

	// Signals
	sc_signal < sc_uint < 32 > > signal_stimulus_addend;
	sc_signal < sc_uint < 32 > > signal_stimulus_augend;
	sc_signal < sc_uint < 4 > > signal_stimulus_add_addend[8];
	sc_signal < sc_uint < 4 > > signal_stimulus_add_augend[8];
	sc_signal < sc_uint < 4 > > signal_delay[21];
	sc_signal < sc_uint < 4 > > signal_add_sum[8];

	// Module declarations
	STIMULUS* stimulus;
	REGISTER_NIBBLE_SPLIT* register_split_addend;
	REGISTER_NIBBLE_SPLIT* register_split_augend;
	DELAY_NIBBLE* delay[21];
	ADD* add;
	RESPONSE* response;
	
	// Module instantiations
	stimulus = new STIMULUS("stimulus");
	register_split_addend = new REGISTER_NIBBLE_SPLIT
		("register_split_addend");
	register_split_augend = new REGISTER_NIBBLE_SPLIT 
		("register_split_augend");
	add = new ADD("add");
	delay[ 0] = new DELAY_NIBBLE("delay(0)",  1);
	delay[ 1] = new DELAY_NIBBLE("delay(1)",  2);
	delay[ 2] = new DELAY_NIBBLE("delay(2)",  3);
	delay[ 3] = new DELAY_NIBBLE("delay(3)",  4);
	delay[ 4] = new DELAY_NIBBLE("delay(4)",  5);
	delay[ 5] = new DELAY_NIBBLE("delay(5)",  6);
	delay[ 6] = new DELAY_NIBBLE("delay(6)",  7);
	delay[ 7] = new DELAY_NIBBLE("delay(7)",  1);
	delay[ 8] = new DELAY_NIBBLE("delay(8)",  2);
	delay[ 9] = new DELAY_NIBBLE("delay(9)",  3);
	delay[10] = new DELAY_NIBBLE("delay(10)", 4);
	delay[11] = new DELAY_NIBBLE("delay(11)", 5);
	delay[12] = new DELAY_NIBBLE("delay(12)", 6);
	delay[13] = new DELAY_NIBBLE("delay(13)", 7);
	delay[14] = new DELAY_NIBBLE("delay(14)", 7);
	delay[15] = new DELAY_NIBBLE("delay(15)", 6);
	delay[16] = new DELAY_NIBBLE("delay(16)", 5);
	delay[17] = new DELAY_NIBBLE("delay(17)", 4);
	delay[18] = new DELAY_NIBBLE("delay(18)", 3);
	delay[19] = new DELAY_NIBBLE("delay(19)", 2);
	delay[20] = new DELAY_NIBBLE("delay(20)", 1);
	response = new RESPONSE("response");

	sc_clock clk("clock", 2, 0.5, 0, false);	// Clock

	// Connections
	// stimulus
	stimulus->Addend(signal_stimulus_addend);
	stimulus->Augend(signal_stimulus_augend);
	stimulus->clk(clk);
	// register_split_addend
	register_split_addend->Input(signal_stimulus_addend);
	for (int i = 0; i < 8; i++)
		register_split_addend->Output[i](signal_stimulus_add_addend[i]);
	register_split_addend->clk(clk);
	// register_split_augend
	register_split_augend->Input(signal_stimulus_augend);
	for (int i = 0; i < 8; i++)
		register_split_augend->Output[i](signal_stimulus_add_augend[i]);
	register_split_augend->clk(clk);
	delay[ 0]->Input(signal_stimulus_add_addend[1]);
	delay[ 0]->Output(signal_delay[0]);
	delay[ 0]->clk(clk);
	delay[ 1]->Input(signal_stimulus_add_addend[2]);
	delay[ 1]->Output(signal_delay[1]);
	delay[ 1]->clk(clk);
	delay[ 2]->Input(signal_stimulus_add_addend[3]);
	delay[ 2]->Output(signal_delay[2]);
	delay[ 2]->clk(clk);
	delay[ 3]->Input(signal_stimulus_add_addend[4]);
	delay[ 3]->Output(signal_delay[3]);
	delay[ 3]->clk(clk);
	delay[ 4]->Input(signal_stimulus_add_addend[5]);
	delay[ 4]->Output(signal_delay[4]);
	delay[ 4]->clk(clk);
	delay[ 5]->Input(signal_stimulus_add_addend[6]);
	delay[ 5]->Output(signal_delay[5]);
	delay[ 5]->clk(clk);
	delay[ 6]->Input(signal_stimulus_add_addend[7]);
	delay[ 6]->Output(signal_delay[6]);
	delay[ 6]->clk(clk);
	delay[ 7]->Input(signal_stimulus_add_augend[1]);
	delay[ 7]->Output(signal_delay[7]);
	delay[ 7]->clk(clk);
	delay[ 8]->Input(signal_stimulus_add_augend[2]);
	delay[ 8]->Output(signal_delay[8]);
	delay[ 8]->clk(clk);
	delay[ 9]->Input(signal_stimulus_add_augend[3]);
	delay[ 9]->Output(signal_delay[9]);
	delay[ 9]->clk(clk);
	delay[10]->Input(signal_stimulus_add_augend[4]);
	delay[10]->Output(signal_delay[10]);
	delay[10]->clk(clk);
	delay[11]->Input(signal_stimulus_add_augend[5]);
	delay[11]->Output(signal_delay[11]);
	delay[11]->clk(clk);
	delay[12]->Input(signal_stimulus_add_augend[6]);
	delay[12]->Output(signal_delay[12]);
	delay[12]->clk(clk);
	delay[13]->Input(signal_stimulus_add_augend[7]);
	delay[13]->Output(signal_delay[13]);
	delay[13]->clk(clk);
	delay[14]->Input(signal_add_sum[0]);
	delay[14]->Output(signal_delay[14]);
	delay[14]->clk(clk);
	delay[15]->Input(signal_add_sum[1]);
	delay[15]->Output(signal_delay[15]);
	delay[15]->clk(clk);
	delay[16]->Input(signal_add_sum[2]);
	delay[16]->Output(signal_delay[16]);
	delay[16]->clk(clk);
	delay[17]->Input(signal_add_sum[3]);
	delay[17]->Output(signal_delay[17]);
	delay[17]->clk(clk);
	delay[18]->Input(signal_add_sum[4]);
	delay[18]->Output(signal_delay[18]);
	delay[18]->clk(clk);
	delay[19]->Input(signal_add_sum[5]);
	delay[19]->Output(signal_delay[19]);
	delay[19]->clk(clk);
	delay[20]->Input(signal_add_sum[6]);
	delay[20]->Output(signal_delay[20]);
	delay[20]->clk(clk);
	// add
	add->Addend[0](signal_stimulus_add_addend[0]);
	add->Augend[0](signal_stimulus_add_augend[0]);
	add->Sum[0](signal_add_sum[0]);
	add->Addend[1](signal_delay[0]);
	add->Augend[1](signal_delay[7]);
	add->Sum[1](signal_add_sum[1]);
	add->Addend[2](signal_delay[1]);
	add->Augend[2](signal_delay[8]);
	add->Sum[2](signal_add_sum[2]);
	add->Addend[3](signal_delay[2]);
	add->Augend[3](signal_delay[9]);
	add->Sum[3](signal_add_sum[3]);
	add->Addend[4](signal_delay[3]);
	add->Augend[4](signal_delay[10]);
	add->Sum[4](signal_add_sum[4]);
	add->Addend[5](signal_delay[4]);
	add->Augend[5](signal_delay[11]);
	add->Sum[5](signal_add_sum[5]);
	add->Addend[6](signal_delay[5]);
	add->Augend[6](signal_delay[12]);
	add->Sum[6](signal_add_sum[6]);
	add->Addend[7](signal_delay[6]);
	add->Augend[7](signal_delay[13]);
	add->Sum[7](signal_add_sum[7]);
	add->clk(clk);
	// response
	response->Sum[0](signal_delay[14]);
	response->Sum[1](signal_delay[15]);
	response->Sum[2](signal_delay[16]);
	response->Sum[3](signal_delay[17]);
	response->Sum[4](signal_delay[18]);
	response->Sum[5](signal_delay[19]);
	response->Sum[6](signal_delay[20]);
	response->Sum[7](signal_add_sum[7]);
	response->clk(clk);

	// Tracing
	sc_trace_file* tf;
	tf = sc_create_vcd_trace_file("add");
        tf->set_time_unit(1, SC_NS);

	sc_trace(tf, clk, "clock");
	sc_trace(tf, stimulus->addend_data, "addend");
	sc_trace(tf, stimulus->augend_data, "augend");
	for (int i = 0; i < 8; i++) { 
		sprintf (stdbuf, "sum(%d)", i);
		sc_trace(tf, response->sum_data[i], stdbuf);
	}

	// Simulation
	int sim_time = 100;
	if (argc == 2)
		sim_time = atoi(argv[1]);

	sc_start(sim_time, SC_NS);

	// sc_close_vcd_trace_file(tf);

	return 0;
}
