if WANT_EXAMPLES
noinst_PROGRAMS = run_x
endif

run_x_SOURCES = bitrev.cpp\
					 bitrev.h\
					 dct.cpp\
					 dct.h\
					 dct-y.cpp\
					 dct-y.h\
					 main.cpp\
					 multiplier.h\
					 psi.cpp\
					 psi.h\
					 ram.h\
					 testbench.cpp\
					 testbench.h

run_x_LDADD = -lsystemc -lpowersc

PSCLIB_INCLUDES = -I$(top_srcdir)/src -I$(srcdir)/src/base -I$(srcdir)/src/utils

PSCLIB_LD = $(top_srcdir)/src

INCLUDES = $(SCLIB_INCLUDES) $(PSCLIB_INCLUDES)

DEFS = -DPOWER_SIM

run_x_CPPFLAGS = -Wall -Wno-deprecated -Wno-char-subscripts 

run_x_LDFLAGS = -L$(PSCLIB_LD)

all-sc:
	@echo "Building for SystemC..."
	$(MAKE) all DEFS=-DPOWER_SIM_DISABLED


