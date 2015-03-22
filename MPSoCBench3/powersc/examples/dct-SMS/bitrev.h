#ifndef BITREV_H
#define BITREV_H

#include <systemc.h>
#include <powersc.h>

SC_MODULE(bitrev){
  sc_in<sc_uint<5> > in;
  sc_out<sc_uint<5> > out;
  void update();

  sc_uint<5> a;
  sc_uint<5> b;
  sc_int<4> i;

  SC_CTOR(bitrev){
    SC_METHOD(update);
    sensitive << in;

    PSC_OBJ_ALIAS( a, "bitrev_a" );
    PSC_OBJ_ALIAS( b, "bitrev_b" );
    PSC_OBJ_ALIAS( i, "bitrev_i" );
  }
};
#endif
