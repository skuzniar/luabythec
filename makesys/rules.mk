#-----------------------------------------------------------------------------------------------------------------------
# Enforce basic minimums.
#-----------------------------------------------------------------------------------------------------------------------
ifndef MAKESYS_PROJECT_NAME
    MAKESYS_PROJECT_NAME := $(error Invalid MAKESYS_PROJECT_NAME='$(MAKESYS_PROJECT_NAME)' - set the name of the project)
endif

MAKESYS_VALID_PROJECT_TYPES := exe dll lib
ifeq "$(findstring $(MAKESYS_PROJECT_TYPE),$(MAKESYS_VALID_PROJECT_TYPES))" ""
    MAKESYS_PROJECT_TYPE := $(error Invalid MAKESYS_PROJECT_TYPE='$(MAKESYS_PROJECT_TYPE)' - set to one of '$(MAKESYS_VALID_PROJECT_TYPES)')
endif

ifndef MAKESYS_MAKESYS_ROOT
	MAKESYS_MAKESYS_ROOT := $(dir $(lastword $(MAKEFILE_LIST)))
endif

ifndef MAKESYS_BUILD_ROOT
    MAKESYS_BUILD_ROOT := $(error Invalid MAKESYS_BUILD_ROOT='$(MAKESYS_BUILD_ROOT)' - set the root of the build tree)
endif

#-----------------------------------------------------------------------------------------------------------------------
# Detect build platform.
#-----------------------------------------------------------------------------------------------------------------------
ifndef MAKESYS_OS
	ifeq ($(OS), Windows_NT)
		MAKESYS_OS := windows

		ifndef MAKESYS_ARCH
			ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
				MAKESYS_ARCH := x64
    	endif
    	ifeq ($(PROCESSOR_ARCHITECTURE),x86)
				MAKESYS_ARCH := x86
    	endif
		endif

	else
		UNAME_S := $(shell uname -s)
		ifeq ($(UNAME_S), Linux)
			MAKESYS_OS := linux
		endif
		ifeq ($(UNAME_S), Darwin)
			MAKESYS_OS := osx
	 	endif

		ifndef MAKESYS_ARCH
    	UNAME_P := $(shell uname -m)
    	ifeq ($(UNAME_P),x86_64)
				MAKESYS_ARCH := x64
    	endif
    	ifneq ($(filter %86,$(UNAME_P)),)
				MAKESYS_ARCH := x86
    	endif
    	ifneq ($(filter arm%,$(UNAME_P)),)
				MAKESYS_ARCH := arm
			endif
		endif

	endif
endif

MAKESYS_VALID_OSS := linux osx mac
ifeq ($(findstring $(MAKESYS_OS),$(MAKESYS_VALID_OSS)),)
    MAKESYS_OS := $(error Invalid MAKESYS_OS='$(MAKESYS_OS)' - set to one of '$(MAKESYS_VALID_OSS)')
endif

MAKESYS_VALID_ARCHS := x86 x64 arm
ifeq ($(findstring $(MAKESYS_ARCH),$(MAKESYS_VALID_ARCHS)),)
    MAKESYS_ARCH := $(error Invalid MAKESYS_ARCH='$(MAKESYS_ARCH)' - set to one of '$(MAKESYS_VALID_ARCHS)')
endif

#-----------------------------------------------------------------------------------------------------------------------
# Destination directories for all build stages
#-----------------------------------------------------------------------------------------------------------------------
ifndef MAKESYS_CODEGEN_DIR
	MAKESYS_CODEGEN_DIR := $(MAKESYS_BUILD_ROOT)/codegen
endif
ifndef MAKESYS_COMPILE_DIR
	MAKESYS_COMPILE_DIR := $(MAKESYS_BUILD_ROOT)/compile
endif
ifndef MAKESYS_LIBLINK_DIR
	MAKESYS_LIBLINK_DIR := $(MAKESYS_BUILD_ROOT)/liblink
endif
ifndef MAKESYS_DLLLINK_DIR
	MAKESYS_DLLLINK_DIR := $(MAKESYS_BUILD_ROOT)/dlllink
