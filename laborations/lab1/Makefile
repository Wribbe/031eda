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

# Directories:
dir_exec := executables
dir_helpers := helper_scripts
dir_objects := objects
dir_sources := sources
dir_includes := includes
dir_txt := text
dir_deps := deps
# Directory lists:
dir_clean := $(dir_exec) $(dir_objects) $(dir_txt) $(dir_deps)
dir_remove := $(dir_clean) $(dir_helpers)
dir_keep := $(dir_sources) $(dir_includes)
dir_all := $(dir_remove) $(dir_keep)

# Set vpaths:
vpath %.cc $(dir_sources)
vpath %.o $(dir_objects)
vpath %.txt $(dir_txt)

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
DEPFLAGS = -MT $@ -MMD -MP -MF $(dir_deps)/$*.d
CXXFLAGS += $(DEPFLAGS)

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

all: exA1.txt

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

%.o : %.cc
	@g++ $< -c $(CPPFLAGS) $(CXXFLAGS) -o $(dir_objects)/$@

$(dir_exec)/%: %.o | setup
	@g++ $(foreach object,$^,$(dir_objects)/$(object)) -o $@

clean:
	$(call remove_dirs,$(dir_clean))
	@rm -rf ._*

remove:
	$(call remove_dirs,$(dir_remove))

setup: $(helper_paths) $(dir_all)

$(dir_all):
	$(call create_dirs,$(dir_all))

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
