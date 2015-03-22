#include "psi.h"
void psi::update(){
	// the variables declared here were moved to the module header file
/*  sc_uint<5> a=in;
  sc_uint<5> b;
  int i;*/
	
	a = in.read();
	b[ 4 ] = a[ 0 ];
  
	for ( i = 0; i < 4; i++ )
		b[ i ] = a[ i+1 ] ^ a[ 0 ];
  
	out.write( b );
}
