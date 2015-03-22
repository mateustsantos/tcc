#include <systemc.h>
#include "testbench.h"

/*   main.cc
 *   sc_main() controls the simulation for drink_machine.cc
 *   It instantiates the DUT (drink_machine) and the testbench,
 *   traces several signals, and runs the simulation.
 */
int sc_main(int argc, char* argv[]) 
{
   int sim_time = 456789; // arbitrary

   run_experiment( sim_time );

	PSC_REPORT_SWITCHING_ACTIVITY;
  
   return( 0 );
}
