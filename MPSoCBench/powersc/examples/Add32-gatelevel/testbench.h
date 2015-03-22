#ifndef testbench_h
#define testbench_h

#include <vector>
#include <systemc.h>
#include <powersc.h>

#include "add32.h"

using namespace std;

SC_MODULE(testbench)
{
	sc_in_clk clk;

	sc_signal<sc_uint<32> > a;
	sc_signal<sc_uint<32> > b;
	sc_signal<sc_uint<32> > out1;

	Add32 * dut;

	void proc();

	bool load_vectors(const char *fname);

	vector<int> stimuli_a;
	vector<int> stimuli_b;

	int count;
	int num_vectors;

	SC_CTOR(testbench)
	{
		SC_METHOD(proc);
		sensitive_neg << clk;
		dont_initialize();

		dut = new Add32("dut");
		dut->a(a);
		dut->b(b);
		dut->out1(out1);

		PSC_OBJ_ALIAS(a, "a");
		PSC_OBJ_ALIAS(b, "b");
		PSC_OBJ_ALIAS(out1, "out1");

		count = 0;
		num_vectors = 0;
	}

	~testbench()
	{
		delete(dut);
	}
};

#endif
