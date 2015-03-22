#ifndef DRINK_MACHINE_H
#define DRINK_MACHINE_H

#include <systemc.h>

#ifndef NO_PSC
#include <powersc.h>
#endif

/*
 *   This enumerated type contains all valid states for the state machine.
 */

enum dm_states {
    IDLE=0, FIVE=1, TEN=2, FIFTEEN=3, TWENTY=4, TWENTY_FIVE=5, THIRTY=6, OWE_DIME=7
};

/*
 *   This module contains a state machine that counts money for a vending
 *   machine.  The machine waits for 35 cents to be deposited and then
 *   signals the vending machine to vend a drink.  If change is owed, that
 *   is dispensed as well.
 */
SC_MODULE(drink_machine) {

   // input ports
   sc_in<bool>  clk;
   sc_in<sc_bit>  reset;
   sc_in<sc_bit>  nickel_in;
   sc_in<sc_bit>  dime_in;
   sc_in<sc_bit>  quarter_in;

   // output ports
   sc_out<sc_bit> collect;
   sc_out<sc_bit> nickel_out;
   sc_out<sc_bit> dime_out;
   sc_out<sc_bit> dispense;
  
  /*
   *   Signals:  Used for process-to-process conmmunication
   */
   sc_signal<sc_uint<3> >  state;
   sc_signal<sc_uint<3> >  next_state;
  
  /*
   *   Processes:  process definition is the the constructor
   */
   void vend_comb();
   void vend_seq();
   
#ifdef SIM
   void trace(sc_trace_file *tf);
#endif
  
  /*
   *   Methods
   */
   void set_defaults();
   void vend_a_drink();
  
  
  /*
   *   Constructor:  Constains process definitions
   *   SC_METHOD process are used for RTL synthesis
   */
   SC_CTOR(drink_machine) { 
      SC_METHOD(vend_comb);
      sensitive << nickel_in << dime_in << quarter_in /*<< state*/;
     
      SC_METHOD(vend_seq);
      sensitive_pos << clk; // the original had "<< reset" also

#ifdef POWER_SIM
      state.set_alias("state");
      next_state.set_alias("next_state");
#endif
   }
};

#endif
