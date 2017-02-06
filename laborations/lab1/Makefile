# Makefile for C++ laboratory session 01.
# ---------------------------------------

dir_make_utils = ../makefile_utils
include $(dir_make_utils)/preamble_makefile

# Output control:
export OUT_INFO := $(True)
export OUT_WARNING := $(True)
#OUT_COMPILATION:=$(True)
OUT_COMPILATION := $(False)
OUTPUT_DYN_LIB := $(False)
OUTPUT_LIB := $(False)

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
$(dir_dynamic_lib)/liblab1.so.1 : $(call fobjs, list.o coding.o)
$(dir_static_lib)/liblab1.a : $(call objs,list.o coding.o)

$(dir_exec)/ltest: $(dir_objects)/list.o
$(call execs,decode encode) : $(dir_objects)/coding.o

$(call execs,static_ltest static_encode static_decode) : $(dir_static_lib)/liblab1.a
$(call execs,dynamic_ltest dynamic_encode dynamic_decode) : $(dir_dynamic_lib)/liblab1.so.1

# Exercise creation and running.

all: exA1.txt exA4.txt exA5.txt exA8.txt exA9.txt

run: all
	@echo_info "exA1.txt info:"
	@cat $(dir_txt)/exA1.txt
	@echo_info "Executing exA1."
	@$(dir_exec)/hello
	@echo_info "Executing exA1 done."

exA1.txt: $(dir_exec)/hello
	@echo_info "Creating: $@."
	@echo "Simple Hello World program compiled to $(dir_exec)/hello." >\
	       $(dir_txt)/$@

exA4.txt: $(dir_exec)/ltest
	@echo_info "Creating: $@."
	@echo "Test of linked list implementation for int variables, reults in"\
		  "$(dir_exec)/ltest." > $(dir_txt)/$@

exA5.txt: $(dir_exec)/encode $(dir_exec)/decode
	@echo_info "Creating: $@."
	@echo "Create basic text scrambelers and store them in"\
		  "$(dir_exec)/(endcode/decode)." > $(dir_txt)/$@

exA8.txt: $(call execs,static_ltest static_encode static_decode)
	@echo_info "Creating: $@."
	@echo "Assemble different objects into a static library and using it to "\
		  "link to static_ltest,static_encode/_decode." > $(dir_txt)/$@

exA9.txt: $(call execs,dynamic_ltest dynamic_encode dynamic_decode)
	@echo_info "Creating: $@."
	@echo "Assemble different objects into a dynamic library and using it to "\
		  "link to dynamic_ltest,dynamic_encode/_decode." > $(dir_txt)/$@

include $(dir_make_utils)/postamble_makefile
