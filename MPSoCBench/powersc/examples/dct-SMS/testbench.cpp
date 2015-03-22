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
			next_num = get_next_input_word();
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

int testbench::get_next_input_word()
{
   int iw; // input word

   if ( buff_pos < buff_max ) {
      iw = buff[ buff_pos++ ];
   } else {
      m_input_file.read( (char*)&buff, sizeof(buff) );
      buff_pos = 0;
      buff_max = m_input_file.gcount() / 4;
      iw = buff[ buff_pos++ ];
   }
      
   if ( m_input_file.eof() ) {
      cout << "End of file has been reached. Terminating simulation" << endl;
      sc_stop();
   } else {
      if ( ++words_read >= MAX_WORDS_READ ) {
         cout << " - Current position in file: " << m_input_file.tellg()
            << " bytes. \tLast value read: " << iw << endl;
         words_read = 0;
      }
   }

   return( iw );
}

void testbench::open_file( const char *name )
{
   m_input_file.open( name, ios::binary | ios::in );

   if ( ! m_input_file.is_open() ) {
      cerr << "ERROR: input file couldn't be opened" << endl;
      exit(-1);
   } else {
      m_input_file.seekg( 0, ios::end );
      cout << "File \"" << name << "\" has been opened. "
         << "Size: " << (m_input_file.tellg() / 1024) << " KB" << endl;
      m_input_file.seekg( 0, ios::beg );
   }

   m_input_file.read( (char*)buff, sizeof(buff) );
   buff_pos = 0;
   buff_max = m_input_file.gcount() / 4;
}

#ifndef SYNTHESIS

#include "dct.h"

void run_experiment( const char * input_file_name, const char *status_quo_fname )
{
  ofstream sq_file( status_quo_fname );
  
  // record the activity into the file using an interval of 1e6 ns
  PSC_STATUS_QUO( 1e6, sq_file );

  PSC_SAMPLING_THRESHOLD(0.15); // tolerance=15%
  
#ifdef SAMPLE_RANGE_EXP
#warning Selected experiment: SAMPLE_RANGE_EXP
   PSC_SAMPLES_PRED_RANGE(S_PRED_MIN, S_PRED_MAX);
   PSC_SAMPLES_MON_RANGE(S_MON_MIN, S_MON_MAX);
#endif
   
#ifdef FIRST_SAMPLES_EXP
#warning Selected experiment: FIRST_SAMPLES_EXP
   PSC_NUM_FIRST_SAMPLES(N_FIRST_SAMPLES);
#endif
   
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
   tb.open_file( input_file_name );
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
	
	sc_start( -1 ); // run forever (until the input file end is reached)

  sq_file.close();
}
#endif
