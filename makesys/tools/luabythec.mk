#-------------------------------------------------------------------------------
# Protobuf and Lua bindings code generation step
#-------------------------------------------------------------------------------
ifndef MAKESYS_CODEGEN_SOURCES
    MAKESYS_CODEGEN_SOURCES += $(wildcard *.proto src/*.proto)
endif

MAKESYS_CODEGEN_TARGETS += $(patsubst %.proto, $(MAKESYS_BUILD_ROOT)/%.pb.cc,       $(MAKESYS_CODEGEN_SOURCES)) \
                           $(patsubst %.proto, $(MAKESYS_BUILD_ROOT)/%.pb.h,        $(MAKESYS_CODEGEN_SOURCES)) \
                           $(patsubst %.proto, $(MAKESYS_BUILD_ROOT)/%.luabythec.h, $(MAKESYS_CODEGEN_SOURCES))

#-------------------------------------------------------------------------------
# Protobuf code generation rules
#-------------------------------------------------------------------------------
%.pb.h %.pb.cc %.luabythec.h: %.proto
	protoc --cpp_out=. --luabythec_out=. $<

