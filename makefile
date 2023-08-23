# Files
sources := main
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
cl := clang

libargs := $(foreach lib,$(libs),-l$(lib))
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

.PHONY: all tag clean fresh

all: tag $(outputfile) $(dynamiclibs)

fresh: tag clean all

tag:
	@echo "* ---------------------------- "
	@echo "* Building for: $(OS)"
	@echo "*   executable: $(outputfile)"
	@echo "*   requires: $(dynamiclibs)"
	@echo "* ---------------------------- "

$(outputfile): $(objfiles)
	$(cl) $(objpaths) $(libdirs) $(libargs) -o $(bin)/$@

clean:
	@echo "cleaning generated files"
	-rm -f $(objpaths)
	-rm -f $(outputfile)
	-rm -f $(foreach lib,$(dynamiclibs),$(bin)/$(lib))
	ls $(build) $(bin)

%.o : $(src)/%.c
	$(cc) -c $< -o $(build)/$@ $(incdirs)

$(dynamiclibs):
	cp $(lib)/$@ $(bin)/$@

