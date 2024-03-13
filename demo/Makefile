# Makefile to build software with CC65

ifeq ("${OSNAME}", "Linux")
  CC65PATH=/usr/local/src/cc65
  CC65INC=$(CC65PATH)/include
  CC65LIB=/usr/local/src/cc65/lib
  CC65=$(CC65PATH)/bin/cc65
  ASM65=$(CC65PATH)/bin/ca65
  ASMINC=$(CC65PATH)/asminc
  CFGPATH=$(CC65PATH)/cfg
  LD65=$(CC65PATH)/bin/ld65
  CL65=$(CC65PATH)/bin/cl65
else
  MINGW=/c/MinGW/msys/1.0
  CC65PATH=$(MINGW)/share/cc65
  CC65INC=$(CC65PATH)/include
  ASMINC=$(CC65PATH)/asminc
  CC65LIB=$(CC65PATH)/lib
  CFGPATH=$(CC65PATH)/cfg
  CC65=$(MINGW)/bin/cc65
  ASM65=$(MINGW)/bin/ca65
  LD65=$(MINGW)/bin/ld65
endif


all: a8cdemo.xex start-demo

OBJ=abbuc-demo.o

TARGET=atarixl
TARGET_LIB=atarixl.lib

abbuc-demo.s: abbuc-demo.c
	@echo "COMPILE ----------------------------------------------------"
	@echo "$(TARGET) $(CC65)"
	$(CC65) -T -Ors -t $(TARGET) -I $(CC65INC) $< -o $@
#	$(CC65) -T      -t $(TARGET) -I $(CC65INC) $< -o $@

abbuc-demo.o: abbuc-demo.s
	@echo "ASSEMBLE ---------------------------------------------------"
	$(ASM65) $< -I $(ASMINC) -o $@

a8cdemo.xex: $(OBJ)
	@echo "LINK -------------------------------------------------------"
	$(LD65) -o $@ -t $(TARGET) --cfg-path $(CFGPATH) -L $(CC65LIB) $(OBJ) $(TARGET_LIB)

## fuer Fortgeschrittene gibt es das alles in eins Tool cl65 (compile & link)
#abbuc-demo.xex: abbuc-demo.c
#	$(CL65) -v -Os -t $(TARGET) $< -o $@

start-demo:
	atari800 a8cdemo.xex

clean:
	rm -f a8cdemo.xex
	rm -f abbuc-demo.o
	rm -f abbuc-demo.s

# try to build with LLVM, but need some code changes
#COMPILER=mos-atari8-clang
#llvm: abbuc-demo.llvm.xex
#
#abbuc-demo.llvm.xex: abbuc-demo.c
#	$(COMPILER) -Os $< -o $@
#
