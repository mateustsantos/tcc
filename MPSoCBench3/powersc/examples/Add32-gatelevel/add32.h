#ifndef __Add32_h__
#define __Add32_h__

#include <systemc.h>
#include <powersc.h>

#include "techlibrary.h"

SC_MODULE(Add32)
{
	// ports
	sc_in<bool> a[32];
	sc_in<bool> b[32];
	sc_out<bool> out1[32];

	// components
	xor2_1 *I106;
	and2_2 *I107;
	fulladder *I1;
	fulladder *I2;
	fulladder *I3;
	xor2_1 *I108;
	mux2_2 *I109;
	xor2_1 *I110;
	xor2_1 *I111;
	mux2_2 *I112;
	xor2_1 *I113;
	xor2_1 *I114;
	mux2_2 *I115;
	xor2_1 *I116;
	fulladder *I7;
	xor2_1 *I117;
	mux2_2 *I118;
	xor2_1 *I119;
	xor2_1 *I120;
	mux2_2 *I121;
	xor2_1 *I122;
	xor2_1 *I123;
	mux2_2 *I124;
	xor2_1 *I125;
	xor2_1 *I126;
	mux2_2 *I127;
	xor2_1 *I128;
	xor2_1 *I129;
	mux2_2 *I130;
	xor2_1 *I131;
	xor2_1 *I132;
	mux2_2 *I133;
	xor2_1 *I134;
	xor2_1 *I135;
	mux2_2 *I136;
	xor2_1 *I137;
	fulladder *I15;
	xor2_1 *I138;
	mux2_2 *I139;
	xor2_1 *I140;
	xor2_1 *I141;
	mux2_2 *I142;
	xor2_1 *I143;
	xor2_1 *I144;
	mux2_2 *I145;
	xor2_1 *I146;
	xor2_1 *I147;
	mux2_2 *I148;
	xor2_1 *I149;
	xor2_1 *I150;
	mux2_2 *I151;
	xor2_1 *I152;
	xor2_1 *I153;
	mux2_2 *I154;
	xor2_1 *I155;
	xor2_1 *I156;
	mux2_2 *I157;
	xor2_1 *I158;
	xor2_1 *I159;
	mux2_2 *I160;
	xor2_1 *I161;
	fulladder *I24;
	xor2_1 *I162;
	mux2_2 *I163;
	xor2_1 *I164;
	xor2_1 *I165;
	mux2_2 *I166;
	xor2_1 *I167;
	xor2_1 *I168;
	mux2_2 *I169;
	xor2_1 *I170;
	xor2_1 *I171;
	mux2_2 *I172;
	xor2_1 *I173;
	xor2_1 *I174;
	mux2_2 *I175;
	xor2_1 *I176;
	xor2_1 *I177;
	mux2_1 *I178;
	xor2_1 *I179;
	xor2_1 *I180;
	xor2_1 *I182;

	// signals
	psc_signal_bool N305;
	psc_signal_bool N309;
	psc_signal_bool N311;
	psc_signal_bool N313;
	psc_signal_bool N443;
	psc_signal_bool N315;
	psc_signal_bool N452;
	psc_signal_bool N317;
	psc_signal_bool N461;
	psc_signal_bool N319;
	psc_signal_bool N321;
	psc_signal_bool N470;
	psc_signal_bool N323;
	psc_signal_bool N479;
	psc_signal_bool N325;
	psc_signal_bool N488;
	psc_signal_bool N327;
	psc_signal_bool N497;
	psc_signal_bool N329;
	psc_signal_bool N506;
	psc_signal_bool N331;
	psc_signal_bool N515;
	psc_signal_bool N333;
	psc_signal_bool N524;
	psc_signal_bool N335;
	psc_signal_bool N337;
	psc_signal_bool N533;
	psc_signal_bool N339;
	psc_signal_bool N542;
	psc_signal_bool N341;
	psc_signal_bool N551;
	psc_signal_bool N343;
	psc_signal_bool N560;
	psc_signal_bool N345;
	psc_signal_bool N569;
	psc_signal_bool N347;
	psc_signal_bool N578;
	psc_signal_bool N349;
	psc_signal_bool N587;
	psc_signal_bool N351;
	psc_signal_bool N596;
	psc_signal_bool N353;
	psc_signal_bool N355;
	psc_signal_bool N605;
	psc_signal_bool N357;
	psc_signal_bool N614;
	psc_signal_bool N359;
	psc_signal_bool N623;
	psc_signal_bool N361;
	psc_signal_bool N632;
	psc_signal_bool N363;
	psc_signal_bool N641;
	psc_signal_bool N365;
	psc_signal_bool N650;
	psc_signal_bool N367;
	psc_signal_bool N659;


	~Add32();

	SC_CTOR(Add32)
	{
		I106 = new xor2_1( "I106" );
		I106->op( out1[0] );
		I106->ip1( a[0] );
		I106->ip2( b[0] );

		I107 = new and2_2( "I107" );
		I107->op( N305 );
		I107->ip1( b[0] );
		I107->ip2( a[0] );

		I1 = new fulladder( "I1" );
		I1->co( N309 );
		I1->s( out1[1] );
		I1->a( b[1] );
		I1->b( N305 );
		I1->ci( a[1] );

		I2 = new fulladder( "I2" );
		I2->co( N311 );
		I2->s( out1[2] );
		I2->a( b[2] );
		I2->b( N309 );
		I2->ci( a[2] );

		I3 = new fulladder( "I3" );
		I3->co( N313 );
		I3->s( out1[3] );
		I3->a( b[3] );
		I3->b( N311 );
		I3->ci( a[3] );

		I108 = new xor2_1( "I108" );
		I108->op( N443 );
		I108->ip1( a[4] );
		I108->ip2( b[4] );

		I109 = new mux2_2( "I109" );
		I109->op( N315 );
		I109->ip1( a[4] );
		I109->ip2( N313 );
		I109->s( N443 );

		I110 = new xor2_1( "I110" );
		I110->op( out1[4] );
		I110->ip1( N443 );
		I110->ip2( N313 );

		I111 = new xor2_1( "I111" );
		I111->op( N452 );
		I111->ip1( a[5] );
		I111->ip2( b[5] );

		I112 = new mux2_2( "I112" );
		I112->op( N317 );
		I112->ip1( a[5] );
		I112->ip2( N315 );
		I112->s( N452 );

		I113 = new xor2_1( "I113" );
		I113->op( out1[5] );
		I113->ip1( N452 );
		I113->ip2( N315 );

		I114 = new xor2_1( "I114" );
		I114->op( N461 );
		I114->ip1( a[6] );
		I114->ip2( b[6] );

		I115 = new mux2_2( "I115" );
		I115->op( N319 );
		I115->ip1( a[6] );
		I115->ip2( N317 );
		I115->s( N461 );

		I116 = new xor2_1( "I116" );
		I116->op( out1[6] );
		I116->ip1( N461 );
		I116->ip2( N317 );

		I7 = new fulladder( "I7" );
		I7->co( N321 );
		I7->s( out1[7] );
		I7->a( b[7] );
		I7->b( N319 );
		I7->ci( a[7] );

		I117 = new xor2_1( "I117" );
		I117->op( N470 );
		I117->ip1( a[8] );
		I117->ip2( b[8] );

		I118 = new mux2_2( "I118" );
		I118->op( N323 );
		I118->ip1( a[8] );
		I118->ip2( N321 );
		I118->s( N470 );

		I119 = new xor2_1( "I119" );
		I119->op( out1[8] );
		I119->ip1( N470 );
		I119->ip2( N321 );

		I120 = new xor2_1( "I120" );
		I120->op( N479 );
		I120->ip1( a[9] );
		I120->ip2( b[9] );

		I121 = new mux2_2( "I121" );
		I121->op( N325 );
		I121->ip1( a[9] );
		I121->ip2( N323 );
		I121->s( N479 );

		I122 = new xor2_1( "I122" );
		I122->op( out1[9] );
		I122->ip1( N479 );
		I122->ip2( N323 );

		I123 = new xor2_1( "I123" );
		I123->op( N488 );
		I123->ip1( a[10] );
		I123->ip2( b[10] );

		I124 = new mux2_2( "I124" );
		I124->op( N327 );
		I124->ip1( a[10] );
		I124->ip2( N325 );
		I124->s( N488 );

		I125 = new xor2_1( "I125" );
		I125->op( out1[10] );
		I125->ip1( N488 );
		I125->ip2( N325 );

		I126 = new xor2_1( "I126" );
		I126->op( N497 );
		I126->ip1( a[11] );
		I126->ip2( b[11] );

		I127 = new mux2_2( "I127" );
		I127->op( N329 );
		I127->ip1( a[11] );
		I127->ip2( N327 );
		I127->s( N497 );

		I128 = new xor2_1( "I128" );
		I128->op( out1[11] );
		I128->ip1( N497 );
		I128->ip2( N327 );

		I129 = new xor2_1( "I129" );
		I129->op( N506 );
		I129->ip1( a[12] );
		I129->ip2( b[12] );

		I130 = new mux2_2( "I130" );
		I130->op( N331 );
		I130->ip1( a[12] );
		I130->ip2( N329 );
		I130->s( N506 );

		I131 = new xor2_1( "I131" );
		I131->op( out1[12] );
		I131->ip1( N506 );
		I131->ip2( N329 );

		I132 = new xor2_1( "I132" );
		I132->op( N515 );
		I132->ip1( a[13] );
		I132->ip2( b[13] );

		I133 = new mux2_2( "I133" );
		I133->op( N333 );
		I133->ip1( a[13] );
		I133->ip2( N331 );
		I133->s( N515 );

		I134 = new xor2_1( "I134" );
		I134->op( out1[13] );
		I134->ip1( N515 );
		I134->ip2( N331 );

		I135 = new xor2_1( "I135" );
		I135->op( N524 );
		I135->ip1( a[14] );
		I135->ip2( b[14] );

		I136 = new mux2_2( "I136" );
		I136->op( N335 );
		I136->ip1( a[14] );
		I136->ip2( N333 );
		I136->s( N524 );

		I137 = new xor2_1( "I137" );
		I137->op( out1[14] );
		I137->ip1( N524 );
		I137->ip2( N333 );

		I15 = new fulladder( "I15" );
		I15->co( N337 );
		I15->s( out1[15] );
		I15->a( b[15] );
		I15->b( N335 );
		I15->ci( a[15] );

		I138 = new xor2_1( "I138" );
		I138->op( N533 );
		I138->ip1( a[16] );
		I138->ip2( b[16] );

		I139 = new mux2_2( "I139" );
		I139->op( N339 );
		I139->ip1( a[16] );
		I139->ip2( N337 );
		I139->s( N533 );

		I140 = new xor2_1( "I140" );
		I140->op( out1[16] );
		I140->ip1( N533 );
		I140->ip2( N337 );

		I141 = new xor2_1( "I141" );
		I141->op( N542 );
		I141->ip1( a[17] );
		I141->ip2( b[17] );

		I142 = new mux2_2( "I142" );
		I142->op( N341 );
		I142->ip1( a[17] );
		I142->ip2( N339 );
		I142->s( N542 );

		I143 = new xor2_1( "I143" );
		I143->op( out1[17] );
		I143->ip1( N542 );
		I143->ip2( N339 );

		I144 = new xor2_1( "I144" );
		I144->op( N551 );
		I144->ip1( a[18] );
		I144->ip2( b[18] );

		I145 = new mux2_2( "I145" );
		I145->op( N343 );
		I145->ip1( a[18] );
		I145->ip2( N341 );
		I145->s( N551 );

		I146 = new xor2_1( "I146" );
		I146->op( out1[18] );
		I146->ip1( N551 );
		I146->ip2( N341 );

		I147 = new xor2_1( "I147" );
		I147->op( N560 );
		I147->ip1( a[19] );
		I147->ip2( b[19] );

		I148 = new mux2_2( "I148" );
		I148->op( N345 );
		I148->ip1( a[19] );
		I148->ip2( N343 );
		I148->s( N560 );

		I149 = new xor2_1( "I149" );
		I149->op( out1[19] );
		I149->ip1( N560 );
		I149->ip2( N343 );

		I150 = new xor2_1( "I150" );
		I150->op( N569 );
		I150->ip1( a[20] );
		I150->ip2( b[20] );

		I151 = new mux2_2( "I151" );
		I151->op( N347 );
		I151->ip1( a[20] );
		I151->ip2( N345 );
		I151->s( N569 );

		I152 = new xor2_1( "I152" );
		I152->op( out1[20] );
		I152->ip1( N569 );
		I152->ip2( N345 );

		I153 = new xor2_1( "I153" );
		I153->op( N578 );
		I153->ip1( a[21] );
		I153->ip2( b[21] );

		I154 = new mux2_2( "I154" );
		I154->op( N349 );
		I154->ip1( a[21] );
		I154->ip2( N347 );
		I154->s( N578 );

		I155 = new xor2_1( "I155" );
		I155->op( out1[21] );
		I155->ip1( N578 );
		I155->ip2( N347 );

		I156 = new xor2_1( "I156" );
		I156->op( N587 );
		I156->ip1( a[22] );
		I156->ip2( b[22] );

		I157 = new mux2_2( "I157" );
		I157->op( N351 );
		I157->ip1( a[22] );
		I157->ip2( N349 );
		I157->s( N587 );

		I158 = new xor2_1( "I158" );
		I158->op( out1[22] );
		I158->ip1( N587 );
		I158->ip2( N349 );

		I159 = new xor2_1( "I159" );
		I159->op( N596 );
		I159->ip1( a[23] );
		I159->ip2( b[23] );

		I160 = new mux2_2( "I160" );
		I160->op( N353 );
		I160->ip1( a[23] );
		I160->ip2( N351 );
		I160->s( N596 );

		I161 = new xor2_1( "I161" );
		I161->op( out1[23] );
		I161->ip1( N596 );
		I161->ip2( N351 );

		I24 = new fulladder( "I24" );
		I24->co( N355 );
		I24->s( out1[24] );
		I24->a( b[24] );
		I24->b( N353 );
		I24->ci( a[24] );

		I162 = new xor2_1( "I162" );
		I162->op( N605 );
		I162->ip1( a[25] );
		I162->ip2( b[25] );

		I163 = new mux2_2( "I163" );
		I163->op( N357 );
		I163->ip1( a[25] );
		I163->ip2( N355 );
		I163->s( N605 );

		I164 = new xor2_1( "I164" );
		I164->op( out1[25] );
		I164->ip1( N605 );
		I164->ip2( N355 );

		I165 = new xor2_1( "I165" );
		I165->op( N614 );
		I165->ip1( a[26] );
		I165->ip2( b[26] );

		I166 = new mux2_2( "I166" );
		I166->op( N359 );
		I166->ip1( a[26] );
		I166->ip2( N357 );
		I166->s( N614 );

		I167 = new xor2_1( "I167" );
		I167->op( out1[26] );
		I167->ip1( N614 );
		I167->ip2( N357 );

		I168 = new xor2_1( "I168" );
		I168->op( N623 );
		I168->ip1( a[27] );
		I168->ip2( b[27] );

		I169 = new mux2_2( "I169" );
		I169->op( N361 );
		I169->ip1( a[27] );
		I169->ip2( N359 );
		I169->s( N623 );

		I170 = new xor2_1( "I170" );
		I170->op( out1[27] );
		I170->ip1( N623 );
		I170->ip2( N359 );

		I171 = new xor2_1( "I171" );
		I171->op( N632 );
		I171->ip1( a[28] );
		I171->ip2( b[28] );

		I172 = new mux2_2( "I172" );
		I172->op( N363 );
		I172->ip1( a[28] );
		I172->ip2( N361 );
		I172->s( N632 );

		I173 = new xor2_1( "I173" );
		I173->op( out1[28] );
		I173->ip1( N632 );
		I173->ip2( N361 );

		I174 = new xor2_1( "I174" );
		I174->op( N641 );
		I174->ip1( a[29] );
		I174->ip2( b[29] );

		I175 = new mux2_2( "I175" );
		I175->op( N365 );
		I175->ip1( a[29] );
		I175->ip2( N363 );
		I175->s( N641 );

		I176 = new xor2_1( "I176" );
		I176->op( out1[29] );
		I176->ip1( N641 );
		I176->ip2( N363 );

		I177 = new xor2_1( "I177" );
		I177->op( N650 );
		I177->ip1( a[30] );
		I177->ip2( b[30] );

		I178 = new mux2_1( "I178" );
		I178->op( N367 );
		I178->ip1( a[30] );
		I178->ip2( N365 );
		I178->s( N650 );

		I179 = new xor2_1( "I179" );
		I179->op( out1[30] );
		I179->ip1( N650 );
		I179->ip2( N365 );

		I180 = new xor2_1( "I180" );
		I180->op( N659 );
		I180->ip1( a[31] );
		I180->ip2( b[31] );

		I182 = new xor2_1( "I182" );
		I182->op( out1[31] );
		I182->ip1( N659 );
		I182->ip2( N367 );



		PSC_OBJ_ALIAS(N305, "N305");
		PSC_OBJ_ALIAS(N309, "N309");
		PSC_OBJ_ALIAS(N311, "N311");
		PSC_OBJ_ALIAS(N313, "N313");
		PSC_OBJ_ALIAS(N443, "N443");
		PSC_OBJ_ALIAS(N315, "N315");
		PSC_OBJ_ALIAS(N452, "N452");
		PSC_OBJ_ALIAS(N317, "N317");
		PSC_OBJ_ALIAS(N461, "N461");
		PSC_OBJ_ALIAS(N319, "N319");
		PSC_OBJ_ALIAS(N321, "N321");
		PSC_OBJ_ALIAS(N470, "N470");
		PSC_OBJ_ALIAS(N323, "N323");
		PSC_OBJ_ALIAS(N479, "N479");
		PSC_OBJ_ALIAS(N325, "N325");
		PSC_OBJ_ALIAS(N488, "N488");
		PSC_OBJ_ALIAS(N327, "N327");
		PSC_OBJ_ALIAS(N497, "N497");
		PSC_OBJ_ALIAS(N329, "N329");
		PSC_OBJ_ALIAS(N506, "N506");
		PSC_OBJ_ALIAS(N331, "N331");
		PSC_OBJ_ALIAS(N515, "N515");
		PSC_OBJ_ALIAS(N333, "N333");
		PSC_OBJ_ALIAS(N524, "N524");
		PSC_OBJ_ALIAS(N335, "N335");
		PSC_OBJ_ALIAS(N337, "N337");
		PSC_OBJ_ALIAS(N533, "N533");
		PSC_OBJ_ALIAS(N339, "N339");
		PSC_OBJ_ALIAS(N542, "N542");
		PSC_OBJ_ALIAS(N341, "N341");
		PSC_OBJ_ALIAS(N551, "N551");
		PSC_OBJ_ALIAS(N343, "N343");
		PSC_OBJ_ALIAS(N560, "N560");
		PSC_OBJ_ALIAS(N345, "N345");
		PSC_OBJ_ALIAS(N569, "N569");
		PSC_OBJ_ALIAS(N347, "N347");
		PSC_OBJ_ALIAS(N578, "N578");
		PSC_OBJ_ALIAS(N349, "N349");
		PSC_OBJ_ALIAS(N587, "N587");
		PSC_OBJ_ALIAS(N351, "N351");
		PSC_OBJ_ALIAS(N596, "N596");
		PSC_OBJ_ALIAS(N353, "N353");
		PSC_OBJ_ALIAS(N355, "N355");
		PSC_OBJ_ALIAS(N605, "N605");
		PSC_OBJ_ALIAS(N357, "N357");
		PSC_OBJ_ALIAS(N614, "N614");
		PSC_OBJ_ALIAS(N359, "N359");
		PSC_OBJ_ALIAS(N623, "N623");
		PSC_OBJ_ALIAS(N361, "N361");
		PSC_OBJ_ALIAS(N632, "N632");
		PSC_OBJ_ALIAS(N363, "N363");
		PSC_OBJ_ALIAS(N641, "N641");
		PSC_OBJ_ALIAS(N365, "N365");
		PSC_OBJ_ALIAS(N650, "N650");
		PSC_OBJ_ALIAS(N367, "N367");
		PSC_OBJ_ALIAS(N659, "N659");
	}
};

