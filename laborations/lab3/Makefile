# Makefile for C++ laboratory session 02.
# ---------------------------------------

dir_make_utils = ../makefile_utils
include $(dir_make_utils)/preamble_makefile

# Output control:
export OUT_INFO := $(True)
export OUT_WARNING := $(True)
OUT_COMPILATION:=$(True)
#OUT_COMPILATION := $(False)
OUTPUT_DYN_LIB := $(False)
OUTPUT_LIB := $(False)


# Functionality toggles:
GIT_TARGETS := $(True)
SUPPRESS_GIT_OUTPUT := $(True)

# Compiler options:
# -----------------
CPPFLAGS += -g -std=c++11 -Wall -Wextra -pedantic-errors -Wold-style-cast
INCLUDE_FLAGS = -I$(dir_includes)
CPPFLAGS += $(INCLUDE_FLAGS)
DEPFLAGS = -MT $@ -MMD -MP -MF $(dir_deps)/$*.d
CXXFLAGS += $(DEPFLAGS)
CXX = g++
LDFLAGS += -L./$(dir_static_lib)
DYNAMIC_LDFLAGS += -L./$(dir_dynamic_lib)

# Compilation commands:
o_from_cc = $(CXX) -c $< $(CPPFLAGS) $(CXXFLAGS) -o $@
exec_from_o = $(CXX) -o $@ $(call get_obj,$^) $(CPPFLAGS) $(call get_slibs,$^) \
			  $(call get_dlibs,$^)
a_from_os = ar crv $@ $^
so_from_os = $(CXX) -shared -Wl,-soname,$(call soname,$(notdir $@)) -o $@ $^

include $(dir_make_utils)/suppression_makefile

# Recipes.
# --------

# Library dependencies.

# Exercise creation and running.

extxt = $(foreach exercise,${1},ex${exercise}.txt)
exercises = $(call extxt, A1 A2)

all: $(exercises) | setup

# test_A1 dependencies.
$(call execs,test_A1) : $(call objs,test.o tag_remover.o)

$(dir_txt)/exA1.txt: $(call execs,test_A1)
	@echo_info "Creating $@."
	@echo "Implement class TagRemover to remove HTML tags." > $@

$(dir_txt)/exA2.txt: $(call execs,string_sieve)
	@echo_info "Creating $@."
	@echo "Implement class TagRemover to remove HTML tags." > $@

include $(dir_make_utils)/postamble_makefile
