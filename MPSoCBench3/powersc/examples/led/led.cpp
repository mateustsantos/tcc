#include "led.h"

void led::do_count()
{
   #ifdef SIM_TRACE
   cout << "[t=" << sc_time_stamp() << endl;
   #endif
	
   if (resetn.read() == 0) {
      data = "0000011111";
      cnt = 0;
      number = 0;
      ldig = "0000000";
   } else {
      cnt++;
      if (cnt == FREQUENCY) {
         data_p1 = data >> 1;
         data_p2 = data << (data.length() - 1);
         data = data_p1 | data_p2;
         cnt = 0;

         switch (number) {
            case 0:
               ldig = "1110111";
               break;

            case 1:
               ldig = "0100100";
               break;

            case 2:
               ldig = "1011101";
               break;

            case 3:
               ldig = "1101101";
               break;

            case 4:
               ldig = "0101110";
               break;
               
            case 5:
               ldig = "1101011";
               break;
               
            case 6:
               ldig = "1111011";
               break;
               
            case 7:
               ldig = "0100101";
               break;

            case 8:
               ldig = "1111111";
               break;

            case 9:
               ldig = "1101111";
               break;
               
            default:
               ldig = "1001001";
         }

         if (number == 9)
            number = 0;
         else
            number++;
      }
   }

   #ifdef SIM_TRACE
   cout << "===> data=" << data.to_string() << ", number=" << number << "\n]" << endl;
   #endif

   led_out.write(data);
   left_digit.write(ldig);
}

#ifndef SYNTHESIS
void run_test(int simtime)
{
	int rst_time = 1000;//int(simtime * .04);
   sc_clock clk("clk", sc_time(50, SC_NS), 0.5, SC_ZERO_TIME, true);
   led my_led("my_led");
   sc_signal<sc_logic> rst("sig_resetn");
   sc_signal<sc_bv<10> > ledout("sig_ledout");
   sc_signal<sc_bv<7> > ldig("sig_ldig");
   
   PSC_FULL_SAMPLING;

   my_led.clk(clk);
   my_led.resetn(rst);
   my_led.led_out(ledout);
   my_led.left_digit(ldig);
   
   rst.write(sc_logic(false));
   sc_start(rst_time, SC_NS);

   rst.write(sc_logic(true));
   sc_start(simtime, SC_NS);
}
#endif
