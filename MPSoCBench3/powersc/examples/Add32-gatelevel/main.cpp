#include "testbench.h"

void go(const char *infile)
{
	sc_clock clk("clk", sc_time(10, SC_NS) );

	testbench tb0("tb0");
	tb0.clk(clk);

	if (! tb0.load_vectors(infile)) {
		fprintf(stderr, "ERROR: the file '%s' could not be opened\n", infile);
		exit(-2);
	}

	sc_start(-1);

	cout << "Simulation time: " << sc_time_stamp() << endl;
}

void print_usage(char **argv, int exit_code)
{
  fprintf(stderr,
	  "Add32 -- gate-level example\n"
	  "http://www.lsc.ic.unicamp.br\n\n"
	  "Usage: %s [options]\n"
	  "- options:\n"
	  "    -i <file name>     Input vectors file\n"
	  "    -h                 Print this message and quit\n"
          "\n\n", 
	  argv[0]
	  );

  exit(exit_code);
}

int sc_main(int argc, char **argv)
{
	const char *infile;
	const char * short_options = "hi:o:";
	int opt;

	infile = NULL;

	do {
		opt = getopt(argc, argv, short_options);

		switch (opt) {
			case 'i':
				infile = optarg;
				break;

			case 'h':
				print_usage(argv, 0);
				break;

			case -1:
				break;

			default:
				print_usage(argv, 0);
				break;
		}
	} while (opt != -1);

	if ( !infile )
		print_usage(argv, -1);

	PSC_FULL_SAMPLING;
	PSC_TECHLIB_INIT;

	go(infile);
	
	PSC_TECHLIB_INFO;
	PSC_REPORT_SWITCHING_POWER;
	PSC_REPORT_POWER;

	return( 0 );
}
