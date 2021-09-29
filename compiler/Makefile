MAKESYS_PROJECT_NAME = protoc-gen-luabythec
MAKESYS_PROJECT_TYPE = exe
MAKESYS_PACKAGE_ROOT = $(HOME)/opt/vcpkg/installed/x64-osx
MAKESYS_MAKESYS_ROOT = ../makesys
MAKESYS_BUILD_ROOT   = ./build

#-----------------------------------------------------------------------------------------------------------------------
# Compilation stage source files. No need to specify if all sources reside in current directory.
#-----------------------------------------------------------------------------------------------------------------------
MAKESYS_COMPILE_SOURCES := src/*cpp

#-----------------------------------------------------------------------------------------------------------------------
# Executable linker definitions. No need to define if the project does not depend on external libraries.
#-----------------------------------------------------------------------------------------------------------------------
MAKESYS_TOOLS_CPP_EXELINK_LIBS := stdc++ protoc protobuf

include $(MAKESYS_MAKESYS_ROOT)/rules.mk
