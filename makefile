# Files
sources := main tmp
libs := SDL2main SDL2
output := phthonus

dynamiclibs := SDL2

# Directories
inc := include h
lib := lib
src := src
build := build
bin := bin

libext:=
execext:=
ifeq ($(OS),Windows_NT)
	libext :=.dll
	execext :=.exe
else
  uname_s := $(shell uname -s)
endif

ifeq ($(uname_s),Darwin)
	libext :=.dylib
endif
ifeq ($(uname_s),Linux)
	libext :=.so
endif

cc := clang

compileflags := -std=c11
linkflags :=
warnings := all extra pedantic

compileflags := $(compileflags) $(foreach w,$(warnings),-W$(w))
linkflags := $(linkflags)

libargs := $(foreach l,$(libs),-l$(l))
objfiles := $(foreach f,$(sources),$(f).o)
objpaths := $(foreach f,$(objfiles),$(build)/$(f))

dynamiclibs := $(foreach lib,$(dynamiclibs),$(lib)$(libext))
outputfile := $(output)$(execext)

incdirs := $(foreach d,$(inc),-I$(d))
libdirs := $(foreach d,$(lib),-L$(d))

vpath %.o $(build)
vpath %.c $(src)
vpath %$(libext) $(bin)
vpath %$(execext) $(bin)

.PHONY: all tag clean fresh compile_commands

all: tag $(outputfile) $(dynamiclibs)

fresh: tag clean all

tag:
	@echo "* ---------------------------- "
	@echo "* Building for: $(OS)"
	@echo "*   executable: $(outputfile)"
	@echo "*   requires: $(dynamiclibs)"
	@echo "* ---------------------------- "

clean:
	@echo "cleaning generated files"
	-rm -f $(objpaths)
	-rm -f $(outputfile)
	-rm -f $(foreach lib,$(dynamiclibs),$(bin)/$(lib))
	ls $(build) $(bin)

# Linking
$(outputfile): $(objfiles)
	$(cc) $(objpaths) $(linkflags) $(libdirs) $(libargs) -o $(bin)/$@

# Compiling object files
%.o : $(src)/%.c
	$(cc) $< $(compileflags) -c -o $(build)/$@ $(incdirs)

$(dynamiclibs):
	cp $(lib)/$@ $(bin)/$@

commandjson := compile_commands.json
compile_command_files := $(foreach f,$(sources),$(f)_fcc)

makedir := $(shell pwd)
# Windows is special
ifeq ($(OS),Windows_NT)
	# Handle Cygwin/MSYS2 style paths
	makedir := $(patsubst /c%,C:%,$(makedir))
	# Avoid stupid shell backslash escape problems
	# as well as JSON backslash escape issues
	# Clangd can handle slashes in windows paths
	makedir := $(subst \,/,$(makedir))
endif

.PHONY: initial_compile_command final_compile_command $(compile_command_files)

compile_commands: initial_compile_command $(compile_command_files) final_compile_command

initial_compile_command:
	@echo "[" > $(commandjson)
final_compile_command:
	@echo "]" >> $(commandjson)

$(compile_command_files):
	@echo "Adding command for file: $@ $(src)/$(@:_fcc=.c) $(build)/$(@:_fcc=.o)"
	@echo "  {" >> $(commandjson)
	@echo "    \"directory\": \"$(makedir)\"," >> $(commandjson)
	@echo "    \"command\": \"$(cc) $(src)/$(@:_fcc=.c) $(compileflags) -c -o $(build)/$(@:_fcc=.o) $(incdirs)\"," >> $(commandjson)
	@echo "    \"file\": \"$(src)/$(@:_fcc=.c)\"," >> $(commandjson)
	@echo "    \"output\": \"$(build)/$(@:_fcc=.o)\"" >> $(commandjson)
	@echo "  }," >> $(commandjson)

