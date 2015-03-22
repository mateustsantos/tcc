#include "dct.h"
void dct::comb_signals(){
	static const sc_uint<32> costab[32]={
		0,                             0xb504f33, /*0.707106781*/
		0xec835e8, /*0.923879533*/     0xf9e08757, /*-0.382683432*/
		0xfb14be8, /*0.980785280*/     0x8e39d9d, /*0.555570233*/
		0xfce0e8f9, /*-0.195090322*/   0xf2b24cec, /*-0.831469612*/
		0xfec46d2, /*0.995184727*/     0xe1c5979, /*0.881921264*/
		0xa267993, /*0.634393284*/     0x4a5018c, /*0.290284677*/
		0xfe6e8595, /*-0.098017140*/   0xf87528b3, /*-0.471396737*/
		0xf3a1bfcb, /*-0.773010453*/   0xf0b05f56, /*-0.956940336*/
		0xffb10f2, /*0.998795456*/     0xf853f7e, /*0.970031253*/
		0xe76bd7a, /*0.903989293*/     0xcd9f024, /*0.803207531*/
		0xabeb49a, /*0.671558955*/     0x839c3cd, /*0.514102744*/
		0x563e69d, /*0.336889853*/     0x259020e, /*0.146730474*/
		0xff3704d1, /*-0.049067674*/   0xfc1cc0d2, /*-0.242980180*/
		0xf928bbff, /*-0.427555093*/   0xf6780403, /*-0.595699304*/
		0xf4251070, /*-0.740951125*/   0xf246be5e, /*-0.857728610*/
		0xf0ef6f7f, /*-0.941544065*/   0xf02c5541 /*-0.989176510*/
	};
		
	y_we.write( sc_bit(0) ); //default

	if(state.read()==read_st && in_trans.read() && i.read()==0)
		nch.write( in_nch.read() );

	out_nch = nch.read();
	a.write( ki.read() + j.read() );
	b.write( a.read()  + i.read() );
	ki = k.read() << li.read();
	kmax.write( 32 >> li.read() );
	out_trans   = sc_bit( (state.read() ==write_st) ? 1 : 0 );
	cos_index.write( j.read() + i.read() );
	data_out    = y_out;
	in_ready    = sc_bit(state.read() == read_st);
	mul_a.write( costab[cos_index.read()] );
	mul_b.write( temp.read() - y_out.read() );
  
  switch(state.read()){
  case read_st:
    y_in.write( data_in );
    y_addr.write( br_psi_i.read() );
    y_we.write( sc_bit( 1 ) );
    break;
  case p1_st:
    y_addr = br_a;
    break;
  case p2_st:
    y_we.write( sc_bit( 1 ) );
    y_addr.write( br_b );
    y_in.write( sc_uint<32>(mul_c.read()) );
    break;
  case p3_st:
    y_we.write( sc_bit( 1 ) );
    y_addr.write( br_a );
    y_in.write( temp );
    break;
  case p4_st:
    y_addr.write( ki.read()-i.read()+j.read() );
    break;
  case p5_st:
    y_we.write( sc_bit( 1 ) );
    y_addr.write( ki.read()+j.read()+i.read() );
    y_in.write( 2 * y_out.read() - temp.read() );
    break;
  case write_st:
    y_addr.write( i );
    break;
  }
}
void dct::fsm(){
  if(Reset_n==0){
    state = read_st;
    i = 0;
    j = 0;//don't care
    k = 0;//don't care
    li = 0;//don't care
  }
  else{
    switch(state.read()){
          case read_st:
            if(in_trans.read()){
              if(i.read()==31){
                state = p1_st;
                i = 16;
              }
              else{
                i = i.read()+1;
                state = read_st;
              }
            }
            li = 5;
            j = 0;
            k = 0;
            break;
       case p1_st:
       temp.write( y_out );
       state = p2_st;
       break;

       case p2_st:
       temp.write( temp.read() + y_out.read() );
       state = p3_st;
       break;

       case p3_st:
         state = p1_st;
         if(j.read() == i.read() - 1){
           j = 0;
           if(k.read() == kmax.read() - 1){
             if(i.read() == 1){
      	 i = 8;
      	 k = 1;
      	 li = 4;
      	 state = p4_st;
             }
             else{
      	 li = li.read() - 1;
      	 k = 0;
      	 i = i.read() / 2;
             }
           }
           else
             k = k.read() + 1;
         }
         else
           j = j.read()+1;
         break;
       case p4_st:
         state = p5_st;
         temp.write( y_out );
         break;
       case p5_st:
         state = p4_st;
         if(j.read()==i.read() - 1){
           j = 0;
           if(k.read()==kmax.read() - 1){
             k = 1;
             i = i.read() / 2;
             li = li.read() - 1;
             if(i.read() == 1)
      	 state = write_st;
           }
           else
             k = k.read() + 1;
         }
         else
           j = j.read() + 1;
         break;
          case write_st:
            if( out_ready.read() ) {
              i = i.read() + 1;
            if(i.read()==31)
              state = read_st;
            }
           break;
    }
  }
}

void dct::set_aliases()
{
   PSC_OBJ_ALIAS( y_addr, "dct.y_addr" );
   PSC_OBJ_ALIAS( y_in, "dct.y_in" );
   PSC_OBJ_ALIAS( y_out, "dct.y_out" );
   PSC_OBJ_ALIAS( y_we, "dct.y_we" );
   PSC_OBJ_ALIAS( i, "dct.i" );
   PSC_OBJ_ALIAS( j, "dct.j" );
   PSC_OBJ_ALIAS( k, "dct.k" );
   PSC_OBJ_ALIAS( ki, "dct.ki" );
   PSC_OBJ_ALIAS( li, "dct.li" );
   PSC_OBJ_ALIAS( kmax, "dct.kmax" );
   PSC_OBJ_ALIAS( a, "dct.a" );
   PSC_OBJ_ALIAS( b, "dct.b" );
   PSC_OBJ_ALIAS( br_a, "dct.br_a" );
   PSC_OBJ_ALIAS( br_b, "dct.br_b" );
   PSC_OBJ_ALIAS( psi_i, "dct.psi_i" );
   PSC_OBJ_ALIAS( br_psi_i, "dct.br_psi_i" );
   PSC_OBJ_ALIAS( mul_a, "dct.mul_a" );
   PSC_OBJ_ALIAS( mul_b, "dct.mul_b" );
   PSC_OBJ_ALIAS( mul_c, "dct.mul_c" );
   PSC_OBJ_ALIAS( cos_index, "dct.cos_index" );
   PSC_OBJ_ALIAS( nch, "dct.nch" );
   PSC_OBJ_ALIAS( temp, "dct.temp" );
   PSC_OBJ_ALIAS( state, "dct.state" ); // state_t replaced by sc_uint<6>
}
