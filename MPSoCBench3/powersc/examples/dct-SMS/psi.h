#ifndef PSI_H
#define PSI_H
#include <systemc.h>
#include <powersc.h>

SC_MODULE(psi){
  sc_in<sc_uint<5> > in;
  sc_out<sc_uint<5> > out;

  sc_uint<5> a;
  sc_uint<5> b;
  sc_int<4> i;
  
  void update();
  SC_CTOR(psi){
    SC_METHOD(update);
    sensitive << in;

    PSC_OBJ_ALIAS( a, "psi_a" );
    PSC_OBJ_ALIAS( b, "psi_b" );
    PSC_OBJ_ALIAS( i, "psi_i" );
  }
};
#endif
