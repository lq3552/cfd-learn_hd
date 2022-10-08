#=======================================================================
#
# SUMMARY: Makefile for Gudunov HD solver
#
# AUTHOR: Qi Li (pg3552@ufl.edu)
#
# DATE: 2017-10-09
#
# CONFIGURABLE FILE:
#	Make.config.system      define syste type
#	Make.system.systemname  system-dependent settings
#	Make.config.objects     list of object files
#
# DESCRIPTION:
#	make [EXE=Hydro.exe] [LOG=compile.out]
#=======================================================================

ifndef SHELL
  SHELL = /bin/bash
endif


include Make.config.objects

LOG = compile.out
EXE = Hydro.exe

CXX = g++ Wc++17-extensions
CC = gcc
OPTIMIZE = -Wall -g #study further
OPTION = -Wall -c

include Make.config.system
ifeq ($(SYSTYPE),"macintosh-sierra")
  SYSFILE = Make.system.macintosh-sierra
  include $(SYSFILE)
endif

# Generate an executable
$(EXE): $(OBJECTS)
	$(CXX) $(OPTIMIZE) $(OBJECTS) -o $(EXE)


# show system
show-sys: $(SYSFILE)
	@echo "System type: $(SYSTYPE)"


# Implicit rules
%.o : %.C
	$(CXX) $(OPTION) $< -o $@


# Clean
clean:
	rm -f $(OBJECTS) $(EXE)
