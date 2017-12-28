cdir = src/main/c

.PHONY: all
all: fib heap


fib : ${cdir}/fib.c
	mkdir -p bin
	cc -o bin/fib ${cdir}/fib.c

heap : ${cdir}/heap.c
	mkdir -p bin
	cc -o bin/heap ${cdir}/heap.c

.PHONY : clean
clean : 
	rm bin/*
