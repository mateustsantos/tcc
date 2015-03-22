#include "testbench.h"

void testbench::execute()
{
#ifdef SIM
   cout << "t=" << sc_time_stamp() << " {" << endl;
#endif

	set_defaults();

	if ( cycle < CYCLES2WAIT )
		cycle++;
	else {
		reset.write( sc_bit(false) );

		if ( data_ready.read() == 0 ) {
			read.write( sc_bit(true) );

			if ( bindex == 0 ) {
				num_to_sent = psc_util_rand_num( MAX_NUM ) & 0xFF;
			}

			cur_bit = ((num_to_sent >> (7-bindex)) & 0x1);
			data.write( sc_bit(cur_bit) );
			

			bindex = (bindex + 1) % 8;
		} else {
			reset.write( sc_bit(true) );
			bindex = 0;
		}
	}

#ifdef SIM
   cout << "}" << endl;
#endif
}

#ifdef SIM
void testbench::comb()
{
   cout << "t=" << sc_time_stamp() << " {" << endl;

	if ( reset.read() == false ) {
		if ( data_ready.read() )
			cout << num_to_sent << ":" << is_legal << ":" << zeros << endl;
	}

/*
	cout << "data_ready: " << data_ready.read() << endl;
	cout << "is_legal: " << is_legal.read() << endl;
	cout << "zeros: " << zeros.read() << endl;
*/

   cout << "}" << endl;
}
#endif


void testbench::set_defaults()
{
	reset.write( sc_bit(true) );
	read.write( sc_bit(false) );
}

#ifndef SYNTHESIS

#include "count_zeros_seq.h"

void elaborate_model( int sim_time )
{
	PSC_FULL_SAMPLING;

#ifdef STATUS_QUO
  ofstream file( "status_quo.txt" );
  PSC_STATUS_QUO( INTERVAL, file );
#endif
	
	psc_util_srand( 42 ); // the answer for all questions

	sc_clock clk("clk", sc_time(20, SC_NS), 0.5, SC_ZERO_TIME, true);

	sc_signal<sc_bit> sig_data_ready("data_ready");
	sc_signal<sc_bit> sig_is_legal("is_legal");
	sc_signal<sc_uint<ZEROS_WIDTH> > sig_zeros("zeros");
	sc_signal<sc_bit> sig_data("data");
	sc_signal<sc_bit> sig_read("read");
	sc_signal<sc_bit> sig_reset("reset");
	
	testbench tb1("tb1");
	count_zeros_seq czseq("czseq");

	tb1.clk( clk );
	tb1.data_ready( sig_data_ready );
	tb1.is_legal( sig_is_legal );
	tb1.zeros( sig_zeros );
	tb1.data( sig_data );
	tb1.read( sig_read );
	tb1.reset( sig_reset );

	czseq.clk( clk );
	czseq.data( sig_data );
	czseq.reset( sig_reset );
	czseq.read( sig_read );
	czseq.is_legal( sig_is_legal );
	czseq.data_ready( sig_data_ready );
	czseq.zeros( sig_zeros );

	sc_start( sim_time );

#ifdef STATUS_QUO
  file.close();
#endif
}

#endif
