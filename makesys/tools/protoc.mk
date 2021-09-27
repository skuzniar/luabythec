#-----------------------------------------------------------------------------------------------------------------------
# Protobuf compiler tool
#-----------------------------------------------------------------------------------------------------------------------
ifeq ($(MAKESYS_TOOLS_PROTOBUF_COMPILE_TOOL),)
	ifneq ($(MAKESYS_PACKAGE_ROOT),)
		ifneq ($(wildcard $(MAKESYS_PACKAGE_ROOT)/tools/protobuf/protoc),)
			MAKESYS_TOOLS_PROTOBUF_COMPILE_TOOL := $(MAKESYS_PACKAGE_ROOT)/tools/protobuf/protoc
		endif
	endif
endif
MAKESYS_TOOLS_PROTOBUF_COMPILE_TOOL    ?= protoc
MAKESYS_TOOLS_PROTOBUF_COMPILE_OUTPUT  ?= cpp
MAKESYS_TOOLS_PROTOBUF_COMPILE_OPTIONS +=

#-----------------------------------------------------------------------------------------------------------------------
# Protobuf compilation sources and targets
#-----------------------------------------------------------------------------------------------------------------------
ifeq ($(findstring cpp,$(MAKESYS_TOOLS_PROTOBUF_COMPILE_OUTPUT)),cpp)
	MAKESYS_CODEGEN_TARGETS += $(patsubst %.proto,$(MAKESYS_CODEGEN_DIR)/%.pb.cc,$(MAKESYS_CODEGEN_SOURCES)) \
	                           $(patsubst %.proto,$(MAKESYS_CODEGEN_DIR)/%.pb.h,$(MAKESYS_CODEGEN_SOURCES))
endif

ifeq ($(findstring luabythec,$(MAKESYS_TOOLS_PROTOBUF_COMPILE_OUTPUT)),luabythec)
	MAKESYS_CODEGEN_TARGETS += $(patsubst %.proto,$(MAKESYS_CODEGEN_DIR)/%.luabythec.hpp,$(MAKESYS_CODEGEN_SOURCES))
endif

#-----------------------------------------------------------------------------------------------------------------------
# Generated code must be compiled
#-----------------------------------------------------------------------------------------------------------------------
MAKESYS_COMPILE_SOURCES += $(filter %.cc, $(MAKESYS_CODEGEN_TARGETS))

#-----------------------------------------------------------------------------------------------------------------------
# Generated headers must be accessible in the compiletion step
#-----------------------------------------------------------------------------------------------------------------------
MAKESYS_TOOLS_CPP_COMPILE_INCPATH += $(MAKESYS_CODEGEN_DIR)

#-----------------------------------------------------------------------------------------------------------------------
# Protobuf compilation rules
#-----------------------------------------------------------------------------------------------------------------------
$(MAKESYS_CODEGEN_DIR)/%.pb.cc $(MAKESYS_CODEGEN_DIR)/%.pb.h $(MAKESYS_CODEGEN_DIR)/%.luabythec.hpp: %.proto
	@mkdir -p $(@D)
	$(MAKESYS_TOOLS_PROTOBUF_COMPILE_TOOL) $(MAKESYS_TOOLS_PROTOBUF_COMPILE_OPTIONS) $(patsubst %,--%_out=$(MAKESYS_CODEGEN_DIR),$(MAKESYS_TOOLS_PROTOBUF_COMPILE_OUTPUT)) $<

