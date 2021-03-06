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
exercises = $(call extxt, A1 A2 A3 A4 A5 Final)

all: $(exercises) | setup

$(dir_exec)/process_words: $(call objs, ngrams.o)

$(dir_output)/proc-words.txt: $(dir_inputs)/words.txt $(dir_exec)/process_words
	@$(dir_exec)/process_words $< > $@

$(dir_txt)/exA1.txt: $(call execs,process_words) $(dir_output)/proc-words.txt
	@echo_info "Creating $@."
	@echo "Creating preprocessed word list from input/words.txt to" \
		"output/proc-words.txt" > $@

# test_A2 dependencies.
$(call execs,test_A2) : $(call objs,dictionary.o)

$(dir_txt)/exA2.txt: $(call git,L02-A2,$(call execs,test_A2))
	@echo_info "Creating $@."
	@echo "Complete the Dictionary constructor." \
		"output/proc-words.txt" > $@

# test_A3_dependencies.
$(call execs,test_A3): $(call objs,word.o ngrams.o test.o)

$(dir_txt)/exA3.txt: $(call git,L02-A3,$(call execs,test_A3))
	@echo_info "Creating $@."
	@echo "Complete Word constructor and test." > $@

# test_A4_dependencies.
$(call execs,test_A4): $(call objs,ngrams.o word.o dictionary.o test.o)

# test_A4_dependencies.
$(dir_txt)/exA4.txt: $(call execs,test_A4)
	@echo_info "Creating $@."
	@echo "Expand Dictionary class and test." > $@

# test_A5_dependencies.
$(call execs,test_A5): $(call objs,ngrams.o word.o dictionary.o test.o)

# test_A5_dependencies.
$(dir_txt)/exA5.txt: $(call execs,test_A5)
	@echo_info "Creating $@."
	@echo "Expand Dictionary class and test." > $@

# spell dependencies.
$(call execs,spell): $(call objs,ngrams.o word.o dictionary.o)

# test_Final_dependencies.
$(dir_txt)/exFinal.txt: $(call execs,spell)
	@echo_info "Creating $@."
	@echo "Compiling and running the supplied test program." > $@

include $(dir_make_utils)/postamble_makefile
