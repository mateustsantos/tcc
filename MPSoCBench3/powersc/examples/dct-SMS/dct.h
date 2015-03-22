#ifndef DCT_H
#define DCT_H

#include <systemc.h>
#include <powersc.h>

#include "bitrev.h"
#include "psi.h"
#include "multiplier.h"
#include "dct-y.h"

SC_MODULE(dct)
{
	// input ports
	sc_in<bool>          clk;
	sc_in<sc_bit>          Reset_n;
	sc_in<sc_bit>          in_trans;
	sc_in<sc_bit>          out_ready;
	sc_in<sc_uint<32> >  data_in;
	sc_in<sc_uint<2> >   in_nch;
  
	// output ports
	sc_out<sc_uint<32> > data_out;
	sc_out<sc_bit>         out_trans;
	sc_out<sc_bit>         in_ready;
	sc_out<sc_uint<2> >  out_nch;

	// enumerations and other stuff
	enum state_t {read_st=0, p1_st=1, p2_st=2, p3_st=3, p4_st=4, p5_st=5, write_st=6};
  
	// signals
	sc_signal<sc_uint<5> >  y_addr;
	sc_signal<sc_uint<32> > y_in;
	sc_signal<sc_uint<32> > y_out;
	sc_signal<sc_bit>       y_we;
	sc_signal<sc_uint<5> >  i;
	sc_signal<sc_uint<4> >  j;
	sc_signal<sc_uint<4> >  k;
	sc_signal<sc_uint<5> >  ki;
	sc_signal<sc_uint<3> >  li;
	sc_signal<sc_uint<5> >  kmax;
	sc_signal<sc_uint<5> >  a;
	sc_signal<sc_uint<5> >  b;
	sc_signal<sc_uint<5> >  br_a;
	sc_signal<sc_uint<5> >  br_b;
	sc_signal<sc_uint<5> >  psi_i;
	sc_signal<sc_uint<5> >  br_psi_i;
	sc_signal<sc_uint<32> > mul_a;
	sc_signal<sc_uint<32> > mul_b;
	sc_signal<sc_uint<32> > mul_c;
	sc_signal<sc_uint<5> >  cos_index;
	sc_signal<sc_uint<2> >  nch;
	sc_signal<sc_uint<32> > temp;
	sc_signal<sc_uint<3> > state; // state_t replaced by sc_uint<3>

	// modules instantiated here
	bitrev           *bitrev0;
	bitrev           *bitrev1;
	bitrev           *bitrev2;
	psi              *psi0;
	multiplier_28_32 *mul0;
	yram             *yram0;


	// processes
	void comb_signals();
	void fsm();

   // methods
   void set_aliases();

	SC_CTOR(dct)
	{
      bitrev0 = new bitrev("bitrev0");
      bitrev1 = new bitrev("bitrev1");
      bitrev2 = new bitrev("bitrev2");
      psi0    = new psi("psi0");
      mul0    = new multiplier_28_32("mul0");
      yram0   = new yram("yram0");

		bitrev0->in(psi_i);
		bitrev0->out(br_psi_i);

		psi0->in(i);
		psi0->out(psi_i);

		bitrev1->in(a);
		bitrev1->out(br_a);

		bitrev2->in(b);
		bitrev2->out(br_b);

		mul0->a(mul_a);
		mul0->b(mul_b);
		mul0->c(mul_c);

		yram0->clk(clk);
		yram0->i(y_addr);
		yram0->we(y_we);
		yram0->in_data(y_in);
		yram0->out_data(y_out);

		SC_METHOD(fsm);
		sensitive_pos << clk;
		SC_METHOD(comb_signals);
		sensitive << ki;
		sensitive << j;
		sensitive << i;
		sensitive << a;
		sensitive << k;
		sensitive << li;
		sensitive << br_a;
		sensitive << br_b;
		sensitive << br_psi_i;
		sensitive << state;
		sensitive << in_trans;
		sensitive << in_nch;
		sensitive << nch;
		sensitive << temp;
		sensitive << y_addr;
		sensitive << y_out;
		sensitive << mul_c;
		sensitive << y_we;
		sensitive << data_in;
      
      set_aliases();
	}

#ifndef SYNTHESIS
   ~dct()
   {
      delete( bitrev0 );
      delete( bitrev1 );
      delete( bitrev2 );
      delete( psi0 );
      delete( mul0 );
      delete( yram0 );
   }
#endif
};
#endif