SC_MODULE(Add32_wrapper)
{
	// ports
	sc_in<sc_uint<32> > a;
	sc_in<sc_uint<32> > b;
	sc_out<sc_uint<32> > out1;

	// components
	Add32 *add32_0;

	// signals
	psc_signal_bool sig_a[32];
	psc_signal_bool sig_b[32];
	psc_signal_bool sig_out1[32];

	// processes
	void exec_i();
	void exec_o();

	SC_CTOR(Add32_wrapper)
	{
		int i;
		char tmp[256];

		SC_METHOD(exec_i);
		sensitive << a << b;

		SC_METHOD(exec_o);
		add32_0 = new Add32( "add32_0" );
		for ( i = 0 ; i < 32 ; i++ ) {
			sprintf(tmp, "sig_a[%d]", i);
			PSC_OBJ_ALIAS(sig_a[i], tmp);
			add32_0->a[i](sig_a[i]);
		}
		for ( i = 0 ; i < 32 ; i++ ) {
			sprintf(tmp, "sig_b[%d]", i);
			PSC_OBJ_ALIAS(sig_b[i], tmp);
			add32_0->b[i](sig_b[i]);
		}
		for ( i = 0 ; i < 32 ; i++ ) {
			sprintf(tmp, "sig_out1[%d]", i);
			PSC_OBJ_ALIAS(sig_out1[i], tmp);
			add32_0->out1[i](sig_out1[i]);
			sensitive << sig_out1[ i ];
		}
	}

	~Add32_wrapper()
	{
		delete( add32_0 );
	}
};

#define	Add32	Add32_wrapper

#endif
