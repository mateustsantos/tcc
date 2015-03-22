#ifndef _parts_16_h_
#define _parts_16_h_
#include "systemc.h"
#ifdef POWER_SIM
#include <powersc.h>
#include "rtl_macromodel-MulS16.h"
#endif

#ifdef BW_TIMES_2
#undef BW_TIMES_2
#endif

#if 16 < 32
#define BW_TIMES_2 16*2
#else
#define BW_TIMES_2 64
#endif

#ifdef DIV_CUTTOF_WIDTH
#undef DIV_CUTTOF_WIDTH
#endif
#ifdef MOD_CUTTOF_WIDTH
#undef MOD_CUTTOF_WIDTH
#endif

#define DIV_CUTOFF_WIDTH	0
#define MOD_CUTOFF_WIDTH	0

#if 16 < 64
// AxA=2A Signed Multiplier
SC_MODULE( MulS16 ) {
	sc_in<sc_int<16> > a; 
	sc_in<sc_int<16> > b; 
	sc_out<sc_int<BW_TIMES_2> > out1; 
	// CLOCK_PORT
	// IN_PORTS a b
	// PIPELINE_REGISTER_TYPES sc_int<16> sc_int<16>

#ifdef CYNTHHL
	// signed multiply up to AxA=2A bits
     sc_int<BW_TIMES_2> SMul ( sc_int<16> a, sc_int<16> b) ;
	// unsigned multiply up to AxA=A bits
     sc_uint<16> UMul( sc_uint<16> a, sc_uint<16> b) ;
#endif

	void thread_combo () ;

	static const 	unsigned long		implemented;
	static const  	unsigned long  		pipelined;
	static const 	unsigned long		stallable; 
	static const  	unsigned long 		latency_a; 
	static const 	unsigned long 		latency_b;
	static const	double				area;
	static const	double				delay;
	static const 	double				clock_period; 
	
#ifdef POWER_SIM
	PSC_MACROMODEL_MulS16;
#endif
	SC_CTOR( MulS16) ;
};



#endif
#endif
