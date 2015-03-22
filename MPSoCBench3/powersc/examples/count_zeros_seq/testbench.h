#ifndef TESTBENCH_H
#define TESTBENCH_H

#include <systemc.h>

//#ifndef NO_PSC
//#ifndef SYNTHESIS
#include <powersc.h>
//#endif
//#endif


#ifndef SYNTHESIS
void elaborate_model( int sim_time );
#endif

const int CYCLES2WAIT = 3;
const int ZEROS_WIDTH = 4;
const int MAX_NUM = 2147483647;

SC_MODULE(testbench)
{
	// input ports
	sc_in<bool> clk;
	sc_in<sc_bit> data_ready;
	sc_in<sc_bit> is_legal;
	sc_in<sc_uint<ZEROS_WIDTH> > zeros;

	// output ports
	sc_out<sc_bit> reset;
	sc_out<sc_bit> data;
	sc_out<sc_bit> read;

	// processes
	void execute();

#ifdef SIM
	void comb();
#endif

	// methods
	void set_defaults();

	// member variables
	int cycle;
	int num_to_sent;
	int bindex; // bit index
	bool cur_bit;
	
	SC_CTOR(testbench)
	{
		SC_METHOD(execute);
		dont_initialize();
		sensitive_neg << clk;

#ifdef SIM
		SC_METHOD(comb);
		dont_initialize();
		sensitive << data_ready << is_legal << zeros;
#endif

		cycle = 0;
		cur_bit = 0;
		bindex = 0;
	}
};

#endif
