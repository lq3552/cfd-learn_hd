#=======================================================================
#
# Summary: Makefile for Gudunov HD solver
#
# Author: Qi Li (pg3552@ufl.edu)
#
# Created: 2017-10-09
# Updated: 2022-10-09
#
# Configurable files:
#	Make.config.system      define syste type
#	Make.system.systemname  system-dependent settings
#	Make.config.objects     list of object files
#
# Description:
#	make [EXE=Hydro.exe] [LOG=compile.out]
#=======================================================================

ifndef SHELL
  SHELL := /bin/bash
endif

ROOT      := $(dir $(lastword $(MAKEFILE_LIST)))
ROOT      := $(ROOT:/=)
SRC_DIR   := $(ROOT)/src
BUILD_DIR := $(ROOT)/build

LOG := compile.out
EXE := Hydro.exe

# set compilers and options based on system
include Make.config.system
ifeq ($(SYSTYPE),"macintosh-monterey")
  SYSFILE = Make.system.macintosh-monterey
  include $(SYSFILE)
else
  CXX = g++
  CC = gcc
  OPTIMIZE = -g #study further
  OPTION = -Wall
endif

DUMMY := $(shell mkdir -p $(BUILD_DIR))

# set the list of objects and headers
include Make.config.objects
OBJS := $(addprefix $(BUILD_DIR)/, $(OBJS))
include Make.config.includes
INCL := $(addprefix $(SRC_DIR)/, $(INCL))


### build rules
# generate an executable
all: build

build: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(STD) $(OPTION) $(OPTIMIZE) $(OBJS) -o $(EXE)

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.cpp $(INCL)
	$(CXX) $(STD) $(OPTION) $(OPTIMIZE) -c $< -o $@

# show system information
show-sys: $(SYSFILE)
	@echo "System type: $(SYSTYPE)"

# clean up
clean:
	rm -f $(OBJS) $(EXE)
	rm -rf $(BUILD_DIR)
