#-----------------------------------------------------------------------------------------------------------------------
# The C++ compiler toolset.
#-----------------------------------------------------------------------------------------------------------------------
ifeq ($(MAKESYS_OS),windows)
	MAKESYS_TOOLS_CPP_OBJ_EXT := .obj
	MAKESYS_TOOLS_CPP_EXE_EXT := .exe
	MAKESYS_TOOLS_CPP_DLL_PFX := 
	MAKESYS_TOOLS_CPP_DLL_EXT ?= .dll
	MAKESYS_TOOLS_CPP_LIB_PFX := 
	MAKESYS_TOOLS_CPP_LIB_EXT := .lib
else
	MAKESYS_TOOLS_CPP_OBJ_EXT := .o
	MAKESYS_TOOLS_CPP_EXE_EXT := 
	MAKESYS_TOOLS_CPP_DLL_PFX := lib
	MAKESYS_TOOLS_CPP_DLL_EXT ?= .so
	MAKESYS_TOOLS_CPP_LIB_PFX := lib
	MAKESYS_TOOLS_CPP_LIB_EXT := .a
endif

#-----------------------------------------------------------------------------------------------------------------------
# Compiler definitions
#-----------------------------------------------------------------------------------------------------------------------
MAKESYS_TOOLS_CPP_COMPILE_TOOL    ?= $(CXX)
MAKESYS_TOOLS_CPP_COMPILE_OPTIONS += -ftemplate-depth-128 -w -pedantic -std=c++17
MAKESYS_TOOLS_CPP_COMPILE_INCPATH +=

ifdef DEBUG
    MAKESYS_TOOLS_CPP_COMPILE_OPTIONS += -g -D_DEBUG
else
    MAKESYS_TOOLS_CPP_COMPILE_OPTIONS += -DNDEBUG
endif

#-----------------------------------------------------------------------------------------------------------------------
# Compilation sources and targets
#-----------------------------------------------------------------------------------------------------------------------
MAKESYS_COMPILE_TARGETS += $(patsubst %.cpp,$(MAKESYS_COMPILE_DIR)/%$(MAKESYS_TOOLS_CPP_OBJ_EXT), \
                           $(patsubst %.cxx,$(MAKESYS_COMPILE_DIR)/%$(MAKESYS_TOOLS_CPP_OBJ_EXT), \
                           $(patsubst %.cc,$(MAKESYS_COMPILE_DIR)/%$(MAKESYS_TOOLS_CPP_OBJ_EXT), \
                           $(patsubst %.c,$(MAKESYS_COMPILE_DIR)/%$(MAKESYS_TOOLS_CPP_OBJ_EXT),$(MAKESYS_COMPILE_SOURCES)))))

#-----------------------------------------------------------------------------------------------------------------------
# Compiler dependency generator
#-----------------------------------------------------------------------------------------------------------------------
MAKESYS_TOOLS_CPP_DEPGEN_OPTIONS  = -MT $@ -MMD -MP -MF $(MAKESYS_COMPILE_DIR)/$*.d
MAKESYS_TOOLS_CPP_DEPGEN_FILES   := $(patsubst %$(MAKESYS_TOOLS_CPP_OBJ_EXT),%.d,$(MAKESYS_COMPILE_TARGETS))

#-----------------------------------------------------------------------------------------------------------------------
# Compilation rules
#-----------------------------------------------------------------------------------------------------------------------
$(MAKESYS_COMPILE_DIR)/%$(MAKESYS_TOOLS_CPP_OBJ_EXT): %.cpp $(MAKESYS_COMPILE_DIR)/%.d
	@mkdir -p $(@D)
	$(MAKESYS_TOOLS_CPP_COMPILE_TOOL) $(MAKESYS_TOOLS_CPP_DEPGEN_OPTIONS) $(MAKESYS_TOOLS_CPP_COMPILE_OPTIONS) $(patsubst %,-I%, $(MAKESYS_TOOLS_CPP_COMPILE_INCPATH)) -c -o $@ $<

$(MAKESYS_COMPILE_DIR)/%$(MAKESYS_TOOLS_CPP_OBJ_EXT): %.cxx $(MAKESYS_COMPILE_DIR)/%.d
	@mkdir -p $(@D)
	$(MAKESYS_TOOLS_CPP_COMPILE_TOOL) $(MAKESYS_TOOLS_CPP_DEPGEN_OPTIONS) $(MAKESYS_TOOLS_CPP_COMPILE_OPTIONS) $(patsubst %,-I%, $(MAKESYS_TOOLS_CPP_COMPILE_INCPATH)) -c -o $@ $<

$(MAKESYS_COMPILE_DIR)/%$(MAKESYS_TOOLS_CPP_OBJ_EXT): %.cc  $(MAKESYS_COMPILE_DIR)/%.d
	@mkdir -p $(@D)
	$(MAKESYS_TOOLS_CPP_COMPILE_TOOL) $(MAKESYS_TOOLS_CPP_DEPGEN_OPTIONS) $(MAKESYS_TOOLS_CPP_COMPILE_OPTIONS) $(patsubst %,-I%, $(MAKESYS_TOOLS_CPP_COMPILE_INCPATH)) -c -o $@ $<

$(MAKESYS_COMPILE_DIR)/%$(MAKESYS_TOOLS_CPP_OBJ_EXT): %.c   $(MAKESYS_COMPILE_DIR)/%.d
	@mkdir -p $(@D)
	$(MAKESYS_TOOLS_CPP_COMPILE_TOOL) $(MAKESYS_TOOLS_CPP_DEPGEN_OPTIONS) $(MAKESYS_TOOLS_CPP_COMPILE_OPTIONS) $(patsubst %,-I%, $(MAKESYS_TOOLS_CPP_COMPILE_INCPATH)) -c -o $@ $<

#-----------------------------------------------------------------------------------------------------------------------
# Linking executable definitions
#-----------------------------------------------------------------------------------------------------------------------
MAKESYS_TOOLS_CPP_EXELINK_TOOL    ?= $(CXX)
MAKESYS_TOOLS_CPP_EXELINK_OPTIONS +=
MAKESYS_TOOLS_CPP_EXELINK_LIBPATH +=
MAKESYS_TOOLS_CPP_EXELINK_LIBS    +=

#-----------------------------------------------------------------------------------------------------------------------
# Linking executable sources and targets
#-----------------------------------------------------------------------------------------------------------------------
MAKESYS_EXELINK_SOURCES += $(MAKESYS_COMPILE_TARGETS)
MAKESYS_EXELINK_TARGETS += $(MAKESYS_EXELINK_DIR)/$(MAKESYS_PROJECT_NAME)$(MAKESYS_TOOLS_CPP_EXE_EXT)

#-----------------------------------------------------------------------------------------------------------------------
# Executable linking rules
#-----------------------------------------------------------------------------------------------------------------------
$(MAKESYS_EXELINK_DIR)/%$(MAKESYS_TOOLS_CPP_EXE_EXT): $(MAKESYS_TOOLS_CPP_EXELINK_SOURCES)
	@mkdir -p $(@D)
	$(MAKESYS_TOOLS_CPP_EXELINK_TOOL) $(MAKESYS_TOOLS_CPP_EXELINK_OPTIONS) $(patsubst %,-L %, $(MAKESYS_TOOLS_CPP_EXELINK_LIBPATH)) -o $@ $(MAKESYS_EXELINK_SOURCES) $(patsubst %,-l%, $(MAKESYS_TOOLS_CPP_EXELINK_LIBS))

