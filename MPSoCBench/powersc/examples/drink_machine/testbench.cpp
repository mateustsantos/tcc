#include "testbench.h"

void testbench::execute() 
{
#ifdef SIM
   cout << "t=" << sc_time_stamp() << " {" << endl;
#endif
      set_defaults();
   
   if ( reset.read() == false ) {
      
      if ( wait_cycle )
         wait_cycle = ! wait_cycle;
      else /*if ( nickel_out.read() == false && dime_out.read() == false )*/ {
         int cur_coin = coins[ coin_index ];

         switch ( cur_coin ) {
            case NICKEL:
               INS_NICKEL;
               nickel_in.write( sc_bit(1) );
               break;

            case DIME:
               INS_DIME;
               dime_in.write( sc_bit(1) );
               break;

            case QUARTER:
               quarter_in.write( sc_bit(1) );
               INS_QUARTER;
               break;
               
            default:
               INVALID_COIN;
               break;
         }
         
         wait_cycle = true;
         coin_index = (coin_index + 1) % NUM_COINS; // select the next coin
      }
      
   }

#ifdef SIM
   cout << "}" << endl;
#endif
}

#ifdef SIM
void testbench::check_results() 
{
   if ( dispense.read() ) {
      cout << "Got drink.\n";
      if ( dime_out.read() == false && nickel_out.read() == false )
         cout << " Change is nothing\n";
   }

   if ( nickel_out.read() ) 
      cout << "change: nickel\n";
   else if ( dime_out.read() )
      cout << "change: dime\n";
}
#endif

void testbench::set_defaults() 
{
   nickel_in.write( sc_bit(0) );
   dime_in.write( sc_bit(0) );
   quarter_in.write( sc_bit(0) );
}


#ifndef SYNTHESIS

#include "drink_machine.h"

void run_experiment( int sim_time )
{
   /*   Define the clock   */
   sc_clock clk("clk", sc_time(20, SC_NS), 0.5, SC_ZERO_TIME, true);

   PSC_FULL_SAMPLING;
   
#ifdef STATUS_QUO
  ofstream file( "status_quo.txt" );
  PSC_STATUS_QUO( INTERVAL, file );
#endif
	
   sc_signal<sc_bit> reset, nickel_in, dime_in, quarter_in;
   sc_signal<sc_bit> collect, nickel_out, dime_out, dispense;

#ifdef POWER_SIM
   reset.set_alias("reset");
   nickel_in.set_alias("nickel_in");
   dime_in.set_alias("dime_in");
   quarter_in.set_alias("quarter_in");
   collect.set_alias("collect");
   nickel_out.set_alias("nickel_out");
   dime_out.set_alias("dime_out");
   dispense.set_alias("dispense");
#endif
   
   /*   Hierarchical instantiations   */

   drink_machine dut("dms");
   dut.clk(clk);
   dut.reset(reset);
   dut.nickel_in(nickel_in);
   dut.dime_in(dime_in);
   dut.quarter_in(quarter_in);
   dut.collect(collect);
   dut.nickel_out(nickel_out);
   dut.dime_out(dime_out);
   dut.dispense(dispense);
   
   testbench tb("tb");
   tb.clk(clk);
   tb.collect(collect);
   tb.dispense(dispense);
   tb.nickel_out(nickel_out);
   tb.dime_out(dime_out);
   tb.reset(reset);
   tb.nickel_in(nickel_in);
   tb.dime_in(dime_in);
   tb.quarter_in(quarter_in);

   #ifdef SIM
   /*  Signal traces   */
   sc_trace_file *tf = sc_create_vcd_trace_file("traces");
   sc_trace(tf, clk, "clock");
   sc_trace(tf, reset, "reset");
   sc_trace(tf, nickel_in, "nickel_in");
   sc_trace(tf, dime_in, "dime_in");
   sc_trace(tf, quarter_in, "quarter_in");
   sc_trace(tf, collect, "collect");
   sc_trace(tf, nickel_out, "nickel_out");
   sc_trace(tf, dime_out, "dime_out");
   sc_trace(tf, dispense, "dispense");
	dut.trace(tf);
   #endif


   reset.write( sc_bit(1) );
   sc_start( 50 );

   reset.write( sc_bit(0) );
   sc_start( sim_time );

#ifdef STATUS_QUO
  file.close();
#endif
}

#endif
