EXTRA_DIST = input/stimuli-10.txt\
				 input/stimuli-1.txt\
				 input/stimuli-2.txt\
				 input/stimuli-3.txt\
				 input/stimuli-4.txt\
				 input/stimuli-5.txt\
				 input/stimuli-6.txt\
				 input/stimuli-7.txt\
				 input/stimuli-8.txt\
				 input/stimuli-9.txt\
				 model_coefficients-MulS16.cpp\
				 rtl_macromodel-MulS16.cpp\
				 model_defines-MulS16.cpp\
				 points_index-MulS16.cpp

if WANT_EXAMPLES
noinst_PROGRAMS = run_x
endif

run_x_SOURCES = main.cpp\
					 parts.16.cpp\
					 parts.16.h\
					 rtl_macromodel-MulS16.h\
					 testbench.cpp\
					 testbench.h


run_x_LDADD = -lsystemc -lpowersc

CXXFLAGS = -Wall -Wno-deprecated -Wno-char-subscripts

PSCLIB_INCLUDES = -I$(top_srcdir)/src -I$(srcdir)/src/base -I$(srcdir)/src/utils

PSCLIB_LD = $(top_srcdir)/src

INCLUDES = $(SCLIB_INCLUDES) $(PSCLIB_INCLUDES)

DEFS = -DPOWER_SIM

run_x_CPPFLAGS = -Wall -Wno-deprecated -Wno-char-subscripts 

run_x_LDFLAGS = -L$(PSCLIB_LD)

all-sc:
	@echo "Building for SystemC..."
	$(MAKE) all DEFS=-DPOWER_SIM_DISABLED
