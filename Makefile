cdir = src/main/c

.PHONY: all
all: fib heap

ex001 : ${cdir}/ex001.c
	mkdir -p bin
	cc -o bin/ex001 ${cdir}/ex001.c

fib : ${cdir}/fib.c ${cdir}/fibMain.c
	mkdir -p bin
	cc -o bin/fib ${cdir}/fib.c ${cdir}/fibMain.c

heap : ${cdir}/heap.c
	mkdir -p bin
	cc -o bin/heap ${cdir}/heap.c

.PHONY : clean
clean : 
	rm bin/*
