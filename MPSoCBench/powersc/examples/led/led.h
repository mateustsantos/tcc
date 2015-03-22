#ifndef __LED_H_
#define __LED_H_

#include <systemc.h>
#include <powersc.h>

#ifndef SYNTHESIS
#define FREQUENCY	5
#else
#define FREQUENCY	50000000
#endif

void run_test(int simtime);

SC_MODULE(led)
{
   // ports
   sc_in_clk clk;
   sc_in<sc_logic> resetn;
   sc_out<sc_bv<10> > led_out;
   sc_out<sc_bv<7> > left_digit;

   // member variables
   sc_uint<32> cnt;
   
   sc_bv<7> ldig; // left digit
   sc_uint<4> number; // 0 upto 9
   
   sc_bv<10> data;

   sc_bv<10> data_p1, data_p2;

   // processes
   void do_count();
   
   SC_CTOR(led)
   {
      SC_METHOD(do_count);
      sensitive_pos(clk);

		PSC_OBJ_ALIAS(ldig, "ldig");
		PSC_OBJ_ALIAS(cnt, "cnt");
		PSC_OBJ_ALIAS(number, "number");
		PSC_OBJ_ALIAS(data, "data");
      PSC_OBJ_ALIAS(data_p1, "data_p1");
      PSC_OBJ_ALIAS(data_p2, "data_p2");
   }
};

#endif
