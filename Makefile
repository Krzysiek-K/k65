

# ------------------------------------------------ Project definitions ------------------------------------------------


_OBJECTS+= asm.o
_OBJECTS+= base/convert_parse.o
_OBJECTS+= base/streams.o
_OBJECTS+= base/strings.o
_OBJECTS+= base/vfs.o
_OBJECTS+= compiler_src.o
_OBJECTS+= comstate.o
_OBJECTS+= compiler_eval.o
_OBJECTS+= gen/compiler.o
_OBJECTS+= imager.o
_OBJECTS+= main.o
_OBJECTS+= sqapi.o
_OBJECTS+= sqbind.o
_OBJECTS+= sqlinker.o
_OBJECTS+= squirrel.o
_OBJECTS+= stdafx.o

_HEADERS+= asm.h
_HEADERS+= base/base.h
_HEADERS+= base/convert2.h
_HEADERS+= base/vmath.h
_HEADERS+= base/streams.h
_HEADERS+= base/vfs.h
_HEADERS+= common.h
_HEADERS+= compiler.h
_HEADERS+= comstate.h
_HEADERS+= eval.h
_HEADERS+= evalparser.h
_HEADERS+= imager.h
_HEADERS+= optab.h
_HEADERS+= sqbind.h
_HEADERS+= sqlinker.h
_HEADERS+= squirrel.h
_HEADERS+= stdafx.h
_HEADERS+= compiler_evany.h
_HEADERS+= gen/compiler_evops.inl






# ------------------------------------------------ Configuration ------------------------------------------------


COMPILER = bin/compiler.exe
GAWK := $(which gawk)



# ------------------------------------------------ Misc settings ------------------------------------------------


OBJECTS = $(patsubst %,obj/%,$(_OBJECTS))
HEADERS = $(patsubst %,src/%,$(_HEADERS))


CXXFLAGS+= -Isrc


# ------------------------------------------------ Top-level targets ------------------------------------------------

all: init out/k65.exe

clean:
	rm -f out/k65.exe
	rm -f obj/*.*
	rm -f src/gen/*.*

rebuild: clean all

init:
	mkdir -p doc
	mkdir -p out
	mkdir -p obj
	mkdir -p obj/base
	mkdir -p obj/gen
	mkdir -p src/gen

test: a2600-tutorial-03.bin



# ------------------------------------------------ Build rules ------------------------------------------------


out/k65.exe : $(OBJECTS)
	g++ -o $@ $(OBJECTS)

obj/%.o : src/%.cpp $(HEADERS)
	g++ -c $(CXXFLAGS) -o obj/$*.o $<


src/gen/compiler.cpp : src/compiler.inc
	# Building K65 code parser
	$(COMPILER) src/compiler.inc src/gen/compiler.cpp

src/gen/compiler_evops.inl doc/wiki-eval-funcs.txt : src/gen_eval_ops.awk src/compiler_eval.cpp
	$(GAWK) -f src/gen_eval_ops.awk OUT=src/gen/compiler_evops.inl src/compiler_eval.cpp


# ------------------------------------------------ Test project ------------------------------------------------

a2600-tutorial-03.bin : out/k65.exe workdir/a2600-tutorial-03/files.lst workdir/a2600-tutorial-03/_defs.k65 workdir/a2600-tutorial-03/main.k65 workdir/a2600-tutorial-03/sprites.bmp
	cd workdir && ../out/k65.exe @a2600-tutorial-03/files.lst
