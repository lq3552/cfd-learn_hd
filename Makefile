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

CXX = g++
CC = gcc
OPT = -Wall -g # debug, need to study further

include Make.config.system
ifeq ($(SYSTYPE),"macintosh-sierra")
  include Make.system.macintosh-sierra
endif

$(EXE): $(OBJECTS)
	$(CXX) $(OPT) $(OBJECTS) -o $(EXE)


clean:
	rm -f $(OBJECTS) $(EXE)
