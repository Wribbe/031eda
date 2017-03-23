# Makefile for c++ project in EDA031.

# Disable use of implicit rules and variables.
MAKEFLAGS += --no-builtin-rules --no-builtin-variables
# Same as the following
# MAKEFLAGS += -r -R

dirs := sources \
		docs \
		includes \
		bin \
		objects \
		lib \
		lib/static
remove_on_clean := bin objects lib/static
# Prefix for dir variables.
dir_var_prefix := dir_

# Create all dir variables.
$(foreach dir,$(dirs),\
	$(eval $(dir_var_prefix)$(subst /,_,$(dir)) := $(dir)) \
)

SRC_EXTENSION = .cc
# Set path for source files.
vpath %$(SRC_EXTENSION) $(dir_lib) $(dir_sources)

CXX = g++

DEBUG_FLAGS := -g
INCUDE_FLAGS := -I$(dir_includes)

CXXFLAGS := -Wall -Wextra -pedantic-errors -Wold-style-cast -std=c++11
CXXFLAGS += $(DEBUG_FLAGS)
CXXFLAGS += $(INCUDE_FLAGS)

# Find and save path to all source files.
CC_SOURCES := $(wildcard $(dir_sources)/*$(SRC_EXTENSION))

# For all found source files, replace $(SRC_EXTENSION) with '', take the file
# part of the path and put the resulting target in the bin folder.
EXECS := $(foreach path,$(CC_SOURCES),$(dir_bin)/$(notdir $(path:$(SRC_EXTENSION)=)))

# Helper function for calling several objects as prerequisites.
objs = $(foreach name,$(1),$(dir_objects)/$(name).o)
# Helper function for calling libraries as prerequisites.
libs = $(foreach name,$(1),$(dir_lib_static)/$(name).a)

# All executables are prerequisites for target all.
all : $(EXECS)

# Helper function to create directories if they are missing.
create_missing_path = $(if $(wildcard $(1)/*),,$(shell mkdir -p $(1)))
# Recipe for how to create directories.
$(dirs) :
	$(call create_missing_path,$@)

bin/% : $(call objs,%) $(call libs,libclientserver)
	$(CXX) -o $@ $^

$(call objs,%): %$(SRC_EXTENSION) | $(dirs)
	$(CXX) $^ -c -o $@ $(CXXFLAGS)

# Recipe to create libclientserver.a.
$(call libs,libclientserver): $(call objs,connection server)
	ar rv $@ $^
	@ranlib $@

clean :
	@rm -rf $(remove_on_clean)

re: clean all

.PHONY: all clean re
