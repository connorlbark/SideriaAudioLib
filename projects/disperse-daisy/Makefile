# Project Name
TARGET = Disperse


# Sources
CPP_SOURCES = Disperse.cpp

C_INCLUDES += -I./util/
C_INCLUDES += -I../../siderialib/lib

# Library Locations
LIBDAISY_DIR = ../../external/libDaisy
DAISYSP_DIR = ../../external/DaisySP


# Link sideria library
ifdef DEBUG
	LIBDIR += -L../../cmake-build-daisy-debug/siderialib
else
	LIBDIR += -L../../cmake-build-daisy-release/siderialib
endif

LIBS += -lsiderialib

# Core location, and generic makefile.
SYSTEM_FILES_DIR = $(LIBDAISY_DIR)/core
include $(SYSTEM_FILES_DIR)/Makefile
