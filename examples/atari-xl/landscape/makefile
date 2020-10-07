ifeq ($(OS), Windows_NT)
	K65=${K65_PATH}\bin\k65.exe
	FilesList=windows.k65proj
endif
ifeq ($(shell uname), Linux)
	K65=${K65_HOME}/bin/k65
	FilesList=linux.k65proj
endif

all: main

main:
	$(K65) @$(FilesList)
