# Makefile for C++ laboratory session 01.
# ---------------------------------------

# Make flags:
# -----------
MAKEFLAGS=--warn-undefined-variables

# Variables.
# ----------

# Boolean variables:
True:=True
False:=False

# Output control:
export OUT_INFO:=$(True)
export OUT_WARNING:=$(True)
OUT_COMPILATION:=$(False)

# Directories:
dir_exec := bin
dir_helpers := helper_scripts
dir_objects := objects
dir_sources := sources
dir_includes := includes
dir_txt := text
dir_deps := deps
dir_lib := lib
# Directory lists:
dir_clean := $(dir_exec) $(dir_objects) $(dir_txt) $(dir_deps)
dir_remove := $(dir_clean) $(dir_helpers)
dir_keep := $(dir_sources) $(dir_includes) $(dir_lib)
dir_all := $(dir_remove) $(dir_keep)

# Set vpaths (vpath is for source only):
vpath %.cc $(dir_sources)
vpath %.cc $(dir_lib)
vpath %.txt $(dir_txt)
vpath %.d $(dir_deps)

# File_lists:
CC_sources = $(foreach path,\
			 	$(wildcard $(dir_sources)/*.cc),\
				$(patsubst $(dir_sources)/%,%,$(path))\
			  )

# Output scripts.
echo_info := echo_info
echo_warning := echo_warning
helpers := $(echo_info) $(echo_warning)
helper_paths := $(foreach name,$(helpers),$(dir_helpers)/$(name))
# Add helpers to path.
export PATH := $(shell pwd)/$(dir_helpers):$(PATH)

# Compiler options:
# -----------------
CPPFLAGS += -g -std=c++11 -Wall -Wextra -pedantic-errors -Wold-style-cast
INCLUDE_FLAGS = -I$(dir_includes)
CPPFLAGS += $(INCLUDE_FLAGS)
DEPFLAGS = -MT $@ -MMD -MP -MF $(dir_deps)/$*.d
CXXFLAGS += $(DEPFLAGS)
CXX = g++

# Utilities.
# ----------

create_dirs = \
	@for dir in $(1) ; do \
		if [ ! -d $$dir ]; then \
		    echo_info "Can't find directory: <$$dir>, creating."; \
			mkdir $$dir; \
		fi \
	done

remove_dirs = \
	@for dir in $(1) ; do \
		if [ -d $$dir ]; then \
			if [ -f "$(dir_helpers)/$(echo_info)" ]; then \
			    echo_info "Removing directory <$$dir>."; \
			fi; \
		    rm -rf $$dir; \
		fi;\
	done; \


# Recipes.
# --------

# Exercise creation and running.

all: exA1.txt exA4.txt

run: all
	@echo_info "exA1.txt info:"
	@cat $(dir_txt)/exA1.txt
	@echo_info "Executing exA1."
	@$(dir_exec)/hello
	@echo_info "Executing exA1 done."

exA1.txt: $(dir_exec)/hello
	@echo_info "Creating: $@."
	@echo "Simple Hello World program compiled do $(dir_exec)/hello." >\
	       $(dir_txt)/$@

exA4.txt: $(dir_exec)/ltest
	@echo_info "Creating: $@."
	@echo "Linked list implementation for int variables, reults in $(dir_exec)/ltest." >\
	       $(dir_txt)/$@


# Compilation, linking and folder operations.

o_from_cc = $(CXX) $< -c $(CPPFLAGS) $(CXXFLAGS) -o $(dir_objects)/$@
exec_from_o = $(CXX) $(foreach object,$^,$(dir_objects)/$(object)) -o $@
# Prepend @ sign if OUT_COMPILATION == False.
ifeq ($(OUT_COMPILATION), $(False))
$(eval o_from_cc = @$(value o_from_cc))
$(eval exec_from_o = @$(value exec_from_o))
endif

%.o : %.cc
	$(o_from_cc)

$(dir_exec)/%: %.o | setup
	$(exec_from_o)

clean:
	$(call remove_dirs,$(dir_clean))
	@rm -rf ._*

remove:
	$(call remove_dirs,$(dir_remove))

setup: $(helper_paths) $(dir_all)

$(dir_all):
	$(call create_dirs,$(dir_all))

# Creating and writing helper scripts.

$(helper_paths):
	@# Bootstrap directory creation for helper scripts, since create_dirs uses
	@# helper scripts.
	@if [ ! -d $(dir_helpers) ] ; then \
		mkdir $(dir_helpers); \
	 fi
	@# Write echo_info utility to disk.
	@(echo "#!/bin/sh" &&\
	  echo "if [ \"\$$OUT_INFO\" = \"$(True)\" ] ; then"  &&\
	  echo "   echo [?]: \$$1;" &&\
	  echo "fi" &&\
	  echo "") > $(dir_helpers)/$(echo_info)
	@# Make echo_info executable.
	@chmod a+x $(dir_helpers)/$(echo_info)
	@# Write echo_warning utility to disk.
	@(echo "#!/bin/sh" &&\
	  echo "if [ \"\$$OUT_WARNING\" = \"$(True)\" ] ; then"  &&\
	  echo "   echo [!]: \$$1;" &&\
	  echo "fi" &&\
	  echo "") > $(dir_helpers)/$(echo_warning)
	@# Make echo_warning executable.
	@chmod a+x $(dir_helpers)/$(echo_warning)
	@echo_info "Helper scrips created."

# Phony targets.
# --------------

.PHONY: all setup remove clean

# *d-file inclusion.
# ------------------
D_FILES := $(foreach source,$(CC_sources),$(dir_deps)/$(source:.cc=.d))
-include D_FILES
