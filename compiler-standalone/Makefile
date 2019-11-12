

all: out/compiler.exe test/test.exe

clean:
	rm -f out/compiler.exe test/test.exe
	rm -f src/lexer.inl
	rm -f test/grammar.cpp



# ---------------- Compiler ----------------

src/lexer.inl: src/lexer.template src/_txt2cpp.awk
	gawk -f src/_txt2cpp.awk OUTFILE=src/lexer.inl src/lexer.template

out/compiler.exe: src/common.h src/lexer.inl src/lexer.cpp src/parser.cpp src/main.cpp
	mkdir -p out
	g++ src/lexer.cpp src/parser.cpp src/main.cpp -o out/compiler.exe



# ---------------- Test ----------------

test/grammar.cpp: test/grammar.h out/compiler.exe
	./out/compiler.exe test/grammar.h test/grammar.cpp


test/test.exe: test/grammar.cpp
	g++ test/grammar.cpp -o test/test.exe
