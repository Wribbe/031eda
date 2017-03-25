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
			sources/generators\
			sources/generated \
		docs \
		includes \
		bin \
			bin/generators \
			bin/generated \
		objects \
		lib \
			lib/static
# Clean up bin files but not jar-files.
non_jar_binfiles := $(filter-out %.jar,$(wildcard bin/*))
remove_on_clean := objects lib/static $(non_jar_binfiles) sources/generated
# Prefix for dir variables.
dir_var_prefix := dir_

# Create all dir variables replace '/' in sub-dirs with '_'.
$(foreach dir,$(dirs),\
	$(eval $(dir_var_prefix)$(subst /,_,$(dir)) := $(dir)) \
)

SRC_EXTENSION = .cc
# Set path for source files.
vpath %$(SRC_EXTENSION) $(dir_lib) \
						$(dir_sources) \
						$(dir_sources_generators) \
						$(dir_sources_generated)

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

# Helper function for extracting and returning a specific line from a file and
# stripping any comments.
get_raw_line = $(foreach token,$(subst //,,$(shell sed -n $(1)p $(2))),$(strip $(token)))
# Function that strips tag and only returns the words after said tag.
get_line = $(strip  $(eval eval_line := $(call get_raw_line,$(1),$(2)))\
			$(foreach token,$(filter-out $(firstword $(eval_line)),$(eval_line)),$(strip $(token))))

define \n =



endef
null :=
\t :=$(null)	$(null)
space := $(null) $(null)

space_sub = !!
pack = $(subst $(space),$(space_sub),$(1))
unpack = $(subst $(space_sub),$(space),$(1))


# Find generator sources.
GENERATORS := $(foreach path,$(wildcard $(dir_sources_generators)/*$(SRC_EXTENSION))\
				,$(eval eval_generator_bin := $(dir_bin_generators)/$(notdir $(path:$(SRC_EXTENSION)=)))\
				$(eval_generator_bin)\
				$(eval eval_gen_output := $(dir_sources_generated)/$(call get_line,2,$(path)))\
				$(eval eval_gen_input := $(call get_line,1,$(path)))\
				$(eval RULE_TOKENS += $(call pack,$(eval_gen_output) $(eval_gen_input) $(eval_generator_bin) ))\
				$(eval GENERATED_BINS += $(dir_bin_generated)/$(notdir $(eval_gen_output:$(SRC_EXTENSION)=)))\
			)\

# Helper function for calling several objects as prerequisites.
objs = $(foreach name,$(1),$(dir_objects)/$(name).o)
# Helper function for calling libraries as prerequisites.
libs = $(foreach name,$(1),$(dir_lib_static)/$(name).a)

# All executables are prerequisites for target all.
all : $(GENERATORS) $(GENERATED_BINS) $(EXECS)

# Create generation targets.
$(foreach token_pack,$(RULE_TOKENS),\
	$(eval eval_tokens := $(call unpack,$(token_pack)))\
	$(eval eval_output := $(firstword $(eval_tokens)))\
	$(eval eval_inputs := $(filter-out $(eval_output),$(eval_tokens)))\
	$(eval $(eval_output) : $(eval_inputs)\
	$(\n)$(\t)$(lastword $(eval_inputs)) $(firstword $(eval_inputs)) > $$@)\
)

# Helper function to create directories if they are missing.
create_missing_path = $(if $(wildcard $(1)/*),,$(shell mkdir -p $(1)))
# Tell make how to make missing directories.
$(dirs) :
	$(call create_missing_path,$@)

# General recipe for executables.
make_executables = $(CXX) -o $@ $^

# Special path specification for generated executables.
$(dir_bin_generated)/% : $(dir_objects)/%.o $(call libs,libclientserver)
	$(make_executables)

# Special path specification for generator executables.
$(dir_bin_generators)/% : $(dir_objects)/%.o $(call libs,libclientserver)
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
$(call libs,libclientserver): $(call objs,connection server print_functions)
	@ar rv $@ $^
	@ranlib $@

# Clean up temporary files.
clean :
	@rm -rf $(remove_on_clean)

# Clean and redo all target.
re: clean all


.PHONY: all clean re
