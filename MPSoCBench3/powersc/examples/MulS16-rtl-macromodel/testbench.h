#ifndef testbench_h
#define testbench_h

#include <vector>
#include <string>
#include <systemc.h>
#include <powersc.h>

#include "parts.16.h"

using namespace std;

SC_MODULE(testbench)
{
	sc_in_clk clk;

	sc_signal<sc_int<16> > a;
	sc_signal<sc_int<16> > b;
	sc_signal<sc_int<32> > out1;

	// multiplicador de 16 bits com sinal
	MulS16 * dut;

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

		dut = new MulS16("dut");
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
