#include "testbench.h"

void testbench::generate_stimuli()
{
   int next_num;
   
	switch ( state_drv ) {
		case reset_0:
			// cout << "[stimuli]: reset_0\n";
			duv_reset_n.write( sc_bit(0) );
			state_drv = reset_1;
			break;

		case reset_1:
			// cout << "[stimuli]: reset_1\n";
			duv_reset_n.write( sc_bit(1) );
			state_drv = pre_start;
			break;

		case pre_start:
			// cout << "[stimuli]: pre_start\n";
			data_available.write( sc_bit(0) );
			state_drv = start_0;
			break;

		case start_0:
			// cout << "[stimuli]: start_0\n";
			if ( duv_may_read.read() ) {
				duv_reset_n.write( sc_bit(0) );
				state_drv = start_1;
			}
			break;

		case start_1:
			// cout << "[stimuli]: start_1\n";
			duv_reset_n.write( sc_bit(1) );
			state_drv = send_0;
			i =  0;
			break;

		case send_0:
			duv_in_nch = N_CH;
			next_num = psc_util_rand_num( MAX_DATA_VAL );
			data_out = next_num;
			// cout << "[stimuli]: send_0 (num=" << next_num << "\n";
			data_available.write( sc_bit(1) );
			i++;
			state_drv = send_1;
			break;

		case send_1:
			// cout << "[stimuli]: send_1 (i=" << i << ")\n";
			data_available.write( sc_bit(0) );
			if ( i < 32 )
				state_drv = send_0;
			else
				state_drv = start_0;
			break;

		default:
			cout << "Houston, we've got a problem!" << endl;
	}
}

void testbench::stimuli_response()
{
	switch ( state_mnt ) {
		case start:
			// cout << "[response]: start\n";
			duv_may_write.write( sc_bit(1) );
			if ( duv_done.read() )
				state_mnt = read_0;
				j = 0;
			break;

		case read_0:
			// cout << "[response]: read_0\n";
			res = data_in.read();
			state_mnt = read_1;
			j++;
			break;

		case read_1:
			// cout << "[response]: read_1 (j=" << j << ")\n";
			if ( j < 32 )
				state_mnt = read_0;
			else {
				state_mnt = start;
				duv_may_write.write( sc_bit(0) );
			}
			break;
			
		default:
			cout << "Houston, we've got a problem!" << endl;
	}
}

#ifndef SYNTHESIS

#include "dct.h"

void run_experiment( int sim_time )
{
   PSC_FULL_SAMPLING;

	psc_util_srand( 42 );

	sc_clock clk("clk", sc_time(20, SC_NS), 0.5, SC_ZERO_TIME, true);

	// driver signals
	sc_signal<sc_bit> reset_n( "Reset_n" );
	sc_signal<sc_uint<32> > driver_duv( "data_in" );
	sc_signal<sc_bit> data_available( "in_trans" );
	sc_signal<sc_bit> may_read( "in_ready" );
	sc_signal<sc_uint<2> > duv_in_nch( "in_nch" );

	// monitor signals
	sc_signal<sc_bit> done( "out_trans" );
	sc_signal<sc_bit> may_write( "out_ready" );
	sc_signal<sc_uint<2> > duv_out_nch( "out_nch" );
	sc_signal<sc_uint<32> > duv_monitor( "data_out" );
	
	testbench tb( "tb" );
	tb.clk( clk );

	tb.duv_reset_n( reset_n );
	tb.data_out( driver_duv );
	tb.data_available( data_available );
	tb.duv_may_read( may_read );
	tb.duv_in_nch( duv_in_nch );

	dct dct1( "dct1" );
	dct1.clk( clk );
	dct1.Reset_n( reset_n );
	dct1.data_in( driver_duv );
	dct1.in_trans( data_available );
	dct1.in_ready( may_read );
	dct1.in_nch( duv_in_nch );

	tb.duv_done( done );
	tb.duv_out_nch( duv_out_nch );
	tb.data_in( duv_monitor );
	tb.duv_may_write( may_write );

	dct1.out_trans( done );
	dct1.out_nch( duv_out_nch );
	dct1.data_out( duv_monitor );
	dct1.out_ready( may_write );
	
	sc_start( sim_time );

}
#endif
