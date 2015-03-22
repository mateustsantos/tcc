#ifndef TESTBENCH_H
#define TESTBENCH_H

#include <systemc.h>
#include <powersc.h>

#ifndef SYNTHESIS
void run_experiment( int );
#endif

const int WAIT_CYCLES = 1;
const int N_CH = 1;
const int MAX_DATA_VAL = 2147483647;

SC_MODULE(testbench)
{
	sc_in<bool> clk;
	
	// driver ports
	sc_in<sc_bit> duv_may_read;
	sc_out<sc_uint<2> > duv_in_nch; //number of channels
	sc_out<sc_bit> duv_reset_n;
	sc_out<sc_bit> data_available;
	sc_out<sc_uint<32> > data_out;

	// monitor ports
	sc_in<sc_bit> duv_done;
	sc_in<sc_uint<32> > data_in;
	sc_in<sc_uint<2> > duv_out_nch;
	sc_out<sc_bit> duv_may_write;
	
	// processes
	void generate_stimuli();
	void stimuli_response();

	// member variables and other stuff
	
	enum { reset_0, reset_1, pre_start, start_0, start_1, 
		send_0, send_1 } state_drv;

	enum { start, read_0, read_1 } state_mnt;
		
	int i, j, res;

	SC_CTOR(testbench)
	{
		SC_METHOD(generate_stimuli);
		sensitive_pos << clk;

		SC_METHOD(stimuli_response);
		sensitive_pos << clk;

		state_drv = reset_0;
		state_mnt = start;
	}
};

#endif
