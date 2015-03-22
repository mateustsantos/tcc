#include "add32.h"

#undef	Add32

Add32::~Add32()
{
	delete( I106 );
	delete( I107 );
	delete( I1 );
	delete( I2 );
	delete( I3 );
	delete( I108 );
	delete( I109 );
	delete( I110 );
	delete( I111 );
	delete( I112 );
	delete( I113 );
	delete( I114 );
	delete( I115 );
	delete( I116 );
	delete( I7 );
	delete( I117 );
	delete( I118 );
	delete( I119 );
	delete( I120 );
	delete( I121 );
	delete( I122 );
	delete( I123 );
	delete( I124 );
	delete( I125 );
	delete( I126 );
	delete( I127 );
	delete( I128 );
	delete( I129 );
	delete( I130 );
	delete( I131 );
	delete( I132 );
	delete( I133 );
	delete( I134 );
	delete( I135 );
	delete( I136 );
	delete( I137 );
	delete( I15 );
	delete( I138 );
	delete( I139 );
	delete( I140 );
	delete( I141 );
	delete( I142 );
	delete( I143 );
	delete( I144 );
	delete( I145 );
	delete( I146 );
	delete( I147 );
	delete( I148 );
	delete( I149 );
	delete( I150 );
	delete( I151 );
	delete( I152 );
	delete( I153 );
	delete( I154 );
	delete( I155 );
	delete( I156 );
	delete( I157 );
	delete( I158 );
	delete( I159 );
	delete( I160 );
	delete( I161 );
	delete( I24 );
	delete( I162 );
	delete( I163 );
	delete( I164 );
	delete( I165 );
	delete( I166 );
	delete( I167 );
	delete( I168 );
	delete( I169 );
	delete( I170 );
	delete( I171 );
	delete( I172 );
	delete( I173 );
	delete( I174 );
	delete( I175 );
	delete( I176 );
	delete( I177 );
	delete( I178 );
	delete( I179 );
	delete( I180 );
	delete( I182 );
#ifdef POWER_SIM
#endif
}

#define	Add32	Add32_wrapper

void Add32_wrapper::exec_i()
{
	int i;

	sc_uint<32> tmp_a = a.read();
	PSC_IGNORE( tmp_a );
	for ( i = 0 ; i < 32 ; i++ )
		sig_a[ i ].write( sc_uint<1>(tmp_a.bit(i)) );

	sc_uint<32> tmp_b = b.read();
	PSC_IGNORE( tmp_b );
	for ( i = 0 ; i < 32 ; i++ )
		sig_b[ i ].write( sc_uint<1>(tmp_b.bit(i)) );
}

void Add32_wrapper::exec_o()
{
	int i;

	sc_uint<32> tmp_out1;
	PSC_IGNORE( tmp_out1 );
	for ( i = 0 ; i < 32 ; i++ )
		tmp_out1[ i ] = sig_out1[ i ].read();
	out1.write( tmp_out1 );
}
