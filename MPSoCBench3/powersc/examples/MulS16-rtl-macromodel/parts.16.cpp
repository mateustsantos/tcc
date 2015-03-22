#include "parts.16.h"
#ifdef POWER_SIM
#include "rtl_macromodel-MulS16.cpp"
#endif

	const	double mux_16_2_area	= 3233.26;
	const	double mux_16_4_area	= 6156.261;
	const	double mux_16_8_area	= 15692.75;
	const	double mux_16_16_area	= 30977.23;
	const	double mux_16_32_area	= 65285.9;
	const	double mux_16_64_area	= 130162.9;
	const	double mux_16_128_area	= 263705.2;

	const	double mux_16_2_delay	= 452.2603;
	const	double mux_16_4_delay	= 489.3902;
	const	double mux_16_8_delay	= 1165.662;
	const	double mux_16_16_delay	= 1298.558;
	const	double mux_16_32_delay	= 1468.387;
	const	double mux_16_64_delay	= 1591.497;
	const	double mux_16_128_delay	= 1751.935;

#if 16 < 64
// AxA=2A Signed Multiplier
	// SC_MODULE( MulS16 )
	// CLOCK_PORT
	// IN_PORTS a b
	// PIPELINE_REGISTER_TYPES sc_int<16> sc_int<16>

	// signed multiply up to AxA=2A bits
#ifdef CYNTHHL
     sc_int<BW_TIMES_2> MulS16::SMul ( sc_int<16> a, sc_int<16> b) {
       sc_int<BW_TIMES_2> out1;
       out1 = a * b;
       return(out1);
     };
	// unsigned multiply up to AxA=A bits
     sc_uint<16> MulS16::UMul( sc_uint<16> a, sc_uint<16> b) {
       sc_uint<16> out1;
       out1 = a * b;
       return(out1);
     };
#endif

	void MulS16::thread_combo () { out1 = a.read() * b.read(); };

	MulS16::MulS16(const sc_module_name name ): sc_module(name) {
		SC_METHOD (thread_combo);
		sensitive << (a);
		sensitive << (b);
	};
const   unsigned long           MulS16::stallable =0;
const    double                    MulS16::area = 115189.6;
const    double                    MulS16::delay = 5961.241;
const    double                    MulS16::clock_period = 10000;
const    unsigned long            MulS16::pipelined = 0;
const    unsigned long            MulS16::latency_a = 0;
const    unsigned long            MulS16::latency_b = 0;
const 	unsigned long		MulS16::implemented =1;

#endif
