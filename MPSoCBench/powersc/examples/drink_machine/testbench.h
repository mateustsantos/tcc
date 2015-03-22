#ifndef TESTBENCH_H
#define TESTBENCH_H

#include <systemc.h>

#ifndef NO_PSC
#include <powersc.h>
#endif

#ifndef SYNTHESIS
void run_experiment( int sim_time );

#ifdef SIM

#define INS_NICKEL cout << "Inserting nickel" << endl
#define INS_DIME cout << "Inserting dime" << endl
#define INS_QUARTER cout << "Inserting quarter" << endl
#define INVALID_COIN cout << "Error: coin value is not valid: " << cur_coin << endl

#else

#define INS_NICKEL 
#define INS_DIME 
#define INS_QUARTER 
#define INVALID_COIN 

#endif

#endif


const int NUM_COINS = 16;

enum { NICKEL = 5, DIME = 10, QUARTER = 25 };

static const int coins[NUM_COINS] = {5, 10, 25, 5, 5, 10, 10, 25, 25, 10, 10, 5, 5, 5, 25, 10};


SC_MODULE(testbench) {

   // input ports
   sc_in<bool> clk;
   sc_in<sc_bit> collect, dispense, nickel_out, dime_out;
  
   // output ports
   sc_out<sc_bit> reset;
   sc_out<sc_bit> nickel_in, dime_in, quarter_in;

   // member variables
   int coin_index;
   bool wait_cycle;

   // processes
   void execute();

#ifdef SIM
   void check_results();
#endif
  
   // methods
   void set_defaults();
  
   SC_CTOR(testbench) {
      SC_METHOD(execute);
      sensitive_pos << clk;
      
#ifdef SIM
      SC_METHOD(check_results);
      sensitive_pos << clk;
#endif

      coin_index = 0;
      wait_cycle = false;
   }
};

#endif
