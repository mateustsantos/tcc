lib_LIBRARIES = libpowersc.a

INCLUDES = $(SCLIB_INCLUDES) $(SCLIB_SRC_INCLUDES)

include_HEADERS = base/psc_sampler.h base/psc_base_integer.h base/psc_objinfo.h base/psc_objinfo_if.h base/psc_obj_rep.h base/psc_obj_rep_base.h debug_power.h powersc.h psc_bit.h psc_bv.h psc_clock.h psc_int.h psc_logic.h psc_lv.h psc_sensitive.h psc_signal.h psc_signal_bool.h psc_uint.h utils/psc_randgen.h utils/psc_tables.h utils/psc_misc.h utils/psc_interp.h base/psc_techlib.h base/psc_macromodel.h

libpowersc_a_CXXFLAGS = -Wall -Wno-deprecated -Wno-char-subscripts

dist_EXTRA_libpowersc_a_SOURCES = base/psc_objinfo.cpp psc_bv.cpp psc_int.cpp psc_lv.cpp psc_uint.cpp  
libpowersc_a_SOURCES = powersc.cpp base/psc_sampler.cpp base/psc_obj_rep.cpp psc_bit.cpp psc_signal_bool.cpp psc_clock.cpp psc_logic.cpp utils/psc_randgen.cpp utils/psc_tables.cpp utils/psc_misc.cpp utils/psc_interp.cpp base/psc_techlib.cpp base/psc_macromodel.cpp

nodist_libpowersc_a_SOURCES = $(SC_DT_BIT_DIR)/sc_bit.cpp $(SC_DT_BIT_DIR)/sc_logic.cpp $(SC_COMM_DIR)/sc_clock.cpp $(SC_KERNEL_DIR)/sc_wait.cpp  $(SC_KERNEL_DIR)/sc_join.cpp
