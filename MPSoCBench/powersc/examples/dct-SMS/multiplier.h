#ifndef MULTIPLIER_H
#define MULTIPLIER_H
#include <systemc.h>
#include <powersc.h>

/*SC_MODULE(multiplier_28_32){
  sc_in<sc_uint<32> >  a;
  sc_in<sc_uint<32> >  b;
  sc_out<sc_uint<32> > c;
    void mul(){
      sc_int<32> aa;
      sc_int<32> bb;
      aa=a.read();
      bb=b.read();
      sc_int<28+1> aux=0;
      aux[28-1]=1;
      sc_uint<32+32> temp;
      temp=aa*bb+aux;
      c=temp.range(28+31,28);
    }
 
  SC_CTOR(multiplier_28_32){
    SC_METHOD(mul);
    sensitive << a;
    sensitive << b;
  }
};

SC_MODULE(multiplier_16_18){
  sc_in<sc_uint<32> >     a;
  sc_in<sc_uint<18> > b;
  sc_out<sc_uint<32> >    c;
    void mul(){
      sc_int<32> aa;
      sc_int<18> bb;
      aa=a.read();
      bb=b.read();
      sc_int<16+1> aux=0;
      aux[16-1]=1;
      sc_uint<32+18> temp;
      temp=aa*bb+aux;
      c=temp.range(16+31,16);
    }

  SC_CTOR(multiplier_16_18){
    SC_METHOD(mul);
    sensitive << a;
    sensitive << b;
  }
};*/


// the module below was modified by klein
SC_MODULE(multiplier_28_32)
{
	sc_in<sc_uint<32> >     a;
	sc_in<sc_uint<32> > b;
	sc_out<sc_uint<32> >    c;
  
	sc_bit sign_a, sign_b;
	sc_uint<31> abs_a;
	sc_uint<31> abs_b;
	
	sc_uint<28+1> aux;
	sc_uint<32+32-2> abs_temp;
	sc_bit sign_temp;
	sc_uint<32+32-1> temp;
		
	void mul()
	{
		sign_a = bool(a.read()[31]);
		sign_b = bool(b.read()[31]);

		if(sign_a)
			abs_a = -a.read();
		else
			abs_a = a.read();
		if(sign_b)
			abs_b = -b.read();
		else
			abs_b = b.read();

		aux=0;
		aux[28-1]=1;
		abs_temp = abs_a * abs_b + aux;
		sign_temp = sign_a ^ sign_b;
		
		if(sign_temp)
			temp = -abs_temp;
		else
			temp= abs_temp;

		c = temp.range(28+31,28);
	}

	SC_CTOR(multiplier_28_32)
	{
		SC_METHOD(mul);
		sensitive << a;
		sensitive << b;

      PSC_OBJ_ALIAS( sign_a, "mul_28_32.sign_a" );
      PSC_OBJ_ALIAS( sign_b, "mul_28_32.sign_b" );
      PSC_OBJ_ALIAS( abs_a, "mul_28_32.abs_a" );
      PSC_OBJ_ALIAS( abs_b, "mul_28_32.abs_b" );
      PSC_OBJ_ALIAS( aux, "mul_28_32.aux" );
      PSC_OBJ_ALIAS( abs_temp, "mul_28_32.abs_temp" );
      PSC_OBJ_ALIAS( sign_temp, "mul_28_32.sign_temp" );
      PSC_OBJ_ALIAS( temp, "mul_28_32.temp" );
	}
};


#if 0
SC_MODULE(multiplier_16_18){
  sc_in<sc_uint<32> >     a;
  sc_in<sc_uint<18> > b;
  sc_out<sc_uint<32> >    c;
    void mul(){
      bool sign_a, sign_b;
      sign_a = a.read()[31];
      sign_b = b.read()[17];

      sc_uint<31> abs_a;
      sc_uint<17> abs_b;
      if(sign_a)
        abs_a = -a.read();
      else
        abs_a = a.read();
      if(sign_b)
        abs_b = -b.read();
      else
        abs_b = b.read();

      sc_uint<16+1> aux=0;
      aux[16-1]=1;
      sc_uint<32+18-2> abs_temp = abs_a * abs_b + aux;
      bool        sign_temp = sign_a ^ sign_b;
      sc_uint<32+18-1> temp;
      if(sign_temp)
        temp = -abs_temp;
      else
        temp= abs_temp;

      c = temp.range(16+31,16);

  //     sc_int<32> aa;
  //     sc_int<18> bb;
  //     aa=a.read();
  //     bb=b.read();
  //     sc_int<16+1> aux=0;
  //     aux[16-1]=1;
  //     sc_uint<32+18-1> temp;
  //     temp=aa*bb+aux;
  //     c=temp.range(16+31,16);
    }

  SC_CTOR(multiplier_16_18){
    SC_METHOD(mul);
    sensitive << a;
    sensitive << b;
  }
};
#endif

#endif
