#include "led.h"

int sc_main(int argc, char**argv)
{
	// simulation time
   int sim_time = 5000000;

	// instantiate the module and run the simulation
	run_test(sim_time);

	// print out a report with the switching activity
	// gathered throughout the simulation
	PSC_REPORT_SWITCHING_ACTIVITY;

   return(0);
}
