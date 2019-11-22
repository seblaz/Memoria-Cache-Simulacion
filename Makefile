CFLAGS= -mno-mips16 -mgp32 -mfp32 -gpubnames  -mlong32 -mips1 -mabicalls -mlong-calls -mframe-header-opt -march=r2k

OBJS= tp2

all: tp2

SRC=$(wildcard src/*.c main/*.c)

tp2: $(SRC)
	gcc -g $^ -o $@

clean:
	rm tp2*