#include <systemc.h>
#include "testbench.h"

int sc_main(int argc, char **argv)
{
   int sim_time = 9876543; // arbitrary

	run_experiment( sim_time );
	
	PSC_REPORT_SWITCHING_ACTIVITY;

	return(0);
}
