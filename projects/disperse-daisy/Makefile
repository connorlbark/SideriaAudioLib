# Project Name
TARGET = Blink

# Sources
CPP_SOURCES = Blink.cpp 

# Library Locations
LIBDAISY_DIR = ../../external/libDaisy
DAISYSP_DIR = ../../external/DaisySP
SIDERIALIB_DIR = ../../siderialib/

LIBDIR += -L../../arm-debug/siderialib

LIBS += -lsiderialib

# Core location, and generic makefile.
SYSTEM_FILES_DIR = $(LIBDAISY_DIR)/core
include $(SYSTEM_FILES_DIR)/Makefile