endif
ifndef MAKESYS_EXELINK_DIR
	MAKESYS_EXELINK_DIR := $(MAKESYS_BUILD_ROOT)/exelink
endif
ifndef MAKESYS_PACKAGE_DIR
	MAKESYS_PACKAGE_DIR := $(MAKESYS_BUILD_ROOT)/package
endif
ifndef MAKESYS_INSTALL_DIR
	ifeq ($(prefix),)
		ifneq ($(wildcard $(HOME)/.local),)
			MAKESYS_INSTALL_DIR := $(HOME)/.local
		else
			MAKESYS_INSTALL_DIR := /usr/local
		endif
	else
		ifeq ($(wildcard $(prefix)),)
			MAKESYS_INSTALL_DIR := $(error Invalid prefix='$(prefix)' - set it to the root of the installation)
		else
			MAKESYS_INSTALL_DIR := $(prefix)
		endif
	endif
endif

#-----------------------------------------------------------------------------------------------------------------------
# Set default build rule for the projet type
#-----------------------------------------------------------------------------------------------------------------------
ifeq ($(MAKESYS_PROJECT_TYPE), exe)
	MAKESYS_DEFAULT_RULE := exelink
endif
ifeq ($(MAKESYS_PROJECT_TYPE), dll)
	MAKESYS_DEFAULT_RULE := dlllink
endif
ifeq ($(MAKESYS_PROJECT_TYPE), lib)
	MAKESYS_DEFAULT_RULE := liblink
endif

#-------------------------------------------------------------------------------
# Expand user supplied file patterns into file names.
#-------------------------------------------------------------------------------
MAKESYS_CODEGEN_SOURCES := $(wildcard $(MAKESYS_CODEGEN_SOURCES))
MAKESYS_COMPILE_SOURCES := $(wildcard $(MAKESYS_COMPILE_SOURCES))

#-----------------------------------------------------------------------------------------------------------------------
# Code generation rules - protobuf compiler
#-----------------------------------------------------------------------------------------------------------------------
ifneq ($(filter %.proto,$(MAKESYS_CODEGEN_SOURCES)),)
	include $(MAKESYS_MAKESYS_ROOT)/tools/protoc.mk
endif

#-----------------------------------------------------------------------------------------------------------------------
# Compilation rules
#-----------------------------------------------------------------------------------------------------------------------
ifneq ($(filter %.cpp %.cxx %.cc %.c,$(MAKESYS_COMPILE_SOURCES)),)
	include $(MAKESYS_MAKESYS_ROOT)/tools/c++.mk
endif

#-----------------------------------------------------------------------------------------------------------------------
# Installation rules
#-----------------------------------------------------------------------------------------------------------------------
include $(MAKESYS_MAKESYS_ROOT)/tools/install.mk

#-----------------------------------------------------------------------------------------------------------------------
# Top level rules define overall build proces.
#-----------------------------------------------------------------------------------------------------------------------
.PHONY: \
	codegen	\
	compile	\
	liblink \
	dlllink	\
	exelink \
	package	\
	install	\
	cleanup	\
	clean   \
	info    \
	debug   \
	default

default : $(MAKESYS_DEFAULT_RULE)

$(MAKESYS_CODEGEN_TARGETS) : $(MAKESYS_CODEGEN_SOURCES)
codegen                    : $(MAKESYS_CODEGEN_TARGETS)

$(MAKESYS_COMPILE_TARGETS) : $(MAKESYS_COMPILE_SOURCES) $(MAKESYS_CODEGEN_TARGETS)
compile                    : $(MAKESYS_COMPILE_TARGETS)

$(MAKESYS_LIBLINK_TARGETS) : $(MAKESYS_LIBLINK_SOURCES)
liblink                    : $(MAKESYS_LIBLINK_TARGETS)

$(MAKESYS_DLLLINK_TARGETS) : $(MAKESYS_DLLLINK_SOURCES)
dlllink                    : $(MAKESYS_DLLLINK_TARGETS)

$(MAKESYS_EXELINK_TARGETS) : $(MAKESYS_EXELINK_SOURCES)
exelink                    : $(MAKESYS_EXELINK_TARGETS)

