# Project Name
TARGET = Disperse


# Sources
CPP_SOURCES = Disperse.cpp

C_INCLUDES += -I./util/
C_INCLUDES += -I../../siderialib/include

# Library Locations
LIBDAISY_DIR = ../../external/libDaisy
DAISYSP_DIR = ../../external/DaisySP

# include sideria library in search path
SIDERIALIB_DIR = ../../siderialib
SIDERIALIB_SRC = {SIDERIALIB_DIR}/src

# Link sideria library
LIBDIR += -L../../arm-debug/siderialib
LIBS += -lsiderialib

# Core location, and generic makefile.
SYSTEM_FILES_DIR = $(LIBDAISY_DIR)/core
include $(SYSTEM_FILES_DIR)/Makefile
