CFLAGS= -mno-mips16 -mgp32 -mfp32 -gpubnames  -mlong32 -mips1 -mabicalls -mlong-calls -mframe-header-opt -march=r2k

OBJS= tp2

all: tp2 ej_pruebas

SRC=$(wildcard src/*.c)
TESTS=$(wildcard tests/*.c)

tp2: $(SRC) main/*.c
	gcc -g $^ -o $@

ej_pruebas: $(SRC) $(TESTS)
	gcc -g $^ -o $@

clean:
	rm tp2* ej_pruebas
