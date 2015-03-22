#include "testbench.h"

int sc_main( int argc, char **argv )
{
	int sim_time = 987654; // arbitrary
	
	elaborate_model( sim_time );

	PSC_REPORT_SWITCHING_ACTIVITY;
	
	return( 0 );
}
