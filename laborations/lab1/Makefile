# Makefile for C++ laboratory session 01.
# ---------------------------------------

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
# Directory lists:
dir_light_clean := $(dir_exec) $(dir_objects)
dir_full_clean := $(dir_light_clean) $(dir_helpers)
dir_non_removable := $(dir_sources) $(dir_includes)
dir_all := $(dir_full_clean) $(dir_non_removable)

# Output scripts.
echo_info := echo_info
echo_warning := echo_warning
helpers := $(echo_info) $(echo_warning)
helper_paths := $(foreach name,$(helpers),$(dir_helpers)/$(name))
# Add helpers to path.
export PATH := $(shell pwd)/$(dir_helpers):$(PATH)

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

all: | setup

clean:
	$(call remove_dirs,$(dir_light_clean))
	@rm -rf ._*

remove:
	$(call remove_dirs,$(dir_full_clean))

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
