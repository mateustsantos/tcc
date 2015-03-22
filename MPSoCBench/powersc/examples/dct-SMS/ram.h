#ifndef RAM_H
#define RAM_H

#include <systemc.h>
#include <powersc.h>
#include <assert.h>

#ifdef SIMULATION
#define SIM_SENSITIVE(size)  for(int k=0; k< size; k++) sensitive << buff[k]
#define RAM_TYPE(elem_type) sc_signal<elem_type >
#else
#define SIM_SENSITIVE(size)
#define RAM_TYPE(elem_type) elem_type
#endif

#define DEFINE_RAM(size, elem_type, index_type, ram_name) \
        SC_MODULE(ram_name){\
          sc_in<bool>            clk;\
          sc_in<index_type >     i;\
          sc_in<sc_bit>            we;\
          sc_in<elem_type >      in_data;\
          sc_out<elem_type >     out_data;\
          RAM_TYPE(elem_type)    buff[size];\
          void sync_proc();\
          void async_proc();\
          SC_CTOR(ram_name){\
            SC_METHOD(sync_proc);\
            sensitive_pos << clk;\
            SC_METHOD(async_proc);\
            sensitive << i;\
            SIM_SENSITIVE(size); \
            char tmp[32]; \
            for (int ai = 0; ai < size; ai++) { \
               sprintf(tmp, #ram_name ".buff[%d]", ai); \
               PSC_OBJ_ALIAS(buff[ai], tmp); \
            } \
          }\
	};

#ifdef SIMULATION
#define SIM_ASSERT(size) assert(i.read() < size)
#else
#define SIM_ASSERT(size)
#endif

#define IMPL_RAM(size, ram_name) \
void ram_name::sync_proc(){\
  SIM_ASSERT(size); \
  if(we.read())\
    buff[i.read()] = in_data;\
}\
void ram_name::async_proc(){\
  SIM_ASSERT(size); \
  out_data = buff[i.read()];\
}

#endif
