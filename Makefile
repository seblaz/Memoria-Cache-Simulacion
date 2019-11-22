CFLAGS= -mno-mips16 -mgp32 -mfp32 -gpubnames  -mlong32 -mips1 -mabicalls -mlong-calls -mframe-header-opt -march=r2k

OBJS= tp2

all: tp2

tp2: main.c
	gcc -g $^ -o $@

clean:
	rm tp2*