#-----------------------------------------------------------------------------------------------------------------------
# Installer tool
#-----------------------------------------------------------------------------------------------------------------------
ifeq ($(MAKESYS_OS), windows)
	MAKESYS_TOOLS_INSTALL_EXE_DIR := $(MAKESYS_INSTALL_DIR)/bin
	MAKESYS_TOOLS_INSTALL_DLL_DIR := $(MAKESYS_INSTALL_DIR)/bin
	MAKESYS_TOOLS_INSTALL_LIB_DIR := $(MAKESYS_INSTALL_DIR)/lib
else
	MAKESYS_TOOLS_INSTALL_EXE_DIR := $(MAKESYS_INSTALL_DIR)/bin
	MAKESYS_TOOLS_INSTALL_DLL_DIR := $(MAKESYS_INSTALL_DIR)/bin
	MAKESYS_TOOLS_INSTALL_LIB_DIR := $(MAKESYS_INSTALL_DIR)/lib
endif

#-----------------------------------------------------------------------------------------------------------------------
# Installation definitions
#-----------------------------------------------------------------------------------------------------------------------
MAKESYS_TOOLS_INSTALL_TOOL    ?= install
MAKESYS_TOOLS_INSTALL_OPTIONS +=

#-----------------------------------------------------------------------------------------------------------------------
# Installation sources and targets
#-----------------------------------------------------------------------------------------------------------------------
ifeq ($(MAKESYS_PROJECT_TYPE), exe)
	MAKESYS_INSTALL_SOURCES := $(MAKESYS_EXELINK_TARGETS)
	MAKESYS_INSTALL_TARGETS := $(addprefix $(MAKESYS_TOOLS_INSTALL_EXE_DIR)/, $(notdir $(MAKESYS_INSTALL_SOURCES)))
endif
ifeq ($(MAKESYS_PROJECT_TYPE), dll)
	MAKESYS_INSTALL_SOURCES := $(MAKESYS_DLLLINK_TARGETS)
	MAKESYS_INSTALL_TARGETS := $(addprefix $(MAKESYS_TOOLS_INSTALL_DLL_DIR)/, $(notdir $(MAKESYS_INSTALL_SOURCES)))
endif
ifeq ($(MAKESYS_PROJECT_TYPE), lib)
	MAKESYS_INSTALL_SOURCES := $(MAKESYS_LIBLINK_TARGETS)
	MAKESYS_INSTALL_TARGETS := $(addprefix $(MAKESYS_TOOLS_INSTALL_LIB_DIR)/, $(notdir $(MAKESYS_INSTALL_SOURCES)))
endif

#-----------------------------------------------------------------------------------------------------------------------
# Installation rules
#-----------------------------------------------------------------------------------------------------------------------
$(MAKESYS_TOOLS_INSTALL_EXE_DIR)/%: $(MAKESYS_EXELINK_DIR)/%
	$(MAKESYS_TOOLS_INSTALL_TOOL) $(MAKESYS_TOOLS_INSTALL_OPTIONS) $< $(MAKESYS_TOOLS_INSTALL_EXE_DIR)