$(MAKESYS_PACKAGE_TARGETS) : $(MAKESYS_PACKAGE_SOURCES)
package                    : $(MAKESYS_PACKAGE_TARGETS)

$(MAKESYS_INSTALL_TARGETS) : $(MAKESYS_INSTALL_SOURCES)
install                    : $(MAKESYS_INSTALL_TARGETS)

cleanup : 
	rm -rf $(MAKESYS_CODEGEN_DIR) $(MAKESYS_COMPILE_DIR) $(MAKESYS_EXELINK_DIR) $(MAKESYS_DLLLINK_DIR) $(MAKESYS_LIBLINK_DIR) $(MAKESYS_PACKAGE_DIR)

clean   : cleanup

#-----------------------------------------------------------------------------------------------------------------------
# Include dependency files if present
#-----------------------------------------------------------------------------------------------------------------------
$(MAKESYS_TOOLS_CPP_DEPGEN_FILES):
include $(wildcard $(MAKESYS_TOOLS_CPP_DEPGEN_FILES))

#-----------------------------------------------------------------------------------------------------------------------
# Makefile debug utilities from C++ Journal, John Graham-Cumming.
#-----------------------------------------------------------------------------------------------------------------------
info    : print-MAKESYS_PROJECT_NAME \
          print-MAKESYS_PROJECT_TYPE \
          print-MAKESYS_MAKESYS_ROOT \
          print-MAKESYS_BUILD_ROOT   \
          print-MAKESYS_OS           \
          print-MAKESYS_ARCH         \
          print-MAKESYS_DEFAULT_RULE \
          print-MAKESYS_CODEGEN_SOURCES \
          print-MAKESYS_CODEGEN_TARGETS \
          print-MAKESYS_COMPILE_SOURCES \
          print-MAKESYS_COMPILE_TARGETS \
          print-MAKESYS_LIBLINK_SOURCES \
          print-MAKESYS_LIBLINK_TARGETS \
          print-MAKESYS_DLLLINK_SOURCES \
          print-MAKESYS_DLLLINK_TARGETS \
          print-MAKESYS_EXELINK_SOURCES \
          print-MAKESYS_EXELINK_TARGETS \
          print-MAKESYS_PACKAGE_SOURCES \
          print-MAKESYS_PACKAGE_TARGETS \
          print-MAKESYS_INSTALL_SOURCES \
          print-MAKESYS_INSTALL_TARGETS

debug   : verbose-print-MAKESYS_PROJECT_NAME \
          verbose-print-MAKESYS_PROJECT_TYPE \
          verbose-print-MAKESYS_MAKESYS_ROOT \
          verbose-print-MAKESYS_BUILD_ROOT   \
          verbose-print-MAKESYS_OS           \
          verbose-print-MAKESYS_ARCH         \
          verbose-print-MAKESYS_DEFAULT_RULE \
          verbose-print-MAKESYS_CODEGEN_SOURCES \
          verbose-print-MAKESYS_CODEGEN_TARGETS \
          verbose-print-MAKESYS_COMPILE_SOURCES \
          verbose-print-MAKESYS_COMPILE_TARGETS \
          verbose-print-MAKESYS_LIBLINK_SOURCES \
          verbose-print-MAKESYS_LIBLINK_TARGETS \
          verbose-print-MAKESYS_DLLLINK_SOURCES \
          verbose-print-MAKESYS_DLLLINK_TARGETS \
          verbose-print-MAKESYS_EXELINK_SOURCES \
          verbose-print-MAKESYS_EXELINK_TARGETS \
          verbose-print-MAKESYS_PACKAGE_SOURCES \
          verbose-print-MAKESYS_PACKAGE_TARGETS \
          verbose-print-MAKESYS_INSTALL_SOURCES \
          verbose-print-MAKESYS_INSTALL_TARGETS

print-% :
	@$(warning $*=$($*))

$(filter-out print-%, $(MAKECMDGOALS)) : $(filter print-%, $(MAKECMDGOALS))

verbose-print-% :
	@$(warning $* is $($*) ($(value $*)) (from $(origin $*)))

$(filter-out verbose-print-%, $(MAKECMDGOALS)) : $(filter verbose-print-%, $(MAKECMDGOALS))

