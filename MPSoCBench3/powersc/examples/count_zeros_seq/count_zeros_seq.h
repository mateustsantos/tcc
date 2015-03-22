#ifndef COUNT_ZEROS_SEQ_H
#define COUNT_ZEROS_SEQ_H

#include <systemc.h>

//#ifndef NO_PSC
//#ifndef SYNTHESIS
#include <powersc.h>
//#endif
//#endif

#define ZEROS_WIDTH 4
#define MAX_BIT_READ 7

SC_MODULE(count_zeros_seq) 
{
	// input ports
	sc_in<bool> clk;
	sc_in<sc_bit> data;
	sc_in<sc_bit> reset;
	sc_in<sc_bit> read;

	// output ports
	sc_out<sc_bit> is_legal;
	sc_out<sc_bit> data_ready;
	sc_out<sc_uint<ZEROS_WIDTH> > zeros;
  
	// signals
	sc_signal<sc_bit> new_data_ready;
	sc_signal<sc_bit> new_is_legal;
	sc_signal<sc_bit> new_seenZero;
	sc_signal<sc_bit> new_seenTrailing;
	sc_signal<sc_bit> seenZero, seenTrailing;
	sc_signal<sc_bit> is_legal_s;
	sc_signal<sc_bit> data_ready_s;

	sc_signal<sc_uint<ZEROS_WIDTH> > new_zeros;
	sc_signal<sc_uint<ZEROS_WIDTH> > zeros_s;
	
	sc_signal<sc_uint<ZEROS_WIDTH - 1> > bits_seen;
	sc_signal<sc_uint<ZEROS_WIDTH - 1> > new_bits_seen;
  
	// Processes
	void comb_logic();
	void seq_logic();
	void assign_outputs();
  
	// Helper functions
	void set_defaults();
  
	SC_CTOR(count_zeros_seq) 
	{
		SC_METHOD(comb_logic);
		sensitive << data << read << is_legal_s << data_ready_s;
		sensitive << seenTrailing << seenZero << zeros_s << bits_seen;
    
		SC_METHOD(seq_logic);
		sensitive_pos << clk; // << reset;
		
		SC_METHOD(assign_outputs);
		sensitive << is_legal_s << data_ready_s << zeros_s;   

      PSC_OBJ_ALIAS(new_data_ready, "new_data_ready");
      PSC_OBJ_ALIAS(new_is_legal, "new_is_legal");
      PSC_OBJ_ALIAS(new_seenZero, "new_seenZero");
      PSC_OBJ_ALIAS(new_seenTrailing, "new_seenTrailing");
      PSC_OBJ_ALIAS(seenZero, "seenZero");
      PSC_OBJ_ALIAS(seenTrailing, "seenTrailing");
      PSC_OBJ_ALIAS(is_legal_s, "is_legal_s");
      PSC_OBJ_ALIAS(data_ready_s, "data_ready_s");
      PSC_OBJ_ALIAS(new_zeros, "new_zeros");
      PSC_OBJ_ALIAS(zeros_s, "zeros_s");
      PSC_OBJ_ALIAS(bits_seen, "bits_seen");
      PSC_OBJ_ALIAS(new_bits_seen, "new_bits_seen");
  }
};

#endif
