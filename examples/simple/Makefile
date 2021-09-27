MAKESYS_PROJECT_NAME = simple
MAKESYS_PROJECT_TYPE = exe
MAKESYS_PACKAGE_ROOT = /usr/local/opt/vcpkg/libexec/installed/x64-osx
MAKESYS_MAKESYS_ROOT = ../../makesys
MAKESYS_BUILD_ROOT   = ./build

#-----------------------------------------------------------------------------------------------------------------------
# Code generation stage. List of source files.
#-----------------------------------------------------------------------------------------------------------------------
MAKESYS_CODEGEN_SOURCES := def/*proto

#-----------------------------------------------------------------------------------------------------------------------
# Code generation stage. Types of output. No need to define if the output is cpp soiurce and header.
#-----------------------------------------------------------------------------------------------------------------------
MAKESYS_TOOLS_PROTOBUF_COMPILE_OUTPUT  := cpp luabythec

#-----------------------------------------------------------------------------------------------------------------------
# Compilation stage. List of source files.
#-----------------------------------------------------------------------------------------------------------------------
MAKESYS_COMPILE_SOURCES := src/*cpp

#-----------------------------------------------------------------------------------------------------------------------
# Compilation stage. Add necessary include paths.
#-----------------------------------------------------------------------------------------------------------------------
MAKESYS_TOOLS_CPP_COMPILE_INCPATH += /usr/local/include/lua

#-----------------------------------------------------------------------------------------------------------------------
# Executable linking stage. List of libraries. No need to define if the project does not depend on external libraries.
#-----------------------------------------------------------------------------------------------------------------------
MAKESYS_TOOLS_CPP_EXELINK_LIBS := stdc++ protobuf lua

include $(MAKESYS_MAKESYS_ROOT)/rules.mk

#-----------------------------------------------------------------------------------------------------------------------
# Add rule to execute the program
#-----------------------------------------------------------------------------------------------------------------------
run:
	$(firstword $(MAKESYS_EXELINK_TARGETS))

