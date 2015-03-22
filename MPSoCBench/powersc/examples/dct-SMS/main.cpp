#include <systemc.h>
#include "testbench.h"

#define N_ARGS	3

int sc_main(int argc, char **argv)
{
   if (argc != N_ARGS) {
      cerr << "- Brazil-IP Fenix MP3 - DCT Module -" << endl;
      cerr << "Usage: " << argv[0] << " <input file> [status quo file]" << endl;
      return(-1);
   }

   const char *fname = argv[1];

// the line below is commented out so as to enable the SMS mechanism
#if 0
	PSC_FULL_SAMPLING;
#endif

	run_experiment( fname, argv[2] );
   
   PSC_REPORT_SWITCHING_ACTIVITY;

	return(0);
}
