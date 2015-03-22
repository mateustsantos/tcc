#include "bitrev.h"

void bitrev::update()
{
  // the variables declared here were moved to the module header file
  /*sc_uint<5> a=in;
  sc_uint<5> b;
  int i;*/
	
	a = in.read();
	for( i = 0; i < 5; i++ )
		b[ i ] = a[ 4-i ];
	
	out.write( b );
}
