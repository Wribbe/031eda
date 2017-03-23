# Makefile for c++ project in EDA031.
# -----------------------------------
# Author: Stefan Eng <atn08sen@student.lu.se>
# Date: 2017-03-23

# Disable use of implicit rules and variables.
MAKEFLAGS += --no-builtin-rules --no-builtin-variables
# Same as the following
# MAKEFLAGS += -r -R

# The directories that exist in the project.
dirs := sources \
			sources/helpers\
		docs \
		includes \
		bin \
			bin/helpers \
		objects \
		lib \
			lib/static
# Clean up bin files but not jar-files.
non_jar_binfiles := $(filter-out %.jar,$(wildcard bin/*))
remove_on_clean := objects lib/static $(non_jar_binfiles)
# Prefix for dir variables.
dir_var_prefix := dir_

# Create all dir variables.
$(foreach dir,$(dirs),\
	$(eval $(dir_var_prefix)$(subst /,_,$(dir)) := $(dir)) \
)

SRC_EXTENSION = .cc
# Set path for source files.
vpath %$(SRC_EXTENSION) $(dir_lib) $(dir_sources) $(dir_sources_helpers)

# Set compiler and compiler flags.
CXX = g++

DEBUG_FLAGS := -g
INCUDE_FLAGS := -I$(dir_includes)

CXXFLAGS := -Wall -Wextra -pedantic-errors -Wold-style-cast -std=c++11
CXXFLAGS += $(DEBUG_FLAGS)
CXXFLAGS += $(INCUDE_FLAGS)

# Find and save path to all source files.
CC_SOURCES := $(wildcard $(dir_sources)/*$(SRC_EXTENSION))


# For all found source files, replace $(SRC_EXTENSION) with '', take the file
# part of the path and construct the path so that the target target ends up in
# the bin folder.
EXECS := $(foreach path,$(CC_SOURCES),$(dir_bin)/$(notdir $(path:$(SRC_EXTENSION)=)))

# Find and add helper sources.
EXECS += $(foreach path,$(wildcard $(dir_sources_helpers)/*$(SRC_EXTENSION)), \
			 $(dir_bin_helpers)/$(notdir $(path:$(SRC_EXTENSION)=)) \
		 )

# Helper function for calling several objects as prerequisites.
objs = $(foreach name,$(1),$(dir_objects)/$(name).o)
# Helper function for calling libraries as prerequisites.
libs = $(foreach name,$(1),$(dir_lib_static)/$(name).a)

# All executables are prerequisites for target all.
all : $(EXECS)

# Helper function to create directories if they are missing.
create_missing_path = $(if $(wildcard $(1)/*),,$(shell mkdir -p $(1)))
# Tell make how to make missing directories.
$(dirs) :
	$(call create_missing_path,$@)

# General recipe for executables.
make_executables = $(CXX) -o $@ $^

# Special path specification for helper executables.
bin/helpers/% : $(dir_objects)/%.o
	$(make_executables)

# Case for regular executables.
$(dir_bin)/% : $(call objs,%) $(call libs,libclientserver)
	$(make_executables)

# Tell make how to make object files.

# NOTE:
# -----
# Here objects depend on that $(dirs) are created, but we don't want to have
# the directories as update-prerequisites. That's why the $(dirs) are after the
# pipe '|' symbol . This tells make that the directories are a dependency that
# should exist, but we don't care if they are older/newer then any of our
# object source files.
# (For additional information google: 'order-only prerequisites gnu make' or go
# here:
# https://www.gnu.org/software/make/manual/html_node/Prerequisite-Types.html)
$(call objs,%): %$(SRC_EXTENSION) | $(dirs)
	$(CXX) $^ -c -o $@ $(CXXFLAGS)

# Recipe to create libclientserver.a.
$(call libs,libclientserver): $(call objs,connection server)
	@ar rv $@ $^
	@ranlib $@

# Clean up temporary files.
clean :
	@rm -rf $(remove_on_clean)

# Clean and redo all target.
re: clean all

.PHONY: all clean re
