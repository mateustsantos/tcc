#include "drink_machine.h"

/*
 *   Process: vend_seq()        Type: SC_METHOD
 *   This process registers the next_state to the current state
 */
void drink_machine::vend_seq() 
{
   if (reset.read()) {
      state.write( IDLE );
   } else { 
      state = next_state;
   }  
}

/*
 *   Process: vend_comb()       Type: SC_METHOD
 *   This combinational process calculates the value of the
 *   next state and the outputs, based on the current state.
 *
 *   The swith statement is fully specified because all the 
 *   values in the enumerated type state are defined.
 */
void drink_machine::vend_comb() 
{
   set_defaults();
   
   switch ( state.read() ) {
      case IDLE:
         if (quarter_in.read() == 1) {
            next_state.write( TWENTY_FIVE );
         } else if (dime_in.read() == 1) {
            next_state.write( TEN );
         } else if (nickel_in.read() == 1) {
            next_state.write( FIVE );
         }
         break;

      case FIVE:
         next_state.write( FIVE );
         if (nickel_in.read())
            next_state.write( TEN );
         else if (dime_in.read())
            next_state.write( FIFTEEN );
         else if (quarter_in.read())
            next_state.write( THIRTY );
         break;
      
      case TEN:
         next_state.write( TEN );
         if (nickel_in.read()) {
            next_state.write( FIFTEEN );
         } else if (dime_in.read()) {
            next_state.write( TWENTY );
         } else if (quarter_in.read()) {
            vend_a_drink();
            next_state.write( IDLE );
         }
         break;
         
      case FIFTEEN:
         next_state.write( FIFTEEN );
         if (nickel_in.read()) {
            next_state.write( TWENTY );
         } else if (dime_in.read()) {
            next_state.write( TWENTY_FIVE );
         } else if (quarter_in.read()) {
            vend_a_drink();
            nickel_out.write( sc_bit(1) );
            next_state.write( IDLE );
         }
         break;
         
      case TWENTY:
         next_state.write( TWENTY );
         if (nickel_in.read()) {
            next_state.write( TWENTY_FIVE );
         } else if (dime_in.read()) {
            next_state.write( THIRTY );
         } else if (quarter_in.read()) {
            vend_a_drink();
            dime_out.write( sc_bit(1) );
            next_state.write( IDLE );
         }
         break;
         
      case TWENTY_FIVE:
         next_state.write( TWENTY_FIVE );
         if (nickel_in.read()) {
            next_state.write( THIRTY );
         } else if (dime_in.read()) {
            vend_a_drink();
            next_state.write( IDLE );
         } else if (quarter_in.read()) {
            vend_a_drink();
            nickel_out.write( sc_bit(1) );
            next_state.write( OWE_DIME );
         }
      break;
      
      case THIRTY:
         next_state.write( THIRTY );
         if (nickel_in.read()) {
            vend_a_drink();
            next_state.write( IDLE );
         } else if (dime_in.read()) {
            vend_a_drink();
            nickel_out.write( sc_bit(1) );
            next_state.write( IDLE );
         } else if (quarter_in.read()) {
            vend_a_drink();
            dime_out.write( sc_bit(1) );
            next_state.write( OWE_DIME );
         }
         break;

      case OWE_DIME:
         dime_out.write( sc_bit(1) );
         next_state.write( IDLE );
      break;
   }
}

/*
 *   Method: set_defaults()
 *   Sets the reset values for the outputs.
 */
void drink_machine::set_defaults() {
  nickel_out.write( sc_bit(0) );
  dime_out.write( sc_bit(0) );
  dispense.write( sc_bit(0) );
  collect.write( sc_bit(0) );
}

/*
 *   Method: vend_a_drink()
 *   Sets the correct outputs to signal the vending machine to 
 *   dispense a drink.
 */
void drink_machine::vend_a_drink() {
  dispense.write( sc_bit(1) );
  collect.write( sc_bit(1) );
}

/*
 *   Method: trace()
 *   This non-synthesizable code allows the sc_main() to trace
 *   values local to this SC_MODULE
 *
 *   This code is only available if the -DSIMULATION flags is
 *   set for the C++ compiler
 */
#ifdef SIM
  void drink_machine::trace(sc_trace_file *tf) {
    sc_trace(tf, state, "DMS-state");
    sc_trace(tf, next_state, "DMS-next_state");
    sc_trace(tf, nickel_in, "DMS-nickel_in");
    sc_trace(tf, dime_in.read(), "DMS-dime_in");
    sc_trace(tf, quarter_in.read(), "DMS-quarter_in");       
  }
#endif
