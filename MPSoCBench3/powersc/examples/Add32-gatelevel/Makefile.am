EXTRA_DIST = input/stimuli-10.txt\
				 input/stimuli-1.txt\
				 input/stimuli-2.txt\
				 input/stimuli-3.txt\
				 input/stimuli-4.txt\
				 input/stimuli-5.txt\
				 input/stimuli-6.txt\
				 input/stimuli-7.txt\
				 input/stimuli-8.txt\
				 input/stimuli-9.txt

if WANT_EXAMPLES
noinst_PROGRAMS = run_x
endif

run_x_SOURCES = add32.cpp\
					 add32.h\
					 main.cpp\
					 techlibrary.cpp\
					 techlibrary.h\
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


